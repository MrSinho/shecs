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

#ifdef _MSC_VER
#pragma warning ( disable : 6262 )
#endif //_MSC_VER

typedef void* FggSceneMatrix[FGG_ECS_MAX_ENTITIES][FGG_ECS_MAX_COMPONENTS];

typedef struct FggScene {

	uint32_t entity_count;
	FggSceneMatrix matrix;
	uint32_t componentCount[FGG_ECS_MAX_COMPONENTS];
} FggScene;

#define FGG_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t fgg ## x ## ID = n; \
static const uint32_t fgg ## x ## Size = sizeof(x); \
static x* fggAdd ## x(FggScene* scene, const uint32_t entity) { \
	fggCheckEntitiesSize(entity);\
	fggCheckComponentsSize(fgg ## x ## ID);\
	x* component = (x*)calloc(1, sizeof(x));\
	scene->matrix[entity][fgg ## x ## ID] = component;\
	scene->componentCount[fgg ## x ## ID]++;\
	return component;\
} \
static x* fggSet ## x(FggScene* scene, x* component, const uint32_t entity) {\
	fggCheckEntitiesSize(entity);\
	fggCheckComponentsSize(fgg ## x ## ID);\
	scene->matrix[entity][fgg ## x ## ID] == NULL && scene->componentCount[fgg ## x ## ID]++;\
	scene->matrix[entity][fgg ## x ## ID] = component;\
	scene->matrix[entity][fgg ## x ## ID] = component;\
	return component;\
}\
static int fggHas ## x(const FggScene* scene, const uint32_t entity) { \
	return !(scene->matrix[entity][fgg ## x ## ID] == NULL); \
} \
static x* fggGet ## x(const FggScene* scene, const uint32_t entity) { \
	return (x*)scene->matrix[entity][fgg ## x ## ID]; \
} \
static void fggRemove ## x(FggScene* scene, const uint32_t entity) { \
	free(scene->matrix[entity][fgg ## x ## ID]);\
	scene->matrix[entity][fgg ## x ## ID] = NULL;\
	scene->componentCount[fgg ## x ## ID]--;\
} \
static uint32_t fggGet ## x ## Count(const FggScene scene) {\
	return scene.componentCount[fgg ## x ## ID];\
}\
static x* fggGet ## x ## Array(const FggScene* scene) {\
	x* arr = calloc(fggGet ## x ## Count(*scene), sizeof(x));\
	if (arr == NULL) { return NULL; }\
	uint32_t i = 0;\
	for (uint32_t entity = 0; entity < scene->entity_count; entity++) {\
		if (fggHas ## x(scene, entity)) {\
			x* comp_ptr = fggGet ## x(scene, entity);\
			arr[i] = *comp_ptr;\
			i++;\
		}\
	}\
	return arr;\
}\

static void fggCreateScene(FggScene* scene);

static const uint32_t fggCreateEntity(FggScene* scene);

static void fggDestroyEntity(FggScene* scene, const uint32_t entity);

static void fggCheckEntitiesSize(const uint32_t entity);

static void fggCheckComponentsSize(const uint32_t componentID);

static void fggClearScene(FggScene* scene);

void fggCreateScene(FggScene* scene) {
	for (uint32_t entity = 0; entity < FGG_ECS_MAX_ENTITIES; entity++) {
		for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS; component++) {
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
	for (uint32_t component = 0; component < FGG_ECS_MAX_COMPONENTS; component++) {
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
	memset((void*)scene->matrix, 0, sizeof(FggSceneMatrix));
	scene->entity_count = 0;
}

#endif