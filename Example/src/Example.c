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
	
	FggECSScene scene;
	fggECSCreateScene(scene);

	const uint32_t entity0 = fggECSCreateEntity();
	const uint32_t entity1 = fggECSCreateEntity();
	const uint32_t entity2 = fggECSCreateEntity();
	const uint32_t entity3 = fggECSCreateEntity();
	
	printf("Entities: %i, %i, %i, %i\n", entity0, entity1, entity2, entity3);
	printf("Camera component ID: %i\n", fggECSCameraID);
	printf("Transform component ID: %i\n", fggECSTransformID);
	printf("Player component ID: %i\n", fggECSPlayerID);

	//entity0 stuff
	fggECSAddTransform(scene, entity0)->position[0] = 33.33f;
	fggECSAddCamera(scene, entity0)->FOV = 45.0f;
	
	//entity1 stuff
	fggECSAddPlayer(scene, entity1)->intelligence = -20;

	Material mat = { 1, "myShader.spv" };
	fggECSSetMaterial(scene, &mat, entity0);
	fggECSSetMaterial(scene, &mat, entity1);

	mat.color = 2;
	mat.shaderPath = "lol";

	printf("Transform size %i \n", fggECSTransformSize);
	printf("Transform id %i \n", fggECSTransformID);

	for (uint32_t entity = 0; entity < FGG_ECS_MAX_ENTITIES; entity++) {
		if (fggECSHasTransform(scene, entity) && !fggECSIsTransformShared(scene, entity)) {
			printf("%f\n", fggECSGetTransform(scene, entity)->position[0]);
		}
		if (fggECSHasCamera(scene, entity) && !fggECSIsCameraShared(scene, entity)) {
			printf("%f\n", fggECSGetCamera(scene, entity)->FOV);
		}
		if (fggECSHasPlayer(scene, entity) && !fggECSIsPlayerShared(scene, entity)) {
			printf("%i\n", fggECSGetPlayer(scene, entity)->intelligence);
		}
		if (fggECSHasMaterial(scene, entity) && fggECSIsMaterialShared(scene, entity)) {
			printf("%i, %s\n", fggECSGetMaterial(scene, entity)->color, fggECSGetMaterial(scene, entity)->shaderPath);
		}
	}

	system("pause");

	return 0;
}