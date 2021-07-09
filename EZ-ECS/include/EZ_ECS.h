#ifndef EZ_ECS_H
#define EZ_ECS_H


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


#ifndef EZ_ECS_MAX_ENTITIES
#define EZ_ECS_MAX_ENTITIES 64
#endif

#ifndef EZ_ECS_MAX_COMPONENTS
#define EZ_ECS_MAX_COMPONENTS 32
#endif



typedef struct ezecsScene {

	void* sceneMatrix[EZ_ECS_MAX_ENTITIES][EZ_ECS_MAX_COMPONENTS];

} ezecsScene;



#define EZ_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t ezecs ## x ## ComponentID = n; \
x* ezecsAdd ## x ## Component(ezecsScene *scene, uint32_t entity) { \
	ezecsCheckEntitiesSize(entity);\
	ezecsCheckComponentsSize(ezecs ## x ## ComponentID);\
	x *component = (x*)calloc(1, sizeof(x));\
	scene->sceneMatrix[entity][ezecs ## x ## ComponentID] = (void*)component;\
	return (x*)component;\
} \
int ezecsHas ## x ## Component(ezecsScene scene, uint32_t entity) { \
	return !(scene.sceneMatrix[entity][ezecs ## x ## ComponentID] == NULL); \
} \
x* ezecsGet ## x ## Component(ezecsScene scene, uint32_t entity) { \
	return (x*)scene.sceneMatrix[entity][ezecs ## x ## ComponentID]; \
} \
void ezecsRemove ## x ## Component(ezecsScene *scene, uint32_t entity) { \
	free(scene->sceneMatrix[entity][ezecs ## x ## ComponentID]);\
	scene->sceneMatrix[entity][ezecs ## x ## ComponentID] = NULL;\
} \



ezecsScene ezecsCreateScene();

const uint32_t ezecsCreateEntity();

void ezecsDestroyEntity(ezecsScene *scene, uint32_t entity);

void ezecsCheckEntitiesSize(uint32_t entity);

void ezecsCheckComponentsSize(uint32_t componentID);



ezecsScene ezecsCreateScene() {
	ezecsScene scene = { { NULL } };
	return scene;
}

const uint32_t ezecsCreateEntity() {
	static uint32_t entity = 0;
	const uint32_t _entity = entity;
	entity++;
	ezecsCheckEntitiesSize(_entity);
	return _entity;
}

void ezecsDestroyEntity(ezecsScene* scene, uint32_t entity) {
	for (uint32_t i = 0; i < EZ_ECS_MAX_COMPONENTS; i++) {
		free(scene->sceneMatrix[entity][i]);
		scene->sceneMatrix[entity][i] = NULL;
	}
}

void ezecsCheckEntitiesSize(const uint32_t entity) {
	assert(entity < EZ_ECS_MAX_ENTITIES);
}

void ezecsCheckComponentsSize(const uint32_t componentID) {
	assert(componentID < EZ_ECS_MAX_COMPONENTS);
}

#endif