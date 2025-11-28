// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_reduction.hpp"

#include <stdexcept>

namespace xmipp4 
{
namespace communication
{

MPI_Op to_mpi_reduction(reduction_operation operation) noexcept
{
	switch (operation)
	{
	case reduction_operation::sum: return MPI_SUM;
	case reduction_operation::product: return MPI_PROD;
	case reduction_operation::min: return MPI_MIN;
	case reduction_operation::max: return MPI_MAX;
	default: return 0;
	}
}

void validate_mpi_reduction(MPI_Op operation)
{
	if (operation == 0)
	{
		throw std::invalid_argument(
			"Provided reduction operation is not supported"
		);
	}
}

} // namespace communication
} // namespace xmipp4
