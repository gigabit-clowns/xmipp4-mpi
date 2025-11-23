// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_plugin.hpp"
#include "communication/mpi/mpi_communicator_backend.hpp"

#include <xmipp4/core/service_catalog.hpp>
#include <xmipp4/core/communication/communicator_manager.hpp>

namespace xmipp4 
{

const std::string mpi_plugin::name = "xmipp4-mpi";

const std::string& mpi_plugin::get_name() const noexcept
{
    return name; 
}

version mpi_plugin::get_version() const noexcept
{
    return version(
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH
    );
}

void mpi_plugin::register_at(service_catalog& catalog) const
{
    auto& communicator_manager = 
        catalog.get_service_manager<communication::communicator_manager>();
    
    communication::mpi_communicator_backend::register_at(communicator_manager);
}

} // namespace xmipp4
