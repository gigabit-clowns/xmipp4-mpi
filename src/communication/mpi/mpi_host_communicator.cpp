// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_communicator.hpp"

#include "mpi_error.hpp"

#include <xmipp4/core/logger.hpp>

#include <stdexcept>

namespace xmipp4 
{
namespace communication
{

mpi_host_communicator::mpi_host_communicator() noexcept
	: mpi_host_communicator(MPI_COMM_NULL)
{
}

mpi_host_communicator::mpi_host_communicator(
	MPI_Comm mpi_host_communicator
) noexcept
	: m_communicator(mpi_host_communicator)
{
}

mpi_host_communicator::~mpi_host_communicator()
{
	if (m_communicator != MPI_COMM_NULL && m_communicator != MPI_COMM_WORLD)
	{
		const auto error = MPI_Comm_free(&m_communicator);
		if (error != MPI_SUCCESS)
		{
			XMIPP4_LOG_ERROR(
				"Error destroying MPI Communicator: {}",
				error
			);
		}
	}
}

MPI_Comm mpi_host_communicator::get_handle() noexcept
{
	return m_communicator;   
}

std::size_t mpi_host_communicator::get_size() const
{
	int result;
	
	const auto error = MPI_Comm_size(m_communicator, &result);
	mpi_check_error(error);

	return result;
}

std::size_t mpi_host_communicator::get_rank() const
{
	int result;
	
	const auto error = MPI_Comm_rank(m_communicator, &result);
	mpi_check_error(error);

	return result;
}

std::shared_ptr<host_communicator> 
mpi_host_communicator::split(int colour, int rank_priority) const
{
	MPI_Comm new_communicator;

	const auto error = MPI_Comm_split(
		m_communicator,
		colour, rank_priority,
		&new_communicator
	);
	mpi_check_error(error);

	try
	{
		return std::make_shared<mpi_host_communicator>(new_communicator);
	}
	catch(...)
	{
		// Error ocurred creating a the new communicator.
		// Free the resources before propagating the error.
		MPI_Comm_free(&new_communicator);
		throw;
	}
}

void mpi_host_communicator::barrier()
{
	const auto error = MPI_Barrier(m_communicator);
	mpi_check_error(error);
}

} // namespace communication
} // namespace xmipp4
