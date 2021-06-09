#ifndef EZ_ECS_H
#define EZ_ECS_H

#include <stdint.h>
#include <stdexcept>
#include <vector>

#ifndef EZ_ECS_MAX_ENTITIES
    #define EZ_ECS_MAX_ENTITIES 32
#endif

#ifndef EZ_ECS_MAX_COMPONENTS
    #define EZ_ECS_MAX_COMPONENTS 64
#endif

#define CHECK_ENTITIES_SIZE(entity) if (entity == EZ_ECS_MAX_ENTITIES) { throw std::runtime_error("reached maximum number of entities!!"); }
#define CHECK_COMPONENTS_SIZE(componentID) if (componentID == EZ_ECS_MAX_COMPONENTS) { throw std::runtime_error("reached maximum number of components!!"); }

namespace EZ_ECS {

    static uint32_t componentsCounter = 0;
    static void *components[EZ_ECS_MAX_COMPONENTS][EZ_ECS_MAX_ENTITIES] = {nullptr};
    static bool sceneMatrix[EZ_ECS_MAX_COMPONENTS][EZ_ECS_MAX_ENTITIES] = {0};
    static uint32_t entities[EZ_ECS_MAX_ENTITIES] = {EZ_ECS_MAX_ENTITIES};
    static uint32_t createdEntities = 0;

    template <typename Comp> uint32_t GetComponentID() {
        static uint32_t componentID = componentsCounter++;
        return componentID;
    }

    uint32_t CreateEntity() {
        uint32_t entity = createdEntities;
        CHECK_ENTITIES_SIZE(entity);
        createdEntities++;
        entities[entity] = entity;
        return entity;
    }

    void DestroyEntity(uint32_t entity) {
        entities[entity] = EZ_ECS_MAX_ENTITIES;
    }

    template <typename Comp> bool HasComponent(uint32_t entity) {
        CHECK_ENTITIES_SIZE(entity); CHECK_COMPONENTS_SIZE(GetComponentID<Comp>());
        return sceneMatrix[GetComponentID<Comp>()][entity];
    }

    template <typename Comp> void AddComponent(uint32_t entity) {
        CHECK_ENTITIES_SIZE(entity); CHECK_COMPONENTS_SIZE(GetComponentID<Comp>());
        components[GetComponentID<Comp>()][entity] = new Comp();
        sceneMatrix[GetComponentID<Comp>()][entity] = 1;
    }

    template <typename Comp> void RemoveComponent(uint32_t entity) {
        CHECK_ENTITIES_SIZE(entity); CHECK_COMPONENTS_SIZE(GetComponentID<Comp>());
        components[GetComponentID<Comp>()][entity] = nullptr;
        sceneMatrix[GetComponentID<Comp>()][entity] = 0;
    }

    template <typename Comp> Comp *GetComponent(uint32_t entity) {
        return static_cast<Comp*>(components[GetComponentID<Comp>()][entity]);
    }

    template <typename Comp> std::vector<Comp*> View() {
        std::vector<Comp*> _components;
        for (uint32_t i = 0; i < createdEntities; i++) {
            if (static_cast<Comp*>(components[GetComponentID<Comp>()][i]) != nullptr) {
                _components.push_back(static_cast<Comp*>(components[GetComponentID<Comp>()][i]));
            }
        }
        return _components;
    }
};


#endif