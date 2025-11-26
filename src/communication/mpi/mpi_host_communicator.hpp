// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/communication/host_communicator.hpp>
#include <xmipp4/core/span.hpp>
#include <xmipp4/core/memory/byte.hpp>

#include <memory>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

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

	void barrier() override;

private:
	MPI_Comm m_communicator;
};

} // namespace communication
} // namespace xmipp4
