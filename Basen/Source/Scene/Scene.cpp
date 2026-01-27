#include "Scene.h"

namespace Basen {
	Scene::Scene(const SceneOptions& options) : m_Options(options) {}

	Entity Scene::CreateEntity() {
		Entity ent(m_Registry.create(), this);

		return ent;
	}

	Entity Scene::CreateEntity(const std::string& name) {
		return Entity(m_Registry.create(), this);
	}

	void Scene::DestroyEntity(entt::entity entity) {

	}

	void Scene::OnUpdate(float deltaTime) {

	}
}