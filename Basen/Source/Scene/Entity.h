#pragma once

#include <entt/entt.hpp>

namespace Basen {

	class Scene;

	//IMPORTANT: ID does not mean UUID
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity id, Scene* scene);

	private:
		entt::entity m_Id{ entt::null };
		Scene* m_Scene{ nullptr };
	};
}

