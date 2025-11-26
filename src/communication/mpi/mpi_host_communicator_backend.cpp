// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_communicator_backend.hpp"

#include "mpi_instance.hpp"
#include "mpi_host_communicator.hpp"

#include <xmipp4/core/communication/host_communicator_manager.hpp>

namespace xmipp4 
{
namespace communication
{

std::string mpi_host_communicator_backend::get_name() const noexcept
{
	return "mpi";
}

version mpi_host_communicator_backend::get_version() const noexcept
{
	return mpi_instance::get_mpi_version();
}

backend_priority mpi_host_communicator_backend::get_suitability() const noexcept
{
	return backend_priority::normal;
}

std::shared_ptr<host_communicator> 
mpi_host_communicator_backend::create_world_communicator() const
{
	return get_instance().get_world_communicator();
}

bool mpi_host_communicator_backend::register_at(host_communicator_manager &manager)
{
	return manager.register_backend(
		std::make_unique<mpi_host_communicator_backend>()
	);
}

mpi_instance& mpi_host_communicator_backend::get_instance() const
{
	if (!m_instance)
	{
		m_instance = mpi_instance::get();
	}

	XMIPP4_ASSERT(m_instance);
	return *m_instance;
}

} // namespace communication
} // namespace xmipp4
