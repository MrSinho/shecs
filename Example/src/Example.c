#define FGG_ECS_MAX_ENTITIES 256 //is the maximum number of entities used in total
#define FGG_ECS_MAX_COMPONENTS 10 //is the maximum number of component *types* used in total

#include <fggECS.h>
#include<stdio.h>


typedef struct Camera {

	float FOV;
	float aspectRatio;
	float n;
	float f;

} Camera;
FGG_ECS_MAKE_COMPONENT_DEFINITIONS(Camera, 0)

typedef struct Transform {
	
	float position[3];
	float rotation[3];
	float scale[3];

} Transform;
FGG_ECS_MAKE_COMPONENT_DEFINITIONS(Transform, 1)

typedef struct Player {

	int strength;
	int intelligence;
	int luck;
	int vitality;

} Player;
FGG_ECS_MAKE_COMPONENT_DEFINITIONS(Player, 2)

typedef struct Material {
	
	int color;
	const char* shaderPath;

} Material;
FGG_ECS_MAKE_COMPONENT_DEFINITIONS(Material, 3)

int main() {
	
	FggScene scene = { 0 };
	fggCreateScene(&scene);

	const uint32_t entity0 = fggCreateEntity(&scene);
	const uint32_t entity1 = fggCreateEntity(&scene);
	const uint32_t entity2 = fggCreateEntity(&scene);
	const uint32_t entity3 = fggCreateEntity(&scene);
	
	printf("Entities: %i, %i, %i, %i\n", entity0, entity1, entity2, entity3);
	printf("Camera component ID: %i\n", fggCameraID);
	printf("Transform component ID: %i\n", fggTransformID);
	printf("Player component ID: %i\n", fggPlayerID);

	//entity0 stuff
	fggAddTransform(&scene, entity0)->position[0] = 33.33f;
	fggAddCamera(&scene, entity0)->FOV = 45.0f;
	
	//entity1 stuff
	fggAddPlayer(&scene, entity1)->intelligence = -20;

	Material mat = { 1, "myShader.spv" };
	fggSetMaterial(&scene, &mat, entity0);
	fggSetMaterial(&scene, &mat, entity1);

	mat.color = 2;
	mat.shaderPath = "lol";

	printf("Transform size %i \n", fggTransformSize);
	printf("Transform id %i \n", fggTransformID);

	for (uint32_t entity = 0; entity < FGG_ECS_MAX_ENTITIES; entity++) {
		if (fggHasTransform(&scene, entity) && !fggIsTransformShared(&scene, entity)) {
			printf("%f\n", fggGetTransform(&scene, entity)->position[0]);
		}
		if (fggHasCamera(&scene, entity) && !fggIsCameraShared(&scene, entity)) {
			printf("%f\n", fggGetCamera(&scene, entity)->FOV);
		}
		if (fggHasPlayer(&scene, entity) && !fggIsPlayerShared(&scene, entity)) {
			printf("%i\n", fggGetPlayer(&scene, entity)->intelligence);
		}
		if (fggHasMaterial(&scene, entity) && fggIsMaterialShared(&scene, entity)) {
			printf("%i, %s\n", fggGetMaterial(&scene, entity)->color, fggGetMaterial(&scene, entity)->shaderPath);
		}
	}

	system("pause");

	return 0;
}