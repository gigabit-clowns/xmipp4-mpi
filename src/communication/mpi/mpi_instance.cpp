// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_instance.hpp"

#include "mpi_error.hpp"

#include <xmipp4/core/platform/assert.hpp>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

std::weak_ptr<mpi_instance> mpi_instance::m_singleton;

mpi_instance::mpi_instance()
{
    const auto error = MPI_Init(nullptr, nullptr);
    mpi_check_error(error);
    
    m_world = std::make_shared<mpi_host_communicator>(MPI_COMM_WORLD);
}

mpi_instance::~mpi_instance()
{
    MPI_Finalize();
}

const std::shared_ptr<mpi_host_communicator>& 
mpi_instance::get_world_communicator() const noexcept
{
    return m_world;
}

std::shared_ptr<mpi_instance> mpi_instance::get()
{
    auto result = m_singleton.lock();

    if(!result)
    {
        result.reset(new mpi_instance());
        m_singleton = result;
    }

    XMIPP4_ASSERT(result);
    return result;

}

version mpi_instance::get_mpi_version()
{
    int major = 0;
    int minor = 0;
    MPI_Get_version(&major, &minor); // Does not require initialization
    return version(major, minor, 0);
}

} // namespace communication
} // namespace xmipp4
