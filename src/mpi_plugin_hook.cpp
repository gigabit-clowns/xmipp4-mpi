// SPDX-License-Identifier: GPL-3.0-only

#include "mpi_plugin.hpp"

#include <xmipp4/core/platform/dynamic_shared_object.h>

#if defined(XMIPP4_MPI_EXPORTING)
	#define XMIPP4_MPI_API XMIPP4_EXPORT
#else
	#define XMIPP4_MPI_API XMIPP4_IMPORT
#endif

static const xmipp4::mpi_plugin instance;

extern "C"
{
XMIPP4_MPI_API const xmipp4::plugin* xmipp4_get_plugin() 
{
	return &instance;
}
}
