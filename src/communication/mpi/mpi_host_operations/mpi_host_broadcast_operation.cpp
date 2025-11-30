// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_broadcast_operation.hpp"

#include "../mpi_error.hpp"

#include <cstring>

namespace xmipp4 
{
namespace communication
{

mpi_host_broadcast_operation::mpi_host_broadcast_operation(
	MPI_Comm communicator,
	const void *send_data, 
	void *receive_data, 
	int count, 
	MPI_Datatype datatype, 
	int root_rank 
) noexcept
	: mpi_host_operation(communicator)
	, m_send_data(send_data)
	, m_receive_data(receive_data)
	, m_count(count)
	, m_datatype(datatype)
	, m_root_rank(root_rank)
{
}

void mpi_host_broadcast_operation::execute()
{
	if (m_send_data && m_receive_data && m_send_data != m_receive_data)
	{
		// Broadcast is always in-place. Copy if different send and receive
		// buffers were provided.
		int item_size;
		const auto err = MPI_Type_size(m_datatype, &item_size);
		mpi_check_error(err);
		const auto byte_count = item_size * m_count;
		std::memcpy(m_receive_data, m_send_data, byte_count);
	}

	const auto err = MPI_Bcast(
		m_receive_data,
		m_count,
		m_datatype,
		m_root_rank,
		get_communicator()
	);
	mpi_check_error(err);
}

} // namespace communication
} // namespace xmipp4
