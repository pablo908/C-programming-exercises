#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "Tarea1.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<Tarea1> reg(_T("Tarea1"));
}

// constructor
Tarea1::Tarea1()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("Tarea1.zip")))
    {
        NotifyMissingFile(_T("Tarea1.zip"));
    }
}

// destructor
Tarea1::~Tarea1()
{
}

void Tarea1::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

void Tarea1::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

int Tarea1::Execute()
{
    // do your magic ;)
    NotImplemented(_T("Tarea1::Execute()"));
    return -1;
}
