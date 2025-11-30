// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_gather_operation.hpp"

#include "../mpi_error.hpp"

#include <cstring>

namespace xmipp4 
{
namespace communication
{

mpi_host_gather_operation::mpi_host_gather_operation(
	MPI_Comm communicator,
	const void *send_data, 
	int send_count,
	MPI_Datatype send_datatype, 
	void *receive_data, 
	int receive_count,
	MPI_Datatype receive_datatype, 
	int root_rank 
) noexcept
	: mpi_host_operation(communicator)
	, m_send_data(send_data)
	, m_send_count(send_count)
	, m_send_datatype(send_datatype)
	, m_receive_data(receive_data)
	, m_receive_count(receive_count)
	, m_receive_datatype(receive_datatype)
	, m_root_rank(root_rank)
{
}

void mpi_host_gather_operation::execute()
{
	const auto err = MPI_Gather(
		m_send_data,
		m_send_count,
		m_send_datatype,
		m_receive_data,
		m_receive_count,
		m_receive_datatype,
		m_root_rank,
		get_communicator()
	);
	mpi_check_error(err);
}

} // namespace communication
} // namespace xmipp4
