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
static const uint32_t fggECS ## x ## ID = n; \
static const uint32_t fggECS ## x ## Size = sizeof(x); \
static x* fggECSAdd ## x(FggECSScene scene, const uint32_t entity) { \
	fggECSCheckEntitiesSize(entity);\
	fggECSCheckComponentsSize(fggECS ## x ## ID);\
	x* component = (x*)calloc(1, sizeof(x));\
	scene[entity][fggECS ## x ## ID] = component;\
	return component;\
} \
static x* fggECSSet ## x(FggECSScene scene, x* component, const uint32_t entity) {\
	fggECSCheckEntitiesSize(entity);\
	fggECSCheckComponentsSize(fggECS ## x ## ID);\
	scene[entity][fggECS ## x ## ID] = component;\
	uint32_t* shared = calloc(1, sizeof(int));\
	if (shared != NULL) {\
		*shared = fggECS ## x ## ID;\
	}\
	scene[entity][fggECS ## x ## ID + FGG_ECS_SHARED_COMPONENTS] = shared;\
	return component;\
}\
static int fggECSIs ## x ## Shared(FggECSScene scene, const uint32_t entity) {\
		return !(scene[entity][fggECS ## x ## ID + FGG_ECS_SHARED_COMPONENTS] == NULL); \
}\
static int fggECSHas ## x(const FggECSScene scene, const uint32_t entity) { \
	return !(scene[entity][fggECS ## x ## ID] == NULL); \
} \
static x* fggECSGet ## x(const FggECSScene scene, const uint32_t entity) { \
	return (x*)scene[entity][fggECS ## x ## ID]; \
} \
static void FggECSRemove ## x(FggECSScene scene, const uint32_t entity) { \
	free(scene[entity][fggECS ## x ## ID]);\
	scene[entity][fggECS ## x ## ID] = NULL;\
} \


static void fggECSCreateScene(FggECSScene scene);

static const uint32_t fggECSCreateEntity();

static void fggECSDestroyEntity(FggECSScene scene, const uint32_t entity);

static void fggECSCheckEntitiesSize(const uint32_t entity);

static void fggECSCheckComponentsSize(const uint32_t componentID);

static void fggECSClearScene(FggECSScene scene);

void fggECSCreateScene(FggECSScene scene) {
	for (uint32_t entity = 0; entity < FGG_ECS_MAX_ENTITIES; entity++) {
		for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS; component++) {
			scene[entity][component] = NULL;
		}
	}
}

const uint32_t fggECSCreateEntity() {
	static uint32_t entity = 0;
	const uint32_t _entity = entity;
	entity++;
	fggECSCheckEntitiesSize(_entity);
	return _entity;
}

void fggECSDestroyEntity(FggECSScene scene, const uint32_t entity) {
	for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS; component++) {
		free(scene[entity * FGG_ECS_MAX_ENTITIES + component]);
		scene[entity][component] = NULL;
	}
}

void fggECSCheckEntitiesSize(const uint32_t entity) {
	assert(entity < FGG_ECS_MAX_ENTITIES);
}

void fggECSCheckComponentsSize(const uint32_t componentID) {
	assert(componentID < FGG_ECS_MAX_COMPONENTS);
}

void fggECSClearScene(FggECSScene scene) {
	free(scene);
}

#endif