// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_send_operation.hpp"

#include "mpi_error.hpp"

namespace xmipp4 
{
namespace communication
{

mpi_host_send_operation::mpi_host_send_operation(
	MPI_Comm communicator,
	const void *data, 
	int count, 
	MPI_Datatype datatype, 
	int destination, 
	int tag
) noexcept
	: mpi_host_operation(communicator)
	, m_data(data)
	, m_count(count)
	, m_datatype(datatype)
	, m_destination(destination)
	, m_tag(tag)
{
}

void mpi_host_send_operation::execute()
{
	const auto err = MPI_Send(
		m_data,
		m_count,
		m_datatype,
		m_destination,
		m_tag,
		get_communicator()
	);
	mpi_check_error(err);
}

} // namespace communication
} // namespace xmipp4
