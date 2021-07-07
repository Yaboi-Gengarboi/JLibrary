////////////////////////////////////////////////////////////
//
// THIS IS A MODIFIED FILE FROM SFML 2.5.1
// 
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2021 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
// 
// JLibraryDevelopment
// Shader.hpp
// Created on 2021-07-06 by Justyn Durnford
// Last modified on 2021-07-06 by Justyn Durnford
// Header file for the Shader class.

#pragma once

#include <JLibrary/Graphics/GlResource.hpp>
#include <JLibrary/Graphics/GLSL.hpp>
#include <JLibrary/System/Integer.hpp>
#include <map>
#include <string>

namespace jlib
{
	class Color;
	class InputStream;
	class Texture;
	class Transformation;

	// Shader class (vertex, geometry and fragment).
	class Shader : GlResource, NonCopyable
	{
        public:

        // Types of shaders.
        enum Type
        {
            Vertex,
            Geometry,
            Fragment
        };

        // Special type that can be passed to setUniform()
        // and represents the texture of the object being drawn.
        struct CurrentTextureType {};

        // Represents the texture of the object being drawn.
        static CurrentTextureType CurrentTexture;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

		private:

		// RAII object to save and restore the program
		// binding while uniforms are being set.
		struct UniformBinder;

		// Shorthand for std::map<int, const Texture*>
		typedef std::map<i32, const Texture*> TextureTable;
		// Shorthand for std::map<std::string, int>
		typedef std::map<std::string, i32> UniformTable;

		u32          shaderProgram_;  
		i32          currentTexture_;
		TextureTable textures_;
		UniformTable uniforms_;

        // Compiles the shader(s) and creates the program.
        // If one of the arguments is nullptr, the corresponding shader
        // is not created.
        // Returns true if successful.
        bool compile(const char* vertexShaderCode, const char* geometryShaderCode, 
                     const char* fragmentShaderCode);

        // Binds all the textures used by the shader. 
        // This function seperates each texture to a different unit, and
        // updates the corresponding variables in the shader accordingly.
        void bindTextures() const;

        // Gets the location ID of a shader uniform.
        int getUniformLocation(const std::string& name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        // Default constructor.
        // This constructor creates an invalid shader.
        Shader();

        // Destructor.
        ~Shader();

        // Loads the vertex, geometry or fragment shader from a file.
        // This function loads a single shader, vertex, geometry or
        // fragment, identified by the second argument.
        // The source must be a text file containing a valid
        // shader in GLSL language. GLSL is a C-like language
        // dedicated to OpenGL shaders; you'll probably need to
        // read a good documentation for it before writing your
        // own shaders.
        // Returns true if successful.
        bool loadFromFile(const std::string& filename, Type type);

        // Loads both the vertex and fragment shaders from files.
        // This function loads both the vertex and the fragment
        // shaders. If one of them fails to load, the shader is left
        // empty (the valid shader is unloaded).
        // The sources must be text files containing valid shaders
        // in GLSL language. GLSL is a C-like language dedicated to
        // OpenGL shaders; you'll probably need to read a good documentation
        // for it before writing your own shaders.
        // Returns true if successful.
        bool loadFromFile(const std::string& vertexShaderFilename, 
                          const std::string& fragmentShaderFilename);

        // Loads the vertex, geometry and fragment shaders from files.
        // This function loads the vertex, geometry and fragment
        // shaders. If one of them fails to load, the shader is left
        // empty (the valid shader is unloaded).
        // The sources must be text files containing valid shaders
        // in GLSL language. GLSL is a C-like language dedicated to
        // OpenGL shaders; you'll probably need to read a good documentation
        // for it before writing your own shaders.
        // Returns true if successful.
        bool loadFromFile(const std::string& vertexShaderFilename, 
                          const std::string& geometryShaderFilename, 
                          const std::string& fragmentShaderFilename);

        // Loads the vertex, geometry or fragment shader from a source code in memory.
        // This function loads a single shader, vertex, geometry
        // or fragment, identified by the second argument.
        // The source code must be a valid shader in GLSL language.
        // GLSL is a C-like language dedicated to OpenGL shaders;
        // you'll probably need to read a good documentation for
        // it before writing your own shaders.
        // Returns true if successful.
        bool loadFromMemory(const std::string& shader, Type type);

        // Loads both the vertex and fragment shaders from source codes in memory.
        // This function loads both the vertex and the fragment
        // shaders. If one of them fails to load, the shader is left
        // empty (the valid shader is unloaded).
        // The sources must be valid shaders in GLSL language. GLSL is
        // a C-like language dedicated to OpenGL shaders; you'll
        // probably need to read a good documentation for it before
        // writing your own shaders.
        // Returns true if successful.
        bool loadFromMemory(const std::string& vertexShader, const std::string& fragmentShader);

        // Loads the vertex, geometry and fragment shaders from source codes in memory.
        // This function loads the vertex, geometry and fragment
        // shaders. If one of them fails to load, the shader is left
        // empty (the valid shader is unloaded).
        // The sources must be valid shaders in GLSL language. GLSL is
        // a C-like language dedicated to OpenGL shaders; you'll
        // probably need to read a good documentation for it before
        // writing your own shaders.
        // Returns true if successful.
        bool loadFromMemory(const std::string& vertexShader, const std::string& geometryShader, 
                            const std::string& fragmentShader);

        // Loads the vertex, geometry or fragment shader from a custom stream.
        // This function loads a single shader, vertex, geometry
        // or fragment, identified by the second argument.
        // The source code must be a valid shader in GLSL language.
        // GLSL is a C-like language dedicated to OpenGL shaders;
        // you'll probably need to read a good documentation for it
        // before writing your own shaders.
        // Returns true if successful.
        bool loadFromStream(InputStream& stream, Type type);

        // Loads both the vertex and fragment shaders from custom streams.
        // This function loads both the vertex and the fragment
        // shaders. If one of them fails to load, the shader is left
        // empty (the valid shader is unloaded).
        // The source codes must be valid shaders in GLSL language.
        // GLSL is a C-like language dedicated to OpenGL shaders;
        // you'll probably need to read a good documentation for
        // it before writing your own shaders.
        // Returns true if successful.
        bool loadFromStream(InputStream& vertexShaderStream, InputStream& fragmentShaderStream);

        // Loads the vertex, geometry and fragment shaders from custom streams.
        // This function loads the vertex, geometry and fragment
        // shaders. If one of them fails to load, the shader is left
        // empty (the valid shader is unloaded).
        // The source codes must be valid shaders in GLSL language.
        // GLSL is a C-like language dedicated to OpenGL shaders;
        // you'll probably need to read a good documentation for
        // it before writing your own shaders.
        // Returns true if successful.
        bool loadFromStream(InputStream& vertexShaderStream, InputStream& geometryShaderStream, 
                            InputStream& fragmentShaderStream);

        // Specifies the value for the float uniform.
        void setUniform(const std::string& name, float x);

        // Specifies the value for the vec2 uniform.
        void setUniform(const std::string& name, const glsl::Vec2& vector);

        // Specifies the value for the vec3 uniform.
        void setUniform(const std::string& name, const glsl::Vec3& vector);

        // Specifies the value for the vec4 uniform.
        // This overload can also be called with jlib::Color objects
        // that are converted to jlib::glsl::Vec4.
        // It is important to note that the components of the color are
        // normalized before being passed to the shader. Therefore,
        // they are converted from range [0 .. 255] to range [0 .. 1].
        // For example, a jlib::Color(255, 127, 0, 255) will be transformed
        // to a vec4(1.0, 0.5, 0.0, 1.0) in the shader.
        void setUniform(const std::string& name, const glsl::Vec4& vector);

        // Specifies the value forthe int uniform.
        void setUniform(const std::string& name, int x);

        // Specifies the value for the ivec2 uniform.
        void setUniform(const std::string& name, const glsl::Ivec2& vector);

        // Specifies the value for the ivec3 uniform.
        void setUniform(const std::string& name, const glsl::Ivec3& vector);

        // Specifies the value for the ivec4 uniform.
        // This overload can also be called with jlib::Color objects
        // that are converted to jlib::Glsl::Ivec4.
        // If color conversions are used, the ivec4 uniform in GLSL
        // will hold the same values as the original jlib::Color
        // instance. For example, jlib::Color(255, 127, 0, 255) is
        // mapped to ivec4(255, 127, 0, 255).
        void setUniform(const std::string& name, const glsl::Ivec4& vector);

        // Specifies the value for the bool uniform.
        void setUniform(const std::string& name, bool x);

        // Specifies the value for the bvec2 uniform.
        void setUniform(const std::string& name, const glsl::Bvec2& vector);

        // Specifies the value for the bvec3 uniform.
        void setUniform(const std::string& name, const glsl::Bvec3& vector);

        // Specifies the value for the bvec4 uniform.
        void setUniform(const std::string& name, const glsl::Bvec4& vector);

        // Specifies the value for the mat3 matrix.
        void setUniform(const std::string& name, const glsl::Mat3& matrix);

        // Specifies the value for the mat4 matrix.
        void setUniform(const std::string& name, const glsl::Mat4& matrix);

        // Specifies a texture as the sampler2D uniform.
        // name is the name of the variable to change in the shader.
        // The corresponding parameter in the shader must be a 2D texture.
        void setUniform(const std::string& name, const Texture& texture);

        // Specifies current texture as the sampler2D uniform.x
        // This overload maps a shader texture variable to the
        // texture of the object being drawn, which cannot be
        // known in advance. The second argument must be
        // jlib::Shader::CurrentTexture.
        // The corresponding parameter in the shader must be a 2D texture.
        void setUniform(const std::string& name, CurrentTextureType);

        // Specifies values for the float[] array uniform.
        void setUniformArray(const std::string& name, const float* scalarArray, std::size_t length);

        // Specifies values for the vec2[] array uniform.
        void setUniformArray(const std::string& name, const glsl::Vec2* vectorArray, std::size_t length);

        // Specifies values for the vec3[] array uniform.
        void setUniformArray(const std::string& name, const glsl::Vec3* vectorArray, std::size_t length);

        // Specifies values for the vec4[] array uniform.
        void setUniformArray(const std::string& name, const glsl::Vec4* vectorArray, std::size_t length);

        // Specifies values for the mat3[] array uniform.
        void setUniformArray(const std::string& name, const glsl::Mat3* matrixArray, std::size_t length);

        // Specifies values for the mat4[] array uniform.
        void setUniformArray(const std::string& name, const glsl::Mat4* matrixArray, std::size_t length);

        // Gets the underlying OpenGL handle of the shader.
        // You shouldn't need to use this function, unless you have
        // very specific stuff to implement that the JLibrary doesn't 
        // support, or implement a temporary workaround until a bug is fixed.
        // Returns 0 if not yet loaded.
        u32 getNativeHandle() const;

        // Binds a shader for rendering.
        // This function is not part of the graphics API, it mustn't be
        // used when drawing JLibrary entities. It must be used only if you
        // mix jlib::Shader with OpenGL code.
        static void bind(const Shader* shader);

        // Returns true if the system supports shaders.
        /// This function should always be called before using
        /// the shader features. If it returns false, then
        /// any attempt to use a jlib::Shader will fail.
        static bool isAvailable();

        // Returns true if geometry shaders are supported.
        // This function should always be called before using
        // the geometry shader features. If it returns false, then
        // any attempt to use sf::Shader geometry shader features will fail.
        // This function can only return true if isAvailable() would also
        // return true, since shaders in general have to be supported in
        // order for geometry shaders to be supported as well.
        // Note: The first call to this function, whether by your
        // code or the JLibrary will result in a context switch.
        static bool isGeometryAvailable();
	};
}