// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_receive_operation.hpp"

#include "../mpi_error.hpp"

namespace xmipp4 
{
namespace communication
{

mpi_host_receive_operation::mpi_host_receive_operation(
	MPI_Comm communicator,
	void *data, 
	int count, 
	MPI_Datatype datatype, 
	int source, 
	int tag
) noexcept
	: mpi_host_operation(communicator)
	, m_data(data)
	, m_count(count)
	, m_datatype(datatype)
	, m_source(source)
	, m_tag(tag)
{
}

void mpi_host_receive_operation::execute()
{
	MPI_Status status;
	const auto err = MPI_Recv(
		m_data,
		m_count,
		m_datatype,
		m_source,
		m_tag,
		get_communicator(),
		&status
	);
	mpi_check_error(err);
}

} // namespace communication
} // namespace xmipp4
