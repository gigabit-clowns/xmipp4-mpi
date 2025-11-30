// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/numerical_type.hpp>
#include <xmipp4/core/communication/reduction_operation.hpp>

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

MPI_Datatype to_mpi_datatype(numerical_type type) noexcept;

MPI_Op to_mpi_op(reduction_operation operation) noexcept;

} // namespace communication
} // namespace xmipp4

