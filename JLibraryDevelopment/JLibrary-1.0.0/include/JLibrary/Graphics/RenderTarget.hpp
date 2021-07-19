// JLibraryDevelopment
// RenderTarget.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-17 by Justyn Durnford
// Header file for the RenderTarget class.

#pragma once

#include <JLibrary/Graphics/BlendMode.hpp>
#include <JLibrary/Graphics/Color.hpp>
#include <JLibrary/Graphics/PrimitiveType.hpp>
#include <JLibrary/Graphics/Vertex2.hpp>
#include <JLibrary/Graphics/VertexBuffer.hpp>
#include <JLibrary/Window/View.hpp>
#include <bitset>

namespace jlib
{
	// Base class for all render targets.
	class RenderTarget : NonCopyable
	{
        struct StatesCache
        {
            static const i32 VertexCacheSize = 4;

            u64 lastTextureID;
            BlendMode lastBlendMode;
            std::array<Vertex2, VertexCacheSize> vertexCache;

            // Flags:
            // - [0]: isCacheEnabled
            // - [1]: areGLStatesSet
            // - [2]: hasViewChanged
            // - [3]: isTextureCoordinateArrayEnabled
            // - [4]: useVertexCache
            std::bitset<5> flags;
        };

        View        defaultView_; 
        View        view_;        
        StatesCache cache_;       
        u64         id_;          

        // Applies the current view.
        void applyCurrentView();

        // Applies a new blending mode.
        void applyBlendMode(const BlendMode& mode);

        // Applies a new transformation.
        void applyTransform(const Transformation& transform);

        // Applies a new texture.
        void applyTexture(const Texture* texture);

        // Applies a new shader.
        void applyShader(const Shader* shader);

        // Sets up the environment for drawing.
        void setupDraw(bool useVertexCache, const RenderStates& states);

        // Draw the primitives.
        void drawPrimitives(PrimitiveType type, std::size_t firstVertex, std::size_t vertexCount);

        // Clean up environment after drawing.
        void cleanupDraw(const RenderStates& states);

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        protected:

        // Default constructor.
        RenderTarget();

        // Performs the common initialization step after creation.
        // Derived classes must call this function after the
        // target is created and ready for drawing.
        void initialize();

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

        public:

        // Destructor.
        virtual ~RenderTarget();

        // Clears the entire target with a single color.
        // This function is usually called once every frame,
        // to clear the previous contents of the target.
        void clear(const Color& color = Color(0, 0, 0, 255));

        // Changes the current active view.
        // The view is like a 2D camera, it controls which part of
        // the 2D scene is visible, and how it is viewed in the
        // render target.
        // The new view will affect everything that is drawn, until
        // another view is set.
        // The render target keeps its own copy of the view object,
        // so it is not necessary to keep the original one alive
        // after calling this function.
        // To restore the original view of the target, you can pass
        // the result of getDefaultView() to this function.
        void setView(const View& view);

        // Gets the view currently in use in the render target.
        const View& getView() const;

        // Gets the default view of the render target.
        // The default view has the initial size of the render target,
        // and never changes after the target has been created.
        const View& getDefaultView() const;

        // Gets the viewport of a view applied to this render target.
        // The viewport is defined in the view as a ratio, this function
        // simply applies this ratio to the current dimensions of the
        // render target to calculate the pixels rectangle that the viewport
        // actually covers in the target.
        IntRect getViewport(const View& view) const;

        // Converts a point from target coordinates to world
        // coordinates, using the current view.
        // This function is an overload of the mapPixelToCoords
        // function that implicitly uses the current view.
        Point2f mapPixelToCoords(const Point2i& point) const;

        // Converts a point from target coordinates to world coordinates.
        // This function finds the 2D position that matches the
        // given pixel of the render target. In other words, it does
        // the inverse of what the graphics card does, to find the
        // initial position of a rendered pixel.
        // Initially, both coordinate systems (world units and target pixels)
        // match perfectly. But if you define a custom view or resize your
        // render target, this assertion is not true anymore, i.e. a point
        // located at (10, 50) in your render target may map to the point
        // (150, 75) in your 2D world -- if the view is translated by (140, 25).
        // For render-windows, this function is typically used to find
        // which point (or object) is located below the mouse cursor.
        // This version uses a custom view for calculations, see the other
        // overload of the function if you want to use the current view of the
        // render target.
        Point2f mapPixelToCoords(const Point2i& point, const View& view) const;

        // Converts a point from world coordinates to target
        // coordinates, using the current view.
        // This function is an overload of the mapCoordsToPixel
        // function that implicitly uses the current view.
        Point2i mapCoordsToPixel(const Point2f& point) const;

        // Converts a point from world coordinates to target coordinates.
        // This function finds the pixel of the render target that matches
        // the given 2D point. In other words, it goes through the same process
        // as the graphics card, to compute the final position of a rendered point.
        // Initially, both coordinate systems (world units and target pixels)
        // match perfectly. But if you define a custom view or resize your
        // render target, this assertion is not true anymore, i.e. a point
        // located at (150, 75) in your 2D world may map to the pixel
        // (10, 50) of your render target -- if the view is translated by (140, 25).
        // This version uses a custom view for calculations, see the other
        // overload of the function if you want to use the current view of the
        // render target.
        Point2i mapCoordsToPixel(const Point2f& point, const View& view) const;

        // Draws a drawable object to the render target.
        void draw(const Drawable& drawable, const RenderStates& states = RenderStates::Default);

        // Draws primitives defined by an array of vertices.
        void draw(const Vertex2* vertices, std::size_t vertexCount,
                  PrimitiveType type, const RenderStates& states = RenderStates::Default);

        // Draws primitives defined by a vertex buffer.
        void draw(const VertexBuffer& vertexBuffer, const RenderStates& states = RenderStates::Default);

        // Draws primitives defined by a vertex buffer.
        void draw(const VertexBuffer& vertexBuffer, std::size_t firstVertex, 
                  std::size_t vertexCount, const RenderStates& states = RenderStates::Default);

        // Returns the width of the rendering region of the target.
        virtual u32 getWidth() const = 0;

        // Returns the height of the rendering region of the target.
        virtual u32 getHeight() const = 0;

        // Returns true if the render target will use sRGB encoding when drawing on it.
        virtual bool isSRGB() const;

        // Activates or deactivates the render target for rendering.
        // This function makes the render target's context current for
        // future OpenGL rendering operations (so you shouldn't care
        // about it if you're not doing direct OpenGL stuff).
        // A render target's context is active only on the current thread,
        // if you want to make it active on another thread you have
        // to deactivate it on the previous thread first if it was active.
        // Only one context can be current in a thread, so if you
        // want to draw OpenGL geometry to another render target
        // don't forget to activate it again. Activating a render
        // target will automatically deactivate the previously active
        // context (if any).
        // Returns true if the operation was successful.
        virtual bool setActive(bool active = true);

        // Saves the current OpenGL render states and matrices.
        // This function can be used when you mix SFML drawing
        // and direct OpenGL rendering. Combined with popGLStates,
        // it ensures that:
        //  - SFML's internal states are not messed up by your OpenGL code
        //  - your OpenGL states are not modified by a call to a SFML function
        // More specifically, it must be used around code that
        // calls Draw functions.
        // Note that this function is quite expensive: it saves all the
        // possible OpenGL states and matrices, even the ones you
        // don't care about. Therefore it should be used wisely.
        // It is provided for convenience, but the best results will
        // be achieved if you handle OpenGL states yourself (because
        // you know which states have really changed, and need to be
        // saved and restored). Take a look at the resetGLStates
        // function if you do so.
        void pushGLStates();

        // Restores the previously saved OpenGL render states and matrices.
        // See the description of pushGLStates to get a detailed
        // description of these functions.
        void popGLStates();

        // Resets the internal OpenGL states so that the target is ready for drawing.
        // This function can be used when you mix SFML drawing
        // and direct OpenGL rendering, if you choose not to use
        // pushGLStates/popGLStates. It makes sure that all OpenGL
        // states needed by SFML are set, so that subsequent draw()
        // calls will work as expected.
        void resetGLStates();
	};
}