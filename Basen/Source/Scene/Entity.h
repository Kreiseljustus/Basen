#pragma once

#include <entt/entt.hpp>

namespace Basen {

	class Scene;

	//IMPORTANT: ID does not mean UUID
	class Entity {
		friend class Scene;

	public:
		Entity() = default;
		Entity(entt::entity id, Scene* scene);

		bool IsValid() const { return m_Id != entt::null && m_Scene != nullptr; }

		bool operator==(const Entity& other) const {
			return m_Id == other.m_Id && m_Scene == other.m_Scene;
		}

	private:
		entt::entity m_Id{ entt::null };
		Scene* m_Scene{ nullptr };
	};
}

