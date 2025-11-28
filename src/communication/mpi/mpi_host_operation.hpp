// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/communication/host_operation.hpp>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

/**
 * @brief Base class for MPI operations.
 * 
 */
class mpi_host_operation
	: public host_operation
{
public:
	explicit mpi_host_operation(MPI_Comm communicator) noexcept;
	mpi_host_operation(const mpi_host_operation &other) = delete;
	mpi_host_operation(mpi_host_operation &&other) = delete;
	~mpi_host_operation() override = default;

	mpi_host_operation& operator=(
		const mpi_host_operation &other
	) = delete;
	mpi_host_operation& operator=(
		mpi_host_operation &&other
	) = delete;

	MPI_Comm get_communicator() const noexcept;

private:
	MPI_Comm m_communicator;

};

} // namespace communication
} // namespace xmipp4
