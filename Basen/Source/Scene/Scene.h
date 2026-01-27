#pragma once

#include <entt/entt.hpp>
#include "Entity.h"

namespace Basen {

	struct SceneOptions {
		bool DontDestroyOnSceneLoad; //Dont destroy this scene when another gets loaded (or this one gets reloaded)
		std::string Name;
	};

	class Scene {
	public:
		Scene(const SceneOptions& options = { .DontDestroyOnSceneLoad = false, .Name = "New Scene"});
		~Scene() {
			m_Registry.clear();
		}

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		Entity CreateEntity();
		Entity CreateEntity(const std::string& name);

		void DestroyEntity(entt::entity entity);

		const SceneOptions& GetOptions() { return m_Options; }

		void OnUpdate(float deltaTime);
	private:
		entt::registry m_Registry;
		SceneOptions m_Options;
	};
}
