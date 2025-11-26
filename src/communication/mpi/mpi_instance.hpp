// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_host_communicator.hpp"

#include <xmipp4/core/version.hpp>

#include <memory>

namespace xmipp4 
{
namespace communication
{

class mpi_instance
{
public:
	mpi_instance(const mpi_instance &other) = delete;
	mpi_instance(mpi_instance &&other) = delete;
	~mpi_instance();

	mpi_instance& operator=(const mpi_instance &other) = delete;
	mpi_instance& operator=(mpi_instance &&other) = delete;

	const std::shared_ptr<mpi_host_communicator>& 
	get_world_communicator() const noexcept;

	static std::shared_ptr<mpi_instance> get();
	static version get_mpi_version();

private:
	std::shared_ptr<mpi_host_communicator> m_world;

	static std::weak_ptr<mpi_instance> m_singleton;
	
	mpi_instance();
};

} // namespace communication
} // namespace xmipp4
