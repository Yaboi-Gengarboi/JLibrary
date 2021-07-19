// JLibraryDevelopment
// Shader.cpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-14 by Justyn Durnford
// Source file for the Shader class.

#include <JLibrary/Graphics/GLSL.hpp>
#include <JLibrary/Graphics/Shader.hpp>
#include <JLibrary/Graphics/Texture.hpp>
#include <JLibrary/Multithread/Lock.hpp>
#include <JLibrary/Multithread/Mutex.hpp>
using namespace jlib;
using namespace glsl;

#include <fstream>
using std::ifstream;

#include <iostream>
using std::ios_base;
using std::streamsize;
using std::cout;
using std::endl;

#include <string>
using std::size_t;
using std::string;

#include <vector>
using std::vector;

#include <utility>
using std::pair;
using std::make_pair;

#ifndef JLIB_OPENGL_ES

	#define castToGlHandle(x) (x)
	#define castFromGlHandle(x) (x)

#endif // JLIB_OPENGL_ES

namespace
{
    Mutex maxTextureUnitsMutex;
    Mutex isAvailableMutex;

    GLint checkMaxTextureUnits()
    {
        GLint maxUnits = 0;
        glCheck(glGetIntegerv(GLEXT_GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxUnits));
        return maxUnits;
    }

    // Retrieve the maximum number of texture units available.
    GLint getMaxTextureUnits()
    {
        Lock lock(maxTextureUnitsMutex);
        static GLint maxUnits = checkMaxTextureUnits();
        return maxUnits;
    }

    // Read the contents of a file into an array of char.
    bool getFileContents(const string& filename, vector<char>& buffer)
    {
        ifstream file(filename.c_str(), ios_base::binary);
        if (file)
        {
            file.seekg(0, ios_base::end);
            streamsize size = file.tellg();
            if (size > 0)
            {
                file.seekg(0, ios_base::beg);
                buffer.resize(static_cast<size_t>(size));
                file.read(&buffer[0], size);
            }
            buffer.push_back('\0');
            return true;
        }

        return false;
    }

    // Read the contents of a stream into an array of char.
    bool getStreamContents(InputStream& stream, vector<char>& buffer)
    {
        bool success = true;
        i64 size = stream.size();
        if (size > 0)
        {
            buffer.resize(static_cast<size_t>(size));
            stream.seek(0);
            i64 read = stream.read(&buffer[0], size);
            success = (read == size);
        }
        buffer.push_back('\0');
        return success;
    }

    // Transforms an array of 2D vectors into a contiguous array of scalars.
    template <typename T>
    vector<T> flatten(const Vector2<T>* vectorArray, size_t length)
    {
        vector<T> contiguous(2 * length);
        for (size_t i = 0; i < length; ++i)
        {
            contiguous[2 * i + 0] = vectorArray[i].x;
            contiguous[2 * i + 1] = vectorArray[i].y;
        }

        return contiguous;
    }

    // Transforms an array of 3D vectors into a contiguous array of scalars.
    template <typename T>
    vector<T> flatten(const Vector3<T>* vectorArray, size_t length)
    {
        vector<T> contiguous(3 * length);
        for (size_t i = 0; i < length; ++i)
        {
            contiguous[3 * i + 0] = vectorArray[i].x;
            contiguous[3 * i + 1] = vectorArray[i].y;
            contiguous[3 * i + 2] = vectorArray[i].z;
        }

        return contiguous;
    }

    // Transforms an array of 4D vectors into a contiguous array of scalars.
    template <typename T>
    vector<T> flatten(const VectorN<T, 4>* vectorArray, size_t length)
    {
        vector<T> contiguous(4 * length);
        for (size_t i = 0; i < length; ++i)
        {
            contiguous[4 * i + 0] = vectorArray[i][0];
            contiguous[4 * i + 1] = vectorArray[i][1];
            contiguous[4 * i + 2] = vectorArray[i][2];
            contiguous[4 * i + 3] = vectorArray[i][3];
        }

        return contiguous;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

struct Shader::UniformBinder : private NonCopyable
{
    TransientContextLock lock;           // Lock to keep context active while uniform is bound.
    GLEXT_GLhandle       savedProgram;   // Handle to the previously active program object.
    GLEXT_GLhandle       currentProgram; // Handle to the program object of the modified jlib::Shader instance.
    GLint                location;       // Uniform location, used by the surrounding jlib::Shader code.

    // Constructor.
    // Sets up the state before uniform is set.
    UniformBinder(Shader& shader, const string& name)
    {
        savedProgram = 0;
        currentProgram = castToGlHandle(shader.shaderProgram_);
        location = -1;

        if (currentProgram)
        {
            // Enable program object.
            glCheck(savedProgram = GLEXT_glGetHandle(GLEXT_GL_PROGRAM_OBJECT));
            if (currentProgram != savedProgram)
                glCheck(GLEXT_glUseProgramObject(currentProgram));

            // Store uniform location for further use outside constructor.
            location = shader.getUniformLocation(name);
        }
    }

    // Destructor.
    // Restores state after uniform is set.
    ~UniformBinder()
    {
        // Disable program object.
        if (currentProgram && (currentProgram != savedProgram))
            glCheck(GLEXT_glUseProgramObject(savedProgram));
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

bool Shader::compile(const char* vertexShaderCode, const char* geometryShaderCode, 
                     const char* fragmentShaderCode)
{
    TransientContextLock lock;

    // First make sure that we can use shaders.
    if (!isAvailable())
    {
        cout << "Failed to create a shader: your system doesn't support shaders "
             << "(you should test Shader::isAvailable() before trying to use the Shader class)" << endl;
        return false;
    }

    // Make sure we can use geometry shaders.
    if (geometryShaderCode && !isGeometryAvailable())
    {
        cout << "Failed to create a shader: your system doesn't support geometry shaders "
             << "(you should test Shader::isGeometryAvailable() before trying to use geometry shaders)" << endl;
        return false;
    }

    // Destroy the shader if it was already created.
    if (shaderProgram_)
    {
        glCheck(GLEXT_glDeleteObject(castToGlHandle(shaderProgram_)));
        shaderProgram_ = 0;
    }

    // Reset the internal state.
    currentTexture_ = -1;
    textures_.clear();
    uniforms_.clear();

    // Create the program.
    GLEXT_GLhandle shaderProgram;
    glCheck(shaderProgram = GLEXT_glCreateProgramObject());

    // Create the vertex shader if needed.
    if (vertexShaderCode)
    {
        // Create and compile the shader.
        GLEXT_GLhandle vertexShader;
        glCheck(vertexShader = GLEXT_glCreateShaderObject(GLEXT_GL_VERTEX_SHADER));
        glCheck(GLEXT_glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr));
        glCheck(GLEXT_glCompileShader(vertexShader));

        // Check the compile log.
        GLint success;
        glCheck(GLEXT_glGetObjectParameteriv(vertexShader, GLEXT_GL_OBJECT_COMPILE_STATUS, &success));
        if (success == GL_FALSE)
        {
            char log[1024];
            glCheck(GLEXT_glGetInfoLog(vertexShader, sizeof(log), 0, log));
            cout << "Failed to compile vertex shader:" << endl << log << endl;
            glCheck(GLEXT_glDeleteObject(vertexShader));
            glCheck(GLEXT_glDeleteObject(shaderProgram));
            return false;
        }

        // Attach the shader to the program, and delete it (not needed anymore).
        glCheck(GLEXT_glAttachObject(shaderProgram, vertexShader));
        glCheck(GLEXT_glDeleteObject(vertexShader));
    }

    // Create the geometry shader if needed.
    if (geometryShaderCode)
    {
        // Create and compile the shader.
        GLEXT_GLhandle geometryShader = GLEXT_glCreateShaderObject(GLEXT_GL_GEOMETRY_SHADER);
        glCheck(GLEXT_glShaderSource(geometryShader, 1, &geometryShaderCode, nullptr));
        glCheck(GLEXT_glCompileShader(geometryShader));

        // Check the compile log.
        GLint success;
        glCheck(GLEXT_glGetObjectParameteriv(geometryShader, GLEXT_GL_OBJECT_COMPILE_STATUS, &success));
        if (success == GL_FALSE)
        {
            char log[1024];
            glCheck(GLEXT_glGetInfoLog(geometryShader, sizeof(log), 0, log));
            cout << "Failed to compile geometry shader:" << endl << log << endl;
            glCheck(GLEXT_glDeleteObject(geometryShader));
            glCheck(GLEXT_glDeleteObject(shaderProgram));
            return false;
        }

        // Attach the shader to the program, and delete it (not needed anymore).
        glCheck(GLEXT_glAttachObject(shaderProgram, geometryShader));
        glCheck(GLEXT_glDeleteObject(geometryShader));
    }

    // Create the fragment shader if needed.
    if (fragmentShaderCode)
    {
        // Create and compile the shader.
        GLEXT_GLhandle fragmentShader;
        glCheck(fragmentShader = GLEXT_glCreateShaderObject(GLEXT_GL_FRAGMENT_SHADER));
        glCheck(GLEXT_glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr));
        glCheck(GLEXT_glCompileShader(fragmentShader));

        // Check the compile log.
        GLint success;
        glCheck(GLEXT_glGetObjectParameteriv(fragmentShader, GLEXT_GL_OBJECT_COMPILE_STATUS, &success));
        if (success == GL_FALSE)
        {
            char log[1024];
            glCheck(GLEXT_glGetInfoLog(fragmentShader, sizeof(log), 0, log));
            cout << "Failed to compile fragment shader:" << endl << log << endl;
            glCheck(GLEXT_glDeleteObject(fragmentShader));
            glCheck(GLEXT_glDeleteObject(shaderProgram));
            return false;
        }

        // Attach the shader to the program, and delete it (not needed anymore).
        glCheck(GLEXT_glAttachObject(shaderProgram, fragmentShader));
        glCheck(GLEXT_glDeleteObject(fragmentShader));
    }

    // Link the program.
    glCheck(GLEXT_glLinkProgram(shaderProgram));

    // Check the link log.
    GLint success;
    glCheck(GLEXT_glGetObjectParameteriv(shaderProgram, GLEXT_GL_OBJECT_LINK_STATUS, &success));
    if (success == GL_FALSE)
    {
        char log[1024];
        glCheck(GLEXT_glGetInfoLog(shaderProgram, sizeof(log), 0, log));
        cout << "Failed to link shader:" << endl << log << endl;
        glCheck(GLEXT_glDeleteObject(shaderProgram));
        return false;
    }

    shaderProgram_ = castFromGlHandle(shaderProgram);

    // Force an OpenGL flush, so that the shader will appear updated
    // in all contexts immediately (solves problems in multi-threaded apps).
    glCheck(glFlush());

    return true;
}

void Shader::bindTextures() const
{
    TextureTable::const_iterator iter = textures_.begin();
    for (size_t i = 0; i < textures_.size(); ++i)
    {
        GLint index = static_cast<GLsizei>(i + 1);
        glCheck(GLEXT_glUniform1i(iter->first, index));
        glCheck(GLEXT_glActiveTexture(GLEXT_GL_TEXTURE0 + index));
        Texture::bind(iter->second);
        ++iter;
    }

    // Make sure that the texture unit which is left active is the number 0.
    glCheck(GLEXT_glActiveTexture(GLEXT_GL_TEXTURE0));
}

i32 Shader::getUniformLocation(const string& name)
{
    // Check the cache.
    UniformTable::const_iterator iter = uniforms_.find(name);
    if (iter != uniforms_.end()) // Already in cache, return it.
        return iter->second;
    else
    {
        // Not in cache, request the location from OpenGL
        i32 location = GLEXT_glGetUniformLocation(castToGlHandle(shaderProgram_), name.data());
        uniforms_.insert(make_pair(name, location));

        if (location == -1)
            cout << "Uniform \"" << name << "\" not found in shader" << endl;

        return location;
    }
}

Shader::Shader()
{
    shaderProgram_ = 0;
    currentTexture_ = -1;
}

Shader::~Shader()
{
    TransientContextLock lock;

    // Destroy effect program.
    if (shaderProgram_)
        glCheck(GLEXT_glDeleteObject(castToGlHandle(shaderProgram_)));
}

bool Shader::loadFromFile(const string& filename, Type type)
{
    // Read the file.
    vector<char> shader;
    if (!getFileContents(filename, shader))
    {
        cout << "Failed to open shader file \"" << filename << "\"" << endl;
        return false;
    }

    // Compile the shader program.
    if (type == Vertex)
        return compile(&shader[0], nullptr, nullptr);
    else if (type == Geometry)
        return compile(nullptr, &shader[0], nullptr);
    else
        return compile(nullptr, nullptr, &shader[0]);
}

bool Shader::loadFromFile(const string& vertexShaderFilename, const string& fragmentShaderFilename)
{
    // Read the vertex shader file.
    vector<char> vertexShader;
    if (!getFileContents(vertexShaderFilename, vertexShader))
    {
        cout << "Failed to open vertex shader file \"" << vertexShaderFilename << "\"" << endl;
        return false;
    }

    // Read the fragment shader file.
    vector<char> fragmentShader;
    if (!getFileContents(fragmentShaderFilename, fragmentShader))
    {
        cout << "Failed to open fragment shader file \"" << fragmentShaderFilename << "\"" << endl;
        return false;
    }

    // Compile the shader program.
    return compile(&vertexShader[0], nullptr, &fragmentShader[0]);
}

bool Shader::loadFromFile(const string& vertexShaderFilename, const string& geometryShaderFilename, 
                          const string& fragmentShaderFilename)
{
    // Read the vertex shader file.
    vector<char> vertexShader;
    if (!getFileContents(vertexShaderFilename, vertexShader))
    {
        cout << "Failed to open vertex shader file \"" << vertexShaderFilename << "\"" << endl;
        return false;
    }

    // Read the geometry shader file.
    vector<char> geometryShader;
    if (!getFileContents(geometryShaderFilename, geometryShader))
    {
        cout << "Failed to open geometry shader file \"" << geometryShaderFilename << "\"" << endl;
        return false;
    }

    // Read the fragment shader file.
    vector<char> fragmentShader;
    if (!getFileContents(fragmentShaderFilename, fragmentShader))
    {
        cout << "Failed to open fragment shader file \"" << fragmentShaderFilename << "\"" << endl;
        return false;
    }

    // Compile the shader program.
    return compile(&vertexShader[0], &geometryShader[0], &fragmentShader[0]);
}

bool Shader::loadFromMemory(const std::string& shader, Type type)
{
    // Compile the shader program
    if (type == Vertex)
        return compile(shader.c_str(), nullptr, nullptr);
    else if (type == Geometry)
        return compile(nullptr, shader.c_str(), nullptr);
    else
        return compile(nullptr, nullptr, shader.c_str());
}

bool Shader::loadFromMemory(const string& vertexShader, const string& fragmentShader)
{
    // Compile the shader program.
    return compile(vertexShader.data(), nullptr, fragmentShader.data());
}

bool Shader::loadFromMemory(const string& vertexShader, const string& geometryShader, 
                            const string& fragmentShader)
{
    // Compile the shader program.
    return compile(vertexShader.data(), geometryShader.data(), fragmentShader.data());
}

bool Shader::loadFromStream(InputStream& stream, Type type)
{
    // Read the shader code from the stream.
    vector<char> shader;
    if (!getStreamContents(stream, shader))
    {
        cout << "Failed to read shader from stream" << endl;
        return false;
    }

    // Compile the shader program.
    if (type == Vertex)
        return compile(&shader[0], nullptr, nullptr);
    else if (type == Geometry)
        return compile(nullptr, &shader[0], nullptr);
    else
        return compile(nullptr, nullptr, &shader[0]);
}

bool Shader::loadFromStream(InputStream& vertexShaderStream, InputStream& fragmentShaderStream)
{
    // Read the vertex shader code from the stream.
    vector<char> vertexShader;
    if (!getStreamContents(vertexShaderStream, vertexShader))
    {
        cout << "Failed to read vertex shader from stream" << endl;
        return false;
    }

    // Read the fragment shader code from the stream.
    vector<char> fragmentShader;
    if (!getStreamContents(fragmentShaderStream, fragmentShader))
    {
        cout << "Failed to read fragment shader from stream" << endl;
        return false;
    }

    // Compile the shader program
    return compile(&vertexShader[0], nullptr, &fragmentShader[0]);
}

bool Shader::loadFromStream(InputStream& vertexShaderStream, InputStream& geometryShaderStream, 
                            InputStream& fragmentShaderStream)
{
    // Read the vertex shader code from the stream.
    vector<char> vertexShader;
    if (!getStreamContents(vertexShaderStream, vertexShader))
    {
        cout << "Failed to read vertex shader from stream" << endl;
        return false;
    }

    // Read the geometry shader code from the stream.
    vector<char> geometryShader;
    if (!getStreamContents(geometryShaderStream, geometryShader))
    {
        cout << "Failed to read geometry shader from stream" << endl;
        return false;
    }

    // Read the fragment shader code from the stream.
    vector<char> fragmentShader;
    if (!getStreamContents(fragmentShaderStream, fragmentShader))
    {
        cout << "Failed to read fragment shader from stream" << endl;
        return false;
    }

    // Compile the shader program.
    return compile(&vertexShader[0], &geometryShader[0], &fragmentShader[0]);
}

void Shader::setUniform(const string& name, float x)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform1f(binder.location, x));
}

void Shader::setUniform(const string& name, const Vec2& v)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform2f(binder.location, v.x, v.y));
}

void Shader::setUniform(const string& name, const Vec3& v)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform3f(binder.location, v.x, v.y, v.z));
}

void Shader::setUniform(const string& name, const Vec4& v)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform4f(binder.location, v[0], v[1], v[2], v[3]));
}

void Shader::setUniform(const string& name, int x)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform1i(binder.location, x));
}

void Shader::setUniform(const string& name, const Ivec2& v)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform2i(binder.location, v.x, v.y));
}

void Shader::setUniform(const string& name, const Ivec3& v)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform3i(binder.location, v.x, v.y, v.z));
}

void Shader::setUniform(const string& name, const Ivec4& v)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform4i(binder.location, v[0], v[1], v[2], v[3]));
}

void Shader::setUniform(const string& name, bool x)
{
    setUniform(name, static_cast<int>(x));
}

void Shader::setUniform(const string& name, const Bvec2& v)
{
    setUniform(name, Ivec2(v));
}

void Shader::setUniform(const string& name, const Bvec3& v)
{
    setUniform(name, Ivec3(v));
}

void Shader::setUniform(const string& name, const Bvec4& v)
{
    setUniform(name, Ivec4(v));
}

void Shader::setUniform(const string& name, const Mat3& matrix)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniformMatrix3fv(binder.location, 1, GL_FALSE, matrix.begin()));
}

void Shader::setUniform(const string& name, const Mat4& matrix)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniformMatrix4fv(binder.location, 1, GL_FALSE, matrix.begin()));
}

void Shader::setUniform(const string& name, const Texture& texture)
{
    if (shaderProgram_)
    {
        TransientContextLock lock;

        // Find the location of the variable in the shader.
        int location = getUniformLocation(name);
        if (location != -1)
        {
            // Store the location -> texture mapping.
            TextureTable::iterator iter = textures_.find(location);
            if (iter == textures_.end())
            {
                // New entry, make sure there are enough texture units.
                GLint maxUnits = getMaxTextureUnits();
                if (textures_.size() + 1 >= static_cast<size_t>(maxUnits))
                {
                    cout << "Impossible to use texture \"" << name 
                         << "\" for shader: all available texture units are used" << endl;
                    return;
                }

                textures_[location] = &texture;
            }
            else // Location already used, just replace the texture.
                iter->second = &texture;
        }
    }
}

void Shader::setUniform(const string& name, CurrentTextureType)
{
    if (shaderProgram_)
    {
        TransientContextLock lock;

        // Find the location of the variable in the shader.
        currentTexture_ = getUniformLocation(name);
    }
}

void Shader::setUniformArray(const string& name, const float* scalarArray, size_t length)
{
    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform1fv(binder.location, static_cast<GLsizei>(length), scalarArray));
}

void Shader::setUniformArray(const string& name, const Vec2* vectorArray, size_t length)
{
    vector<float> contiguous = flatten(vectorArray, length);

    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform2fv(binder.location, static_cast<GLsizei>(length), &contiguous[0]));
}

void Shader::setUniformArray(const string& name, const Vec3* vectorArray, size_t length)
{
    vector<float> contiguous = flatten(vectorArray, length);

    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform3fv(binder.location, static_cast<GLsizei>(length), &contiguous[0]));
}

void Shader::setUniformArray(const string& name, const Vec4* vectorArray, size_t length)
{
    vector<float> contiguous = flatten(vectorArray, length);

    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniform4fv(binder.location, static_cast<GLsizei>(length), &contiguous[0]));
}

void Shader::setUniformArray(const string& name, const Mat3* matrixArray, size_t length)
{
    const size_t matrixSize = 3 * 3;

    vector<float> contiguous(matrixSize * length);
    for (size_t i = 0; i < length; ++i)
        copyMatrix(matrixArray[i].begin(), &contiguous[matrixSize * i], matrixSize);

    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniformMatrix3fv(binder.location, static_cast<GLsizei>(length), GL_FALSE, &contiguous[0]));
}

void Shader::setUniformArray(const string& name, const Mat4* matrixArray, size_t length)
{
    const size_t matrixSize = 4 * 4;

    vector<float> contiguous(matrixSize * length);
    for (size_t i = 0; i < length; ++i)
        copyMatrix(matrixArray[i].begin(), &contiguous[matrixSize * i], matrixSize);

    UniformBinder binder(*this, name);
    if (binder.location != -1)
        glCheck(GLEXT_glUniformMatrix4fv(binder.location, static_cast<GLsizei>(length), GL_FALSE, &contiguous[0]));
}

void Shader::bind(const Shader* shader)
{
    TransientContextLock lock;

    // Make sure that we can use shaders.
    if (!isAvailable())
    {
        cout << "Failed to bind or unbind shader: your system doesn't support shaders "
             << "(you should test Shader::isAvailable() before trying to use the Shader class)" << endl;
        return;
    }

    if (shader && shader->shaderProgram_)
    {
        // Enable the program.
        glCheck(GLEXT_glUseProgramObject(castToGlHandle(shader->shaderProgram_)));

        // Bind the textures.
        shader->bindTextures();

        // Bind the current texture
        if (shader->currentTexture_ != -1)
            glCheck(GLEXT_glUniform1i(shader->currentTexture_, 0));
    }
    else // Bind no shader
        glCheck(GLEXT_glUseProgramObject(0));
}

bool Shader::isAvailable()
{
    Lock lock(isAvailableMutex);

    static bool checked = false;
    static bool available = false;

    if (!checked)
    {
        checked = true;

        TransientContextLock contextLock;

        // Make sure that extensions are initialized.
        ensureExtensionsInit();

        available = GLEXT_multitexture &&
            GLEXT_shading_language_100 &&
            GLEXT_shader_objects       &&
            GLEXT_vertex_shader        &&
            GLEXT_fragment_shader;
    }

    return available;
}

bool Shader::isGeometryAvailable()
{
    Lock lock(isAvailableMutex);

    static bool checked = false;
    static bool available = false;

    if (!checked)
    {
        checked = true;

        TransientContextLock contextLock;

        // Make sure that extensions are initialized.
        ensureExtensionsInit();

        available = isAvailable() && (GLEXT_geometry_shader4 || GLEXT_GL_VERSION_3_2);
    }

    return available;
}