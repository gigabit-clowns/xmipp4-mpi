// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_host_operation.hpp"

namespace xmipp4 
{
namespace communication
{

/**
 * @brief Implementation of the barrier operation.
 * 
 */
class mpi_host_barrier_operation final
	: public mpi_host_operation
{
public:
	explicit mpi_host_barrier_operation(MPI_Comm communicator) noexcept;
	~mpi_host_barrier_operation() override = default;

	void execute() override;

};

} // namespace communication
} // namespace xmipp4
