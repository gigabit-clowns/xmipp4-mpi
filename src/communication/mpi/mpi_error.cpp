// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_error.hpp"

#include <mpi.h>

namespace xmipp4 
{
namespace communication
{

void mpi_check_error(int error_code)
{
	if (error_code != MPI_SUCCESS)
	{
		char message[MPI_MAX_ERROR_STRING];
		int count = 0;
		MPI_Error_string(error_code, message, &count);
		throw mpi_error(message);
	}
}

} // namespace communication
} // namespace xmipp4
