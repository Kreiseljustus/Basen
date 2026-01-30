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

		void DestroyEntity(Entity entity);

		const SceneOptions& GetOptions() { return m_Options; }

		void OnUpdate(float deltaTime);

		template<typename T, typename... Args>
		T& AddComponent(Entity entity, Args&&... args) {
			return m_Registry.emplace<T>(entity.m_Id, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent(Entity entity) {
			return m_Registry.get<T>(entity.m_Id);
		}

		template<typename T>
		bool HasComponent(Entity entity) {
			return m_Registry.any_of<T>(entity.m_Id);
		}

		template<typename T>
		void RemoveComponent(Entity entity) {
			m_Registry.remove<T>(entity.m_Id);
		}

	private:
		entt::registry m_Registry;
		SceneOptions m_Options;
	};
}
