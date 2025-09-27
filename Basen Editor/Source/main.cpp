#include "AppLayer.h"
#include <Core/Application.h>

int main() {
	Basen::ApplicationSpecification appSpecs{
		.name = "Basen Editor",
		.windowSpec = {
			.width = 1280,
			.height = 720,
		}
	};

	Basen::Application app(appSpecs);
	app.PushLayer<AppLayer>();
	app.run();
}