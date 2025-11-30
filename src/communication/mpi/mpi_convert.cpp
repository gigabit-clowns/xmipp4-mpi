// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_convert.hpp"

namespace xmipp4 
{
namespace communication
{

MPI_Datatype to_mpi_datatype(numerical_type type) noexcept
{
	static_assert(sizeof(float) == 4, "4 byte float assumption is not met");
	static_assert(sizeof(double) == 8, "8 byte double assumption is not met");

	switch (type)
	{
	case numerical_type::int8: return MPI_INT8_T;
	case numerical_type::uint8: return MPI_UINT8_T;
	case numerical_type::int16: return MPI_INT16_T;
	case numerical_type::uint16: return MPI_UINT16_T;
	case numerical_type::int32: return MPI_INT32_T;
	case numerical_type::uint32: return MPI_UINT32_T;
	case numerical_type::int64: return MPI_INT64_T;
	case numerical_type::uint64: return MPI_UINT64_T;
	//case numerical_type::float16: return 0; 
	//case numerical_type::brain_float16: return 0;
	case numerical_type::float32: return MPI_FLOAT;
	case numerical_type::float64: return MPI_DOUBLE;
	// case numerical_type::complex_float16: return 0;
	case numerical_type::complex_float32: return MPI_C_FLOAT_COMPLEX;
	case numerical_type::complex_float64: return MPI_C_DOUBLE_COMPLEX;
	default: return 0;
	}
}

MPI_Op to_mpi_op(reduction_operation operation) noexcept
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

} // namespace communication
} // namespace xmipp4
