// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/communication/host_communicator.hpp>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

/**
 * @brief Implementation of the host_communicator interface using MPI.
 * 
 */
class mpi_host_communicator final
	: public host_communicator
{
public:
	mpi_host_communicator() noexcept;
	explicit mpi_host_communicator(MPI_Comm mpi_host_communicator) noexcept;
	mpi_host_communicator(const mpi_host_communicator &other) = delete;
	mpi_host_communicator(mpi_host_communicator &&other) = delete;
	~mpi_host_communicator() override;

	mpi_host_communicator& operator=(
		const mpi_host_communicator &other
	) = delete;
	mpi_host_communicator& operator=(
		mpi_host_communicator &&other
	) = delete;

	MPI_Comm get_handle() noexcept;

	std::size_t get_size() const override;

	std::size_t get_rank() const override;

	std::shared_ptr<host_communicator> split(
		int colour, 
		int rank_priority 
	) const override;

	std::shared_ptr<host_operation> create_send(
		const host_send_region &buffer,
		int destination_rank,
		int tag
	) override;

	std::shared_ptr<host_operation> create_receive(
		const host_receive_region &region,
		int source_rank,
		int tag
	) override;

	std::shared_ptr<host_operation> create_broadcast(
		const host_duplex_region &region,
		int root_rank
	) override;

	std::shared_ptr<host_operation> create_reduce(
		const host_duplex_region &region,
		reduction_operation reduction,
		int root_rank
	) override;

	std::shared_ptr<host_operation> create_all_reduce(
		const host_duplex_region &region,
		reduction_operation reduction
	) override;

	std::shared_ptr<host_operation> create_gather(
		const host_send_region &send_region,
		const host_receive_region &recv_region,
		int root_rank
	) override;

	std::shared_ptr<host_operation> create_all_gather(
		const host_send_region &send_region,
		const host_receive_region &recv_region
	) override;

	std::shared_ptr<host_operation> create_scatter(
		const host_send_region &send_region,
		const host_receive_region &recv_region,
		int root_rank
	) override;

	std::shared_ptr<host_operation> create_barrier() override;

private:
	MPI_Comm m_communicator;

	void validate_root_rank(int root_rank);
	void validate_peer_rank(int peer_rank);

};

} // namespace communication
} // namespace xmipp4
