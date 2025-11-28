// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/numerical_type.hpp>

#include <mpi.h>


namespace xmipp4 
{
namespace communication
{

MPI_Datatype to_mpi_datatype(numerical_type type) noexcept;

void validate_mpi_datatype(MPI_Datatype type);

} // namespace communication
} // namespace xmipp4

