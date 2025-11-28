// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "mpi_host_operation.hpp"

namespace xmipp4 
{
namespace communication
{

/**
 * @brief Implementation of the receive operation.
 * 
 */
class mpi_host_receive_operation final
	: public mpi_host_operation
{
public:
	explicit mpi_host_receive_operation(
		MPI_Comm communicator,
		void *data, 
		int count, 
		MPI_Datatype datatype, 
		int source, 
		int tag
	) noexcept;
	~mpi_host_receive_operation() override = default;

	void execute() override;

private:
	void *m_data;
	int m_count;
	MPI_Datatype m_datatype;
	int m_source;
	int m_tag;

};

} // namespace communication
} // namespace xmipp4
