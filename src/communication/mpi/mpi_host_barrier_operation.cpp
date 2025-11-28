// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_barrier_operation.hpp"

#include "mpi_error.hpp"

namespace xmipp4 
{
namespace communication
{

mpi_host_barrier_operation::mpi_host_barrier_operation(
	MPI_Comm communicator
) noexcept
	: mpi_host_operation(communicator)
{
}

void mpi_host_barrier_operation::execute()
{
	const auto err = MPI_Barrier(get_communicator());
	mpi_check_error(err);
}

} // namespace communication
} // namespace xmipp4
