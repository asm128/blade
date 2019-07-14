#include "gpk_json.h"

#include <Windows.h>
#include <process.h>

#ifndef BLADE_H_20190712
#define BLADE_H_20190712

namespace blade
{
	static constexpr const uint32_t					MAX_TABLE_RECORD_COUNT		= 0x7FFFFFFF;

	struct SQuery {
		::gpk::SRange<uint32_t>						Range						= {0, MAX_TABLE_RECORD_COUNT};
		::gpk::view_const_string					Expand						= "";
	};


	struct SProcess {
		PROCESS_INFORMATION							ProcessInfo					= {}; 
		STARTUPINFOA								StartInfo					= {sizeof(STARTUPINFOA)};
	};

	struct SBladeApp {
		::gpk::array_obj<::gpk::TKeyValJSONFile>	Databases					= {};
		::blade::SQuery								Query						= {};
		::blade::SProcess							Process						= {};
		::gpk::array_pod<char_t>					CWD							= {};
		::gpk::SJSONFile							JSONConfig					= {};
	};

	::gpk::error_t									validateMethod				(const ::gpk::view_array<::gpk::TKeyValConstString> & environViews, const ::gpk::view_const_string & method);
	::gpk::error_t									loadConfig					(::blade::SBladeApp & appState, const ::gpk::view_const_string & filename);
	::gpk::error_t									loadCWD						(const ::gpk::view_array<::gpk::TKeyValConstString> & environViews, ::gpk::array_pod<char_t> & method);
	::gpk::error_t									loadDetail					(const ::gpk::view_array<::gpk::TKeyValConstString> & environViews, int32_t & detail);
	::gpk::error_t									loadQuery					(::blade::SQuery& query, const ::gpk::view_array<const ::gpk::TKeyValConstString> keyvals);
	::gpk::error_t									loadDatabase				(::blade::SBladeApp & appState);

	::gpk::error_t									generate_output_for_db		(::blade::SBladeApp & app, const ::gpk::view_const_string & databaseName, int32_t detail, ::gpk::array_pod<char_t> & output);
}


#endif // BLADE_H_20190712
