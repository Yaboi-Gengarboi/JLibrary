// JLibraryDevelopment
// PrimitiveType.hpp
// Created on 2021-07-05 by Justyn Durnford
// Last modified on 2021-07-05 by Justyn Durnford
// Header file for the PrimitiveType enum.

#pragma once

namespace jlib
{
	// Types of primitives that a jlib::VertexArray can render.
	// Points and lines have no area, therefore their thickness
	// will always be 1 pixel, regardless the current transform
	// and view.
    enum PrimitiveType
    {
        Points,        
        Lines,         
        LineStrip,     
        Triangles,     
        TriangleStrip, 
        TriangleFan,   
        Quads
    };
}