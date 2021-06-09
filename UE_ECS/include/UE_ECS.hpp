#ifndef UNNAMED_ENGINE_CS_H
#define UNNAMED_ENGINE_CS_H

#include <stdint.h>
#include <stdexcept>

#ifndef MAX_ENTITIES
    #define MAX_ENTITIES 10
#endif

#ifndef MAX_COMPONENTS
    #define MAX_COMPONENTS 10
#endif

#define CHECK_ENTITIES_SIZE(entity) if (entity == MAX_ENTITIES) { throw std::runtime_error("reached maximum number of entities!!"); }
#define CHECK_COMPONENTS_SIZE(componentID) if (componentID == MAX_COMPONENTS) { throw std::runtime_error("reached maximum number of components!!"); }

static uint32_t componentsCounter = 0;

template <typename Comp> uint32_t GetComponentID() {
    static uint32_t componentID = componentsCounter++;
    return componentID;
}

struct Scene {

    uint32_t CreateEntity() {
        uint32_t entity = usedEntitiesCounter;
        CHECK_ENTITIES_SIZE(entity);
        usedEntitiesCounter++;
        entities[entity] = entity;
        return entity;
    }

    void DestroyEntity(uint32_t entity) {
        entities[entity] = MAX_ENTITIES;
    }

   template <typename Comp> bool HasComponent(uint32_t entity) {
        CHECK_ENTITIES_SIZE(entity); CHECK_COMPONENTS_SIZE(GetComponentID<Comp>());
        return sceneMatrix[GetComponentID<Comp>()][entity];
    }

    template <typename Comp> void AddComponent(uint32_t entity) {
        CHECK_ENTITIES_SIZE(entity); CHECK_COMPONENTS_SIZE(GetComponentID<Comp>());
        sceneMatrix[GetComponentID<Comp>()][entity] = 1;
    }

    template <typename Comp> void RemoveComponent(uint32_t entity) {
        CHECK_ENTITIES_SIZE(entity); CHECK_COMPONENTS_SIZE(GetComponentID<Comp>());
        sceneMatrix[GetComponentID<Comp>()][entity] = 0;
    }
    
    template <typename Comp> Comp *GetComponent(uint32_t entity) {
        return nullptr;
    }

    uint32_t entities[MAX_ENTITIES] = {MAX_ENTITIES};
    uint32_t usedEntitiesCounter = 0;

    bool sceneMatrix[MAX_COMPONENTS][MAX_ENTITIES] = {0};
};

#endif