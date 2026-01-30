#include "Scene.h"

#include "Components.h"

namespace Basen {
	Scene::Scene(const SceneOptions& options) : m_Options(options) {}

	Entity Scene::CreateEntity() {
		return CreateEntity("New Entity");
	}

	Entity Scene::CreateEntity(const std::string& name) {
		Entity e = Entity(m_Registry.create(), this);

		m_Registry.emplace<NameComponent>(e.m_Id, name);

		return e;
	}

	void Scene::DestroyEntity(Entity entity) {
		m_Registry.destroy(entity.m_Id);
	}

	void Scene::OnUpdate(float deltaTime) {

	}
}