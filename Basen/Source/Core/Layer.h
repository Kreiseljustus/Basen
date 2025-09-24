#pragma once

namespace Basen {
	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnEvent() {}

		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
	};
}