// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_reduce_operation.hpp"

#include "../mpi_error.hpp"

#include <cstring>

namespace xmipp4 
{
namespace communication
{

mpi_host_reduce_operation::mpi_host_reduce_operation(
	MPI_Comm communicator,
	const void *send_data, 
	void *receive_data, 
	int count, 
	MPI_Datatype datatype, 
	MPI_Op op,
	int root_rank 
) noexcept
	: mpi_host_operation(communicator)
	, m_send_data(send_data)
	, m_receive_data(receive_data)
	, m_count(count)
	, m_datatype(datatype)
	, m_op(op)
	, m_root_rank(root_rank)
{
}

void mpi_host_reduce_operation::execute()
{
	const auto err = MPI_Reduce(
		m_send_data,
		m_receive_data,
		m_count,
		m_datatype,
		m_op,
		m_root_rank,
		get_communicator()
	);
	mpi_check_error(err);
}

} // namespace communication
} // namespace xmipp4
