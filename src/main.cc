#include <arcane/launcher/ArcaneLauncher.h>
#include "scihook/scihookdefs.h"
#ifdef SCIHOOK_ENABLED
#include <SciHook.h>
#include "__Bindings.h"
#endif // SCIHOOK_ENABLED

using namespace Arcane;

int
main(int argc,char* argv[])
{
  #ifdef SCIHOOK_ENABLED
	// FIXME add proper args handling
	int actual_argc;
	if (argc > 2) {
		actual_argc = argc - 2;
	} else {
		actual_argc = argc;
	}	

	if (argc > 2) {
		// Second-to-last arg is python path, last arg is instrumentation script (without .py extension)
		SciHook::initialize_scihook({ argv[argc - 2] }, { argv[argc - 1] }, "mahyco");
	}
	
	ArcaneLauncher::init(CommandLineArguments(&actual_argc,&argv));
	#else
	ArcaneLauncher::init(CommandLineArguments(&argc,&argv));
	#endif // SCIHOOK_ENABLED
	auto& app_build_info = ArcaneLauncher::applicationBuildInfo();
	//app_build_info.setMessagePassingService("SequentialParallelSuperMng");
	app_build_info.setCodeName("Mahyco");
	return ArcaneLauncher::run();
}

#ifdef SCIHOOK_ENABLED
PYBIND11_EMBEDDED_MODULE(mahyco, m) {
    py::module_ arcpy = py::module_::import("arcpy");
	import_modules(m);
}
#endif