// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_host_operation.hpp"

namespace xmipp4 
{
namespace communication
{

/**
 * @brief Implementation of the scatter operation.
 * 
 */
class mpi_host_scatter_operation final
	: public mpi_host_operation
{
public:
	explicit mpi_host_scatter_operation(
		MPI_Comm communicator,
		const void *send_data, 
		int send_count,
		MPI_Datatype send_datatype, 
		void *receive_data, 
		int receive_count,
		MPI_Datatype receive_datatype, 
		int root_rank
	) noexcept;
	~mpi_host_scatter_operation() override = default;

	void execute() override;

private:
	const void *m_send_data;
	int m_send_count;
	MPI_Datatype m_send_datatype;
	void *m_receive_data;
	int m_receive_count;
	MPI_Datatype m_receive_datatype;
	int m_root_rank;

};

} // namespace communication
} // namespace xmipp4
