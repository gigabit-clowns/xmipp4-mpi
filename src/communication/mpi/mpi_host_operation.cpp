// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_operation.hpp"

namespace xmipp4 
{
namespace communication
{

mpi_host_operation::mpi_host_operation(MPI_Comm communicator) noexcept
	: m_communicator(communicator)
{
}

MPI_Comm mpi_host_operation::get_communicator() const noexcept
{
	return m_communicator;
}

} // namespace communication
} // namespace xmipp4
