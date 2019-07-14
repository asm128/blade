#include "blade.h"

#include "gpk_cgi_app_impl_v2.h"

#include "gpk_process.h"

#ifndef BLADE_ENDPOINT_H_20190713
#define BLADE_ENDPOINT_H_20190713

#define BLADE_READONLY_ENDPOINT_IMPL(_endpointName)																																	\
GPK_CGI_JSON_APP_IMPL();																																							\
																																													\
::gpk::error_t									gpk_cgi_generate_output			(::gpk::SCGIRuntimeValues & runtimeValues, ::gpk::array_pod<char_t> & output)					{	\
	output.append(::gpk::view_const_string{"\r\n"});																																\
	::blade::SBladeApp									app;																														\
	::gpk::array_obj<::gpk::TKeyValConstString>			environViews;																												\
	::gpk::environmentBlockViews(runtimeValues.EntryPointArgs.EnvironmentBlock, environViews);																						\
	if(0 == ::blade::validateMethod("GET")) {																																		\
		output.append(::gpk::view_const_string{"{ \"status\" : 403, \"description\" :\"forbidden\" }\r\n"});																		\
		return 1;																																									\
	}																																												\
	gpk_necall(::blade::loadConfig(app, "blade.json"), "%s", "Failed to load query.");																								\
	gpk_necall(::blade::loadCWD(app.CWD), "%s", "Failed to load query.");																											\
	gpk_necall(::blade::loadQuery(app.Query, runtimeValues.QueryStringKeyVals), "%s", "Failed to load query.");																		\
	gpk_necall(::blade::loadDatabase(app), "%s", "Failed to load blade databases.");																								\
	int32_t												detail							= -1;																						\
	gpk_necall(::blade::loadDetail(detail), "%s", "Failed to load detail.");																										\
	gpk_necall(::blade::generate_output_for_db(app, _endpointName, detail, output), "%s", "Failed to load blade databases.");														\
	return 0;																																										\
}

#endif // BLADE_ENDPOINT_H_20190713
