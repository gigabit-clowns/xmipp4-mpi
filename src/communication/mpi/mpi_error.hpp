// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stdexcept>

namespace xmipp4
{
namespace communication
{

/**
 * @brief Exception class representing a MPI error.
 * 
 */
class mpi_error
	: public std::runtime_error
{
	using runtime_error::runtime_error;
};

/**
 * @brief Check the return code of an MPI function
 * 
 * If the error code is MPI_SUCCESSFUL this function does nothing.
 * Otherwise it throws an exception with the appropiate message.
 * 
 * @param error_code Error code returned by MPI
 */
void mpi_check_error(int error_code);

} // namespace communication
} // namespace xmipp4
