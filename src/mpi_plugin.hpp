// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <xmipp4/core/plugin.hpp>

namespace xmipp4 
{

class mpi_plugin final
	: public plugin
{
public:
	const std::string& get_name() const noexcept override;
	version get_version() const noexcept override;
	void register_at(service_catalog& catalog) const override;

private:
	static const std::string name;
};

} // namespace xmipp4
