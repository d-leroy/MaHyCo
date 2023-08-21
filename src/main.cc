#include <arcane/launcher/ArcaneLauncher.h>
#include "scihook/scihookdefs.h"
#ifdef SCIHOOK_ENABLED
#include "arcane/utils/FloatingPointExceptionSentry.h"
#include <SciHook.h>
#include "__Bindings.h"
#endif // SCIHOOK_ENABLED

using namespace Arcane;

int
main(int argc,char* argv[])
{

	CommandLineArguments args(&argc,&argv);

	ArcaneLauncher::init(args);
	auto& app_build_info = ArcaneLauncher::applicationBuildInfo();

  	#ifdef SCIHOOK_ENABLED
	std::vector<std::string> python_path = { args.getParameter("scihook_path").localstr() };
	std::vector<std::string> python_script = { args.getParameter("scihook_script").localstr() };

	if (python_script[0] != "") {
		{
			FloatingPointExceptionSentry fpes(false);
			SciHook::initialize_scihook(python_path, python_script, "mahyco");
		}
	}
	#endif // SCIHOOK_ENABLED

	//app_build_info.setMessagePassingService("SequentialParallelSuperMng");
	app_build_info.setCodeName("Mahyco");
	return ArcaneLauncher::run();
}

#ifdef SCIHOOK_ENABLED
PYBIND11_EMBEDDED_MODULE(mahyco, m) {
    bind_submodules(m);
}
#endif
