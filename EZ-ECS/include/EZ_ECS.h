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

typedef void* ezecsScene[EZ_ECS_MAX_ENTITIES][EZ_ECS_MAX_COMPONENTS];


#define EZ_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t ezecs ## x ## ID = n; \
static x* ezecsAdd ## x(ezecsScene scene, const uint32_t entity) { \
	ezecsCheckEntitiesSize(entity);\
	ezecsCheckComponentsSize(ezecs ## x ## ID);\
	x* component = (x*)calloc(1, sizeof(x));\
	scene[entity][ezecs ## x ## ID] = component;\
	return component;\
} \
static const x* ezecsSet ## x(ezecsScene scene, x* component, const uint32_t entity) {\
	ezecsCheckEntitiesSize(entity);\
	ezecsCheckComponentsSize(ezecs ## x ## ID);\
	scene[entity][ezecs ## x ## ID] = component;\
	return component;\
}\
static int ezecsHas ## x(const ezecsScene scene, const uint32_t entity) { \
	return !(scene[entity][ezecs ## x ## ID] == NULL); \
} \
static x* ezecsGet ## x(const ezecsScene scene, const uint32_t entity) { \
	return (x*)scene[entity][ezecs ## x ## ID]; \
} \
static void ezecsRemove ## x(ezecsScene scene, const uint32_t entity) { \
	free(scene[entity][ezecs ## x ## ID]);\
	scene[entity][ezecs ## x ## ID] = NULL;\
} \


static void ezecsCreateScene(ezecsScene scene);

static const uint32_t ezecsCreateEntity();

static void ezecsDestroyEntity(ezecsScene scene, const uint32_t entity);

static void ezecsCheckEntitiesSize(const uint32_t entity);

static void ezecsCheckComponentsSize(const uint32_t componentID);

static void ezecsClearScene(ezecsScene scene);

void ezecsCreateScene(ezecsScene scene) {
	for (uint32_t entity = 0; entity < EZ_ECS_MAX_ENTITIES; entity++) {
		for (uint32_t component = 0; component < EZ_ECS_MAX_COMPONENTS; component++) {
			scene[entity][component] = NULL;
		}
	}
}

const uint32_t ezecsCreateEntity() {
	static uint32_t entity = 0;
	const uint32_t _entity = entity;
	entity++;
	ezecsCheckEntitiesSize(_entity);
	return _entity;
}

void ezecsDestroyEntity(ezecsScene scene, const uint32_t entity) {
	for (uint32_t component = 0; component < EZ_ECS_MAX_COMPONENTS; component++) {
		free(scene[entity * EZ_ECS_MAX_ENTITIES + component]);
		scene[entity][component] = NULL;
	}
}

void ezecsCheckEntitiesSize(const uint32_t entity) {
	assert(entity < EZ_ECS_MAX_ENTITIES);
}

void ezecsCheckComponentsSize(const uint32_t componentID) {
	assert(componentID < EZ_ECS_MAX_COMPONENTS);
}

void ezecsClearScene(ezecsScene scene) {
	free(scene);
}

#endif