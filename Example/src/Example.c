#define SH_ECS_MAX_ENTITIES 256 //is the maximum number of entities used in total
#define SH_ECS_MAX_COMPONENTS 10 //is the maximum number of component *types* used in total

#include <shecs/shECS.h>
#include<stdio.h>


typedef struct Camera {

	float FOV;
	float aspectRatio;
	float n;
	float f;

} Camera;
SH_ECS_MAKE_COMPONENT_DEFINITIONS(Camera, 0)

typedef struct Transform {
	
	float position[3];
	float rotation[3];
	float scale[3];

} Transform;
SH_ECS_MAKE_COMPONENT_DEFINITIONS(Transform, 1)

typedef struct Player {

	int strength;
	int intelligence;
	int luck;
	int vitality;

} Player;
SH_ECS_MAKE_COMPONENT_DEFINITIONS(Player, 2)

typedef struct Material {
	
	int color;
	const char* shaderPath;

} Material;
SH_ECS_MAKE_COMPONENT_DEFINITIONS(Material, 3)

int main() {
	
	ShScene scene = { 0 };
	shCreateScene(&scene);

	const uint32_t entity0 = shCreateEntity(&scene);
	const uint32_t entity1 = shCreateEntity(&scene);
	const uint32_t entity2 = shCreateEntity(&scene);
	const uint32_t entity3 = shCreateEntity(&scene);
	
	printf("Entities: %i, %i, %i, %i\n", entity0, entity1, entity2, entity3);
	printf("Camera component ID: %i\n", shCameraID);
	printf("Transform component ID: %i\n", shTransformID);
	printf("Player component ID: %i\n", shPlayerID);

	//entity0 stuff
	shAddTransform(&scene, entity0)->position[0] = 33.33f;
	shAddCamera(&scene, entity0)->FOV = 45.0f;
	
	//entity1 stuff
	shAddPlayer(&scene, entity1)->intelligence = -20;

	Material* mat = calloc(1, sizeof(Material)); 
	if (mat == NULL) { return -1; };
	mat->color = 1;
	mat->shaderPath = "myShader.spv";
	shSetMaterial(&scene, mat, entity0);
	shSetMaterial(&scene, mat, entity1);
	printf("Transform size %i \n", shTransformSize);
	printf("Transform id %i \n", shTransformID);
		
	printf("SCENE LOOP: \n");
	for (uint32_t entity = 0; entity < scene.entity_count; entity++) {
		if (shHasTransform(&scene, entity)) {
			printf("%f\n", shGetTransform(&scene, entity)->position[0]);
		}
		if (shHasCamera(&scene, entity)) {
			printf("%f\n", shGetCamera(&scene, entity)->FOV);
		}
		if (shHasPlayer(&scene, entity)) {
			printf("%i\n", shGetPlayer(&scene, entity)->intelligence);
		}
		if (shHasMaterial(&scene, entity)) {
			printf("%i, %s\n", shGetMaterial(&scene, entity)->color, shGetMaterial(&scene, entity)->shaderPath);
		}
	}
	printf("COMPONENTS COUNT: ");
	printf("Transform: %i,\nCamera: %i,\nPlayer: %i,\nMaterial: %i\n", 
			shGetTransformCount(scene), shGetCameraCount(scene), shGetPlayerCount(scene), shGetMaterialCount(scene));

	shClearScene(&scene);
	system("pause");

	return 0;
}
