// SPDX-License-Identifier: GPL-3.0-only

#include <catch2/catch_test_macros.hpp>

#include <xmipp4/core/service_catalog.hpp>
#include <xmipp4/core/plugin_manager.hpp>
#include <xmipp4/core/plugin.hpp>
#include <xmipp4/core/communication/host_communicator_manager.hpp>
#include <xmipp4/core/platform/operating_system.h>

using namespace xmipp4;


static std::string get_mpi_plugin_path()
{
    #if XMIPP4_WINDOWS
        return "xmipp4-mpi.dll";
    #elif XMIPP4_APPLE || XMIPP4_LINUX
        return "./libxmipp4-mpi.so";
    #else
        #error "Unknown platform"
    #endif
}

/* TODO
TEST_CASE( "load and register xmipp4-mpi plugin", "[mpi]" ) 
{
    plugin_manager manager;

    const auto* mpi_plugin = 
        manager.load_plugin(get_mpi_plugin_path());

    REQUIRE( mpi_plugin != nullptr );
    REQUIRE( mpi_plugin->get_name() == "xmipp4-mpi" );

    service_catalog interfaces;
    mpi_plugin->register_at(interfaces);

    auto *mpi_backend =
        interfaces.get_service_manager<communication::host_communicator_manager>()
        .get_backend("mpi");
    REQUIRE( mpi_backend != nullptr );
    REQUIRE( mpi_backend->get_name() == "mpi" );
}
*/ 
