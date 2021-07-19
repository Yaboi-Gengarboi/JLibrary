// JLibraryDevelopment
// GlResource.cpp
// Created on 2021-07-01 by Justyn Durnford
// Last modified on 2021-07-12 by Justyn Durnford
// Source file for the GlResource class.

#include <JLibrary/Graphics/GlContext.hpp>
#include <JLibrary/Graphics/GlResource.hpp>
using namespace jlib;

GlResource::GlResource()
{
    GlContext::initResource();
}

GlResource::~GlResource()
{
    GlContext::cleanupResource();
}

void GlResource::registerContextDestroyCallback(ContextDestroyCallback callback, void* arg)
{
    GlContext::registerContextDestroyCallback(callback, arg);
}

GlResource::TransientContextLock::TransientContextLock()
{
    GlContext::acquireTransientContext();
}

GlResource::TransientContextLock::~TransientContextLock()
{
    GlContext::releaseTransientContext();
}