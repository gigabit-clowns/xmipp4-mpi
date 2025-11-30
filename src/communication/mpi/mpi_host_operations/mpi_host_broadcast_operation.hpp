// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_host_operation.hpp"

namespace xmipp4 
{
namespace communication
{

/**
 * @brief Implementation of the broadcast operation.
 * 
 */
class mpi_host_broadcast_operation final
	: public mpi_host_operation
{
public:
	explicit mpi_host_broadcast_operation(
		MPI_Comm communicator,
		const void *send_data, 
		void *receive_data, 
		int count, 
		MPI_Datatype datatype, 
		int root_rank
	) noexcept;
	~mpi_host_broadcast_operation() override = default;

	void execute() override;

private:
	const void *m_send_data;
	void *m_receive_data;
	int m_count;
	MPI_Datatype m_datatype;
	int m_root_rank;

};

} // namespace communication
} // namespace xmipp4
