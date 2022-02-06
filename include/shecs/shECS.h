#ifndef SH_ECS_H
#define SH_ECS_H


#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#ifndef SH_ECS_MAX_ENTITIES
#define SH_ECS_MAX_ENTITIES 64
#endif

#ifndef SH_ECS_MAX_COMPONENTS
#define SH_ECS_MAX_COMPONENTS 32
#endif

#ifdef _MSC_VER
#pragma warning ( disable : 6262 )
#endif //_MSC_VER

typedef void* ShSceneMatrix[SH_ECS_MAX_ENTITIES][SH_ECS_MAX_COMPONENTS];
typedef uint32_t ComponentCountMatrix[SH_ECS_MAX_COMPONENTS];

typedef struct ShScene {

	uint32_t entity_count;
	ShSceneMatrix matrix;
	ComponentCountMatrix componentCount;
} ShScene;

#define SH_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t sh ## x ## ID = n; \
static const uint32_t sh ## x ## Size = sizeof(x); \
static x* shAdd ## x(ShScene* scene, const uint32_t entity) { \
	shCheckEntitiesSize(entity);\
	shCheckComponentsSize(sh ## x ## ID);\
	x* component = (x*)calloc(1, sizeof(x));\
	scene->matrix[entity][sh ## x ## ID] = component;\
	scene->componentCount[sh ## x ## ID]++;\
	return component;\
} \
static x* shSet ## x(ShScene* scene, x* component, const uint32_t entity) {\
	shCheckEntitiesSize(entity);\
	shCheckComponentsSize(sh ## x ## ID);\
	scene->matrix[entity][sh ## x ## ID] == NULL && scene->componentCount[sh ## x ## ID]++;\
	scene->matrix[entity][sh ## x ## ID] = component;\
	scene->matrix[entity][sh ## x ## ID] = component;\
	return component;\
}\
static int shHas ## x(const ShScene* scene, const uint32_t entity) { \
	return !(scene->matrix[entity][sh ## x ## ID] == NULL); \
} \
static x* shGet ## x(const ShScene* scene, const uint32_t entity) { \
	return (x*)scene->matrix[entity][sh ## x ## ID]; \
} \
static void shRemove ## x(ShScene* scene, const uint32_t entity) { \
	free(scene->matrix[entity][sh ## x ## ID]);\
	scene->matrix[entity][sh ## x ## ID] = NULL;\
	scene->componentCount[sh ## x ## ID]--;\
} \
static uint32_t shGet ## x ## Count(const ShScene scene) {\
	return scene.componentCount[sh ## x ## ID];\
}\
static x* shGet ## x ## Array(const ShScene* scene) {\
	x* arr = calloc(shGet ## x ## Count(*scene), sizeof(x));\
	if (arr == NULL) { return NULL; }\
	uint32_t i = 0;\
	for (uint32_t entity = 0; entity < scene->entity_count; entity++) {\
		if (shHas ## x(scene, entity)) {\
			x* comp_ptr = shGet ## x(scene, entity);\
			arr[i] = *comp_ptr;\
			i++;\
		}\
	}\
	return arr;\
}\

static void shCreateScene(ShScene* scene);

static const uint32_t shCreateEntity(ShScene* scene);

static void shDestroyEntity(ShScene* scene, const uint32_t entity);

static void shCheckEntitiesSize(const uint32_t entity);

static void shCheckComponentsSize(const uint32_t componentID);

static void shClearScene(ShScene* scene);

void shCreateScene(ShScene* scene) {
	for (uint32_t entity = 0; entity < SH_ECS_MAX_ENTITIES; entity++) {
		for (uint32_t component = 0; component < SH_ECS_MAX_COMPONENTS; component++) {
			scene->matrix[entity][component] = NULL;
		}
	}
}

const uint32_t shCreateEntity(ShScene* scene) {
	shCheckEntitiesSize(scene->entity_count);
	scene->entity_count++;
	return scene->entity_count - 1;
}

void shDestroyEntity(ShScene* scene, const uint32_t entity) {
	for (uint32_t component = 0; component < SH_ECS_MAX_COMPONENTS; component++) {
		free(scene->matrix[entity * SH_ECS_MAX_ENTITIES + component]);
		scene->matrix[entity][component] = NULL;
	}
}

void shCheckEntitiesSize(const uint32_t entity) {
	assert(entity < SH_ECS_MAX_ENTITIES);
}

void shCheckComponentsSize(const uint32_t componentID) {
	assert(componentID < SH_ECS_MAX_COMPONENTS);
}

void shClearScene(ShScene* scene) {
	memset((void*)scene->matrix, 0, sizeof(ShSceneMatrix));
	memset((void*)scene->componentCount, 0, sizeof(ComponentCountMatrix));
	scene->entity_count = 0;
	
}

#endif