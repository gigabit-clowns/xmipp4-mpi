// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_host_communicator.hpp"

#include <xmipp4/core/communication/host_duplex_region.hpp>
#include <xmipp4/core/communication/host_receive_region.hpp>
#include <xmipp4/core/communication/host_send_region.hpp>

#include "mpi_error.hpp"
#include "mpi_datatype.hpp"
#include "mpi_reduction.hpp"
#include "mpi_host_operations/mpi_host_send_operation.hpp"
#include "mpi_host_operations/mpi_host_receive_operation.hpp"
#include "mpi_host_operations/mpi_host_broadcast_operation.hpp"
#include "mpi_host_operations/mpi_host_reduce_operation.hpp"
#include "mpi_host_operations/mpi_host_all_reduce_operation.hpp"
#include "mpi_host_operations/mpi_host_gather_operation.hpp"
#include "mpi_host_operations/mpi_host_all_gather_operation.hpp"
#include "mpi_host_operations/mpi_host_scatter_operation.hpp"
#include "mpi_host_operations/mpi_host_barrier_operation.hpp"

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
	const host_send_region &region,
	int destination_rank,
	int tag
)
{
	const auto datatype = to_mpi_datatype(region.get_data_type());
	validate_mpi_datatype(datatype);
	validate_peer_rank(destination_rank);

	return std::make_shared<mpi_host_send_operation>(
		m_communicator,
		region.get_data(),
		region.get_count(),
		datatype,
		destination_rank,
		tag
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_receive(
	const host_receive_region &region,
	int source_rank,
	int tag
)
{
	const auto datatype = to_mpi_datatype(region.get_data_type());
	validate_mpi_datatype(datatype);
	validate_peer_rank(source_rank);

	return std::make_shared<mpi_host_receive_operation>(
		m_communicator,
		region.get_data(),
		region.get_count(),
		datatype,
		source_rank,
		tag
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_broadcast(
	const host_duplex_region &region,
	int root_rank
)
{
	const auto datatype = to_mpi_datatype(region.get_data_type());
	validate_mpi_datatype(datatype);
	validate_root_rank(root_rank);

	return std::make_shared<mpi_host_broadcast_operation>(
		m_communicator,
		region.get_send_data(),
		region.get_receive_data(),
		region.get_count(),
		datatype,
		root_rank
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_reduce(
	const host_duplex_region &region,
	reduction_operation reduction,
	int root_rank
)
{
	const auto datatype = to_mpi_datatype(region.get_data_type());
	const auto op = to_mpi_reduction(reduction);
	validate_mpi_datatype(datatype);
	validate_mpi_reduction(op);
	validate_root_rank(root_rank);

	return std::make_shared<mpi_host_reduce_operation>(
		m_communicator,
		region.get_send_data(),
		region.get_receive_data(),
		region.get_count(),
		datatype,
		op,
		root_rank
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_all_reduce(
	const host_duplex_region &region,
	reduction_operation reduction
)
{
	const auto datatype = to_mpi_datatype(region.get_data_type());
	const auto op = to_mpi_reduction(reduction);
	validate_mpi_datatype(datatype);
	validate_mpi_reduction(op);

	return std::make_shared<mpi_host_all_reduce_operation>(
		m_communicator,
		region.get_send_data(),
		region.get_receive_data(),
		region.get_count(),
		datatype,
		op
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_gather(
	const host_send_region &send_region,
	const host_receive_region &recv_region,
	int root_rank
)
{
	validate_root_rank(root_rank);
	const auto send_datatype = to_mpi_datatype(send_region.get_data_type());
	validate_mpi_datatype(send_datatype);
	const auto recv_datatype = to_mpi_datatype(recv_region.get_data_type());
	validate_mpi_datatype(recv_datatype);

	// TODO handle receive pointer division
	return std::make_shared<mpi_host_gather_operation>(
		m_communicator,
		send_region.get_data(),
		send_region.get_count(),
		send_datatype,
		recv_region.get_data(),
		recv_region.get_count(),
		recv_datatype,
		root_rank
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_all_gather(
	const host_send_region &send_region,
	const host_receive_region &recv_region
)
{
	const auto send_datatype = to_mpi_datatype(send_region.get_data_type());
	validate_mpi_datatype(send_datatype);
	const auto recv_datatype = to_mpi_datatype(recv_region.get_data_type());
	validate_mpi_datatype(recv_datatype);

	// TODO handle receive pointer division
	return std::make_shared<mpi_host_all_gather_operation>(
		m_communicator,
		send_region.get_data(),
		send_region.get_count(),
		send_datatype,
		recv_region.get_data(),
		recv_region.get_count(),
		recv_datatype
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_scatter(
	const host_send_region &send_region,
	const host_receive_region &recv_region,
	int root_rank
)
{
	validate_root_rank(root_rank);
	const auto send_datatype = to_mpi_datatype(send_region.get_data_type());
	validate_mpi_datatype(send_datatype);
	const auto recv_datatype = to_mpi_datatype(recv_region.get_data_type());
	validate_mpi_datatype(recv_datatype);

	// TODO handle receive pointer division
	return std::make_shared<mpi_host_scatter_operation>(
		m_communicator,
		send_region.get_data(),
		send_region.get_count(),
		send_datatype,
		recv_region.get_data(),
		recv_region.get_count(),
		recv_datatype,
		root_rank
	);
}

std::shared_ptr<host_operation> mpi_host_communicator::create_barrier()
{
	return std::make_shared<mpi_host_barrier_operation>(m_communicator);
}

void mpi_host_communicator::validate_root_rank(int root_rank)
{
	if (root_rank >= static_cast<int>(get_size()))
	{
		throw std::out_of_range("The root_rank is out of bounds");
	}
}

void mpi_host_communicator::validate_peer_rank(int peer_rank)
{
	if (peer_rank >= static_cast<int>(get_size()))
	{
		throw std::out_of_range("The peer's rank is out of bounds");
	}

	if (peer_rank == static_cast<int>(get_rank()))
	{
		throw std::invalid_argument(
			"The peer's rank can not be equal to the self rank"
		);
	}
}

} // namespace communication
} // namespace xmipp4
