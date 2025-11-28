// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/communication/reduction_operation.hpp>

#include <mpi.h>


namespace xmipp4 
{
namespace communication
{

MPI_Op to_mpi_reduction(reduction_operation operation) noexcept;

void validate_mpi_reduction(MPI_Op operation);

} // namespace communication
} // namespace xmipp4

