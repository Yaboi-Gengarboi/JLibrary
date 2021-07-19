// JLibraryDevelopment
// Context.cpp
// Created on 2021-07-11 by Justyn Durnford
// Last modified on 2021-07-12 by Justyn Durnford
// Source file for the Context class.

#include <JLibrary/Graphics/Context.hpp>
#include <JLibrary/Multithread/ThreadLocalPtr.hpp>
using namespace jlib;

namespace
{
    // This per-thread variable holds the last activated sf::Context for each thread.
    ThreadLocalPtr<Context> currentContext(nullptr);
}

Context::Context()
{
    context_ = GlContext::create();
}

Context::~Context()
{
    setActive(false);
    delete context_;
}

bool Context::setActive(bool active)
{
    bool result = context_->setActive(active);

    if (result)
        currentContext = (active ? this : nullptr);

    return result;
}

const ContextSettings& Context::settings() const
{
    return context_->settings();
}

bool Context::isExtensionAvailable(const char* name)
{
    return GlContext::isExtensionAvailable(name);
}

GlFunctionPointer Context::getFunction(const char* name)
{
    return GlContext::getFunction(name);
}

const Context* Context::getActiveContext()
{
    // We have to check that the last activated jlib::Context is still active 
    // (a RenderTarget activation may have deactivated it).
    if (currentContext && currentContext->context_ == GlContext::getActiveContext())
        return currentContext;
    else
        return nullptr;
}

u64 Context::getActiveContextId()
{
    return GlContext::getActiveContextId();
}

Context::Context(const ContextSettings& settings, u32 width, u32 height)
{
    context_ = GlContext::create(settings, width, height);
    setActive(true);
}