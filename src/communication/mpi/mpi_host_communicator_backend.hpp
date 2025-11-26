// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_instance.hpp"

#include <xmipp4/core/communication/host_communicator_backend.hpp>

#include <memory>

namespace xmipp4 
{
namespace communication
{

class host_communicator_manager;
class mpi_host_communicator;

class mpi_host_communicator_backend final
	: public host_communicator_backend
{
public:
	mpi_host_communicator_backend() = default;
	mpi_host_communicator_backend(
		const mpi_host_communicator_backend &other
	) = delete;
	mpi_host_communicator_backend(
		mpi_host_communicator_backend &&other
	) = delete;
	~mpi_host_communicator_backend() override = default;

	mpi_host_communicator_backend&
	operator=(const mpi_host_communicator_backend &other) = delete;
	mpi_host_communicator_backend&
	operator=(mpi_host_communicator_backend &&other) = delete;

	std::string get_name() const noexcept override;
	version get_version() const noexcept override;
	backend_priority get_suitability() const noexcept override;
	std::shared_ptr<host_communicator> 
	create_world_communicator() const override;

	static bool register_at(host_communicator_manager &manager);

private:
	mutable std::shared_ptr<mpi_instance> m_instance;

	mpi_instance& get_instance() const;
};

} // namespace communication
} // namespace xmipp4
