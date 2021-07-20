#define EZ_ECS_MAX_ENTITIES 256 //is the maximum number of entities used in total
#define EZ_ECS_MAX_COMPONENTS 10 //is the maximum number of component *types* used in total

#include <EZ_ECS.h>
#include<stdio.h>


typedef struct Camera {

	float FOV;
	float aspectRatio;
	float n;
	float f;

} Camera;
EZ_ECS_MAKE_COMPONENT_DEFINITIONS(Camera, 0)

typedef struct Transform {
	
	float position[3];
	float rotation[3];
	float scale[3];

} Transform;
EZ_ECS_MAKE_COMPONENT_DEFINITIONS(Transform, 1)

typedef struct Player {

	int strength;
	int intelligence;
	int luck;
	int vitality;

} Player;
EZ_ECS_MAKE_COMPONENT_DEFINITIONS(Player, 2)

typedef struct Material {
	
	int color;
	const char* shaderPath;

} Material;
EZ_ECS_MAKE_COMPONENT_DEFINITIONS(Material, 3)

int main() {
	
	ezecsScene scene;
	ezecsCreateScene(scene);

	const uint32_t entity0 = ezecsCreateEntity();
	const uint32_t entity1 = ezecsCreateEntity();
	const uint32_t entity2 = ezecsCreateEntity();
	const uint32_t entity3 = ezecsCreateEntity();
	
	printf("Entities: %i, %i, %i, %i\n", entity0, entity1, entity2, entity3);
	printf("Camera component ID: %i\n", ezecsCameraID);
	printf("Transform component ID: %i\n", ezecsTransformID);
	printf("Player component ID: %i\n", ezecsPlayerID);

	//entity0 stuff
	ezecsAddTransform(scene, entity0)->position[0] = 33.33f;
	ezecsAddCamera(scene, entity0)->FOV = 45.0f;
	
	//entity1 stuff
	ezecsAddPlayer(scene, entity1)->intelligence = -20;

	Material mat = { 1, "myShader.spv" };
	ezecsSetMaterial(scene, &mat, entity0);
	ezecsSetMaterial(scene, &mat, entity1);

	mat.color = 2;
	mat.shaderPath = "lol";

	printf("Transform size %i \n", ezecsTransformSize);
	printf("Transform id %i \n", ezecsTransformID);

	for (uint32_t entity = 0; entity < EZ_ECS_MAX_ENTITIES; entity++) {
		if (ezecsHasTransform(scene, entity) && !ezecsIsTransformShared(scene, entity)) {
			printf("%f\n", ezecsGetTransform(scene, entity)->position[0]);
		}
		if (ezecsHasCamera(scene, entity) && !ezecsIsCameraShared(scene, entity)) {
			printf("%f\n", ezecsGetCamera(scene, entity)->FOV);
		}
		if (ezecsHasPlayer(scene, entity) && !ezecsIsPlayerShared(scene, entity)) {
			printf("%i\n", ezecsGetPlayer(scene, entity)->intelligence);
		}
		if (ezecsHasMaterial(scene, entity) && ezecsIsMaterialShared(scene, entity)) {
			printf("%i, %s\n", ezecsGetMaterial(scene, entity)->color, ezecsGetMaterial(scene, entity)->shaderPath);
		}
	}

	return 0;
}