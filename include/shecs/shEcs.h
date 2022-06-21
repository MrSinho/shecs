#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifndef SH_ECS_H
#define SH_ECS_H

#ifdef _MSC_VER
#pragma warning (disable: 6011)
#endif//_MSC_VER

#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#if 0
typedef enum ShEcsStatus {
	SH_ECS_SUCCESS								= 0b0000,
	SH_ECS_ERROR_ENTITY_INDEX_OUT_OF_RANGE		= 0b0001,
	SH_ECS_ERROR_COMPONENT_INDEX_OUT_OF_RANGE	= 0b0010,
	SH_ECS_INVALID_MEMORY						= 0b0100
} ShEcsStatus;
#endif//0


typedef struct ShScene {
	void***		ppp_matrix;						//matrix pointer
	uint32_t	max_entities;					//
	uint32_t	max_components;					//
	uint32_t	entity_count;					//
	uint32_t*	p_entity_component_count;		//number of components for each entity
	uint32_t*	p_component_component_count;	//number of components inside the scene
} ShScene;



static uint8_t shEcsWarning(int condition, const char* msg);

static uint8_t shEcsError(int condition, const char* msg);

static void shCreateScene(ShScene* p_scene, const uint32_t max_entities, const uint32_t max_components);

static uint32_t shCreateEntity(ShScene* scene);

static void shComponentRelease(ShScene* p_scene, const uint32_t entity, const uint32_t component_id);

static void shEntityRelease(ShScene* p_scene, const uint32_t entity);

static void shSceneRelease(ShScene* p_scene);



uint8_t shEcsWarning(int condition, const char* msg) {
	if ((int)(condition)) { printf("shecs warning: %s.\n", msg); return 1; }
	return 0;
}

#define shEcsError(condition, msg)\
	if ((condition)) { printf("shecs error: %s.\n", msg); return; }\

void shCreateScene(ShScene* p_scene, const uint32_t max_entities, const uint32_t max_components) {
	if (!shEcsWarning(max_entities == 0 || max_components == 0, "invalid scene parameters")) {
		p_scene->ppp_matrix = calloc(max_entities, sizeof(void*));
		shEcsError(p_scene->ppp_matrix == NULL, "invalid scene matrix");
			for (uint32_t entity = 0; entity < max_entities; entity++) {
				p_scene->ppp_matrix[entity] = calloc(max_components, sizeof(void*));
				shEcsError(p_scene->ppp_matrix[entity] == NULL, "invalid scene entities");
				//Components allocated individually
			}
		p_scene->p_entity_component_count = calloc(max_entities, sizeof(uint32_t));
		p_scene->p_component_component_count = calloc(max_components, sizeof(uint32_t));
	}
	p_scene->max_entities = max_entities;
	p_scene->max_components = max_components;
}

uint32_t shCreateEntity(ShScene* p_scene) {
	if (!shEcsWarning(p_scene->entity_count >= p_scene->max_entities, "entity index out of range")) {
		p_scene->entity_count++;
		return p_scene->entity_count - 1;
	}
	return UINT32_MAX;
}

void shComponentRelease(ShScene* p_scene, const uint32_t entity, const uint32_t component_id) {
	uint8_t* p_component = ((uint8_t***)p_scene->ppp_matrix)[entity][component_id];
	if (!shEcsWarning(p_component == NULL || component_id >= p_scene->max_components, "invalid component id or index out of range")) {
		free(p_component);
		((uint8_t***)p_scene->ppp_matrix)[entity][component_id] = NULL;
		p_scene->p_component_component_count[component_id]--;
	}
}

void shEntityRelease(ShScene* p_scene, const uint32_t entity) {
	uint8_t** pp_entity = ((uint8_t***)p_scene->ppp_matrix)[entity];
	shEcsWarning(pp_entity == NULL || entity >= p_scene->max_entities, "invalid entity or index out of range");
	if (pp_entity != NULL && entity <= p_scene->max_entities) {
		for (uint32_t component = 0; component < p_scene->p_entity_component_count[entity]; component++) {
			uint8_t* p_component = pp_entity[component];
			if (p_component != NULL) {
				shComponentRelease(p_scene, entity, component);
			}
		}
		free(pp_entity);
		((uint8_t***)p_scene->ppp_matrix)[entity] = NULL;
		p_scene->p_entity_component_count[entity] = 0;
	}
}

void shSceneRelease(ShScene* p_scene) {
	for (uint32_t entity = 0; entity < p_scene->entity_count; entity++) {
		shEntityRelease(p_scene, entity);
	}
	p_scene->entity_count = 0;
	free(p_scene->p_entity_component_count);
	free(p_scene->p_component_component_count);
	p_scene->p_entity_component_count = NULL;
	p_scene->p_component_component_count = NULL;
}



#define SH_ECS_MAKE_COMPONENT_DEFINITIONS(x, n) \
static const uint32_t sh ## x ## ID = n; \
static const uint32_t sh ## x ## Size = sizeof(x); \
static x* shAdd ## x(ShScene* p_scene, const uint32_t entity) { \
	x* p_component = (x*)calloc(1, sizeof(x));\
	p_scene->ppp_matrix[entity][sh ## x ## ID] = p_component;\
	p_scene->p_component_component_count[sh ## x ## ID]++;\
	return p_component;\
} \
static x* shSet ## x(ShScene* p_scene, x* p_component, const uint32_t entity) {\
	if (!(shEcsWarning(entity >= p_scene->entity_count, "entity index out of range") || shEcsWarning(p_component == NULL, "invalid p_component memory"))) {\
		p_scene->ppp_matrix[entity][sh ## x ## ID] == NULL && p_scene->p_component_component_count[sh ## x ## ID]++;\
		p_scene->ppp_matrix[entity][sh ## x ## ID] = p_component;\
		p_scene->ppp_matrix[entity][sh ## x ## ID] = p_component;\
		return p_component;\
	}\
	return NULL;\
}\
static int shHas ## x(const ShScene* p_scene, const uint32_t entity) { \
	return !(p_scene->ppp_matrix[entity][sh ## x ## ID] == NULL); \
} \
static x* shGet ## x(const ShScene* p_scene, const uint32_t entity) { \
	return (x*)p_scene->ppp_matrix[entity][sh ## x ## ID]; \
} \
static void shRemove ## x(ShScene* p_scene, const uint32_t entity) { \
	free(p_scene->ppp_matrix[entity][sh ## x ## ID]);\
	p_scene->ppp_matrix[entity][sh ## x ## ID] = NULL;\
	p_scene->p_component_component_count[sh ## x ## ID]--;\
} \
static uint32_t shGet ## x ## Count(const ShScene p_scene) {\
	return p_scene.p_component_component_count[sh ## x ## ID];\
}\
static x* shGet ## x ## Array(const ShScene* p_scene) {\
	x* arr = calloc(shGet ## x ## Count(*p_scene), sizeof(x));\
	if (arr == NULL) { return NULL; }\
	uint32_t i = 0;\
	for (uint32_t entity = 0; entity < p_scene->entity_count; entity++) {\
		if (shHas ## x(p_scene, entity)) {\
			x* comp_ptr = shGet ## x(p_scene, entity);\
			arr[i] = *comp_ptr;\
			i++;\
		}\
	}\
	return arr;\
}\



#endif//SH_ECS_H

#ifdef __cplusplus
}
#endif//__cplusplus