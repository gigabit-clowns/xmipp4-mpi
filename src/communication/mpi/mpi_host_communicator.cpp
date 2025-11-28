// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_communicator.hpp"

#include "mpi_error.hpp"
#include "mpi_host_barrier_operation.hpp"

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
		// Error occurred creating a the new communicator.
		// Free the resources before propagating the error.
		MPI_Comm_free(&new_communicator);
		throw;
	}
}

std::shared_ptr<host_operation> mpi_host_communicator::create_send(
	const host_send_region &buffer,
	int destination_rank,
	int tag
)
{
	validate_peer_rank(destination_rank);

}

std::shared_ptr<host_operation> mpi_host_communicator::create_receive(
	const host_receive_region &region,
	int source_rank,
	int tag
)
{
	validate_peer_rank(source_rank);

}

std::shared_ptr<host_operation> mpi_host_communicator::create_broadcast(
	const host_duplex_region &region,
	int root_rank
)
{
	validate_root_rank(root_rank);

}

std::shared_ptr<host_operation> mpi_host_communicator::create_reduce(
	const host_duplex_region &region,
	reduction_operation reduction,
	int root_rank
)
{
	validate_root_rank(root_rank);

}

std::shared_ptr<host_operation> mpi_host_communicator::create_all_reduce(
	const host_duplex_region &region,
	reduction_operation reduction
)
{

}

std::shared_ptr<host_operation> mpi_host_communicator::create_gather(
	const host_send_region &send_region,
	const host_receive_region &recv_region,
	int root_rank
)
{
	validate_root_rank(root_rank);

}

std::shared_ptr<host_operation> mpi_host_communicator::create_all_gather(
	const host_send_region &send_region,
	const host_receive_region &recv_region
)
{

}

std::shared_ptr<host_operation> mpi_host_communicator::create_scatter(
	const host_send_region &send_region,
	const host_receive_region &recv_region,
	int root_rank
)
{
	validate_root_rank(root_rank);

}

std::shared_ptr<host_operation> mpi_host_communicator::create_barrier()
{
	return std::make_shared<mpi_host_barrier_operation>();
}

} // namespace communication
} // namespace xmipp4
