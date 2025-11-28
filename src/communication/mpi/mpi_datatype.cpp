// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_datatype.hpp"

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

void validate_mpi_datatype(MPI_Datatype type)
{
	if (type == 0)
	{
		throw std::invalid_argument("Provided data type is not supported");
	}
}

} // namespace communication
} // namespace xmipp4
