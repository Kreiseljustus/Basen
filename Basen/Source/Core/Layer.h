#pragma once

namespace Basen {
	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnEvent() {}

		//This method is executed once when the application is started and all systems are initialized
		//This is where initial assets should be loaded
		//If done in the constructor instead, it will crash
		virtual void OnInitialLoad() {}

		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
	};
}