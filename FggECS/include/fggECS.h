#ifndef FGG_ECS_H
#define FGG_ECS_H


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


#ifndef FGG_ECS_MAX_ENTITIES
#define FGG_ECS_MAX_ENTITIES 64
#endif

#ifndef FGG_ECS_MAX_COMPONENTS
#define FGG_ECS_MAX_COMPONENTS 32
#endif

#ifndef FGG_ECS_SHARED_COMPONENTS
#define FGG_ECS_SHARED_COMPONENTS FGG_ECS_MAX_COMPONENTS
#endif

typedef void* FggECSScene[FGG_ECS_MAX_ENTITIES][FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS];


#define FGG_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t fgg ## x ## ID = n; \
static const uint32_t fgg ## x ## Size = sizeof(x); \
static x* fggAdd ## x(FggECSScene scene, const uint32_t entity) { \
	fggCheckEntitiesSize(entity);\
	fggCheckComponentsSize(fgg ## x ## ID);\
	x* component = (x*)calloc(1, sizeof(x));\
	scene[entity][fgg ## x ## ID] = component;\
	return component;\
} \
static x* fggSet ## x(FggECSScene scene, x* component, const uint32_t entity) {\
	fggCheckEntitiesSize(entity);\
	fggCheckComponentsSize(fgg ## x ## ID);\
	scene[entity][fgg ## x ## ID] = component;\
	uint32_t* shared = calloc(1, sizeof(int));\
	if (shared != NULL) {\
		*shared = fgg ## x ## ID;\
	}\
	scene[entity][fgg ## x ## ID + FGG_ECS_SHARED_COMPONENTS] = shared;\
	return component;\
}\
static int fggIs ## x ## Shared(FggECSScene scene, const uint32_t entity) {\
		return !(scene[entity][fgg ## x ## ID + FGG_ECS_SHARED_COMPONENTS] == NULL); \
}\
static int fggHas ## x(const FggECSScene scene, const uint32_t entity) { \
	return !(scene[entity][fgg ## x ## ID] == NULL); \
} \
static x* fggGet ## x(const FggECSScene scene, const uint32_t entity) { \
	return (x*)scene[entity][fgg ## x ## ID]; \
} \
static void FggECSRemove ## x(FggECSScene scene, const uint32_t entity) { \
	free(scene[entity][fgg ## x ## ID]);\
	scene[entity][fgg ## x ## ID] = NULL;\
} \


static void fggCreateScene(FggECSScene scene);

static const uint32_t fggCreateEntity();

static void fggDestroyEntity(FggECSScene scene, const uint32_t entity);

static void fggCheckEntitiesSize(const uint32_t entity);

static void fggCheckComponentsSize(const uint32_t componentID);

static void fggClearScene(FggECSScene scene);

void fggCreateScene(FggECSScene scene) {
	for (uint32_t entity = 0; entity < FGG_ECS_MAX_ENTITIES; entity++) {
		for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS; component++) {
			scene[entity][component] = NULL;
		}
	}
}

const uint32_t fggCreateEntity() {
	static uint32_t entity = 0;
	const uint32_t _entity = entity;
	entity++;
	fggCheckEntitiesSize(_entity);
	return _entity;
}

void fggDestroyEntity(FggECSScene scene, const uint32_t entity) {
	for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS; component++) {
		free(scene[entity * FGG_ECS_MAX_ENTITIES + component]);
		scene[entity][component] = NULL;
	}
}

void fggCheckEntitiesSize(const uint32_t entity) {
	assert(entity < FGG_ECS_MAX_ENTITIES);
}

void fggCheckComponentsSize(const uint32_t componentID) {
	assert(componentID < FGG_ECS_MAX_COMPONENTS);
}

void fggClearScene(FggECSScene scene) {
	free(scene);
}

#endif