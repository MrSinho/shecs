#ifndef FGG_ECS_H
#define FGG_ECS_H


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#ifndef FGG_ECS_MAX_ENTITIES
#define FGG_ECS_MAX_ENTITIES 64
#endif

#ifndef FGG_ECS_MAX_COMPONENTS
#define FGG_ECS_MAX_COMPONENTS 32
#endif

#ifndef FGG_ECS_SHARED_COMPONENTS
#define FGG_ECS_SHARED_COMPONENTS FGG_ECS_MAX_COMPONENTS
#endif

typedef void* FggSceneMatrix[FGG_ECS_MAX_ENTITIES][FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS];

typedef struct FggScene {

	uint32_t entity_count;
	FggSceneMatrix matrix;

} FggScene;

#define FGG_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t fgg ## x ## ID = n; \
static const uint32_t fgg ## x ## Size = sizeof(x); \
static x* fggAdd ## x(FggScene* scene, const uint32_t entity) { \
	fggCheckEntitiesSize(entity);\
	fggCheckComponentsSize(fgg ## x ## ID);\
	x* component = (x*)calloc(1, sizeof(x));\
	scene->matrix[entity][fgg ## x ## ID] = component;\
	return component;\
} \
static x* fggSet ## x(FggScene* scene, x* component, const uint32_t entity) {\
	fggCheckEntitiesSize(entity);\
	fggCheckComponentsSize(fgg ## x ## ID);\
	scene->matrix[entity][fgg ## x ## ID] = component;\
	uint32_t* shared = calloc(1, sizeof(int));\
	if (shared != NULL) {\
		*shared = fgg ## x ## ID;\
	}\
	scene->matrix[entity][fgg ## x ## ID + FGG_ECS_SHARED_COMPONENTS] = shared;\
	return component;\
}\
static int fggIs ## x ## Shared(FggScene* scene, const uint32_t entity) {\
		return !(scene->matrix[entity][fgg ## x ## ID + FGG_ECS_SHARED_COMPONENTS] == NULL); \
}\
static int fggHas ## x(const FggScene* scene, const uint32_t entity) { \
	return !(scene->matrix[entity][fgg ## x ## ID] == NULL); \
} \
static x* fggGet ## x(const FggScene* scene, const uint32_t entity) { \
	return (x*)scene->matrix[entity][fgg ## x ## ID]; \
} \
static void FggECSRemove ## x(FggScene* scene, const uint32_t entity) { \
	free(scene->matrix[entity][fgg ## x ## ID]);\
	scene->matrix[entity][fgg ## x ## ID] = NULL;\
} \


static void fggCreateScene(FggScene* scene);

static const uint32_t fggCreateEntity(FggScene* scene);

static void fggDestroyEntity(FggScene* scene, const uint32_t entity);

static void fggCheckEntitiesSize(const uint32_t entity);

static void fggCheckComponentsSize(const uint32_t componentID);

static void fggClearScene(FggScene* scene);

void fggCreateScene(FggScene* scene) {
	for (uint32_t entity = 0; entity < FGG_ECS_MAX_ENTITIES; entity++) {
		for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS; component++) {
			scene->matrix[entity][component] = NULL;
		}
	}
}

const uint32_t fggCreateEntity(FggScene* scene) {
	fggCheckEntitiesSize(scene->entity_count);
	scene->entity_count++;
	return scene->entity_count - 1;
}

void fggDestroyEntity(FggScene* scene, const uint32_t entity) {
	for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS + FGG_ECS_SHARED_COMPONENTS; component++) {
		free(scene->matrix[entity * FGG_ECS_MAX_ENTITIES + component]);
		scene->matrix[entity][component] = NULL;
	}
}

void fggCheckEntitiesSize(const uint32_t entity) {
	assert(entity < FGG_ECS_MAX_ENTITIES);
}

void fggCheckComponentsSize(const uint32_t componentID) {
	assert(componentID < FGG_ECS_MAX_COMPONENTS);
}

void fggClearScene(FggScene* scene) {
	memset(scene->matrix, NULL, sizeof(FggSceneMatrix));
}

#endif