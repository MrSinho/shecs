#define EZ_ECS_MAX_ENTITIES 4 //is the maximum number of entities used in total
#define EZ_ECS_MAX_COMPONENTS 4 //is the maximum number of component *types* used in total

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

int main() {
	

	const uint32_t entity0 = ezecsCreateEntity();
	const uint32_t entity1 = ezecsCreateEntity();
	const uint32_t entity2 = ezecsCreateEntity();
	const uint32_t entity3 = ezecsCreateEntity();

	printf("Entities: %i, %i, %i, %i\n", entity0, entity1, entity2, entity3);

	ezecsScene myScene = { 0 };
	
	printf("Camera component ID: %i\n", ezecsCameraID);
	printf("Transform component ID: %i\n", ezecsTransformID);
	printf("Player component ID: %i\n", ezecsPlayerID);

	printf("entity0 has transform component: %i\n", ezecsHasTransform(myScene, entity0));
	Transform *transform = ezecsAddTransform(&myScene, entity0);
	transform->position[0] = 33.33f;
	printf("entity0 has transform component: %i\n", ezecsHasTransform(myScene, entity0));
	
	printf("entity0 transform x position: %f \n", ezecsGetTransform(myScene, entity0)->position[0]);

	ezecsRemoveTransform(&myScene, entity0);
	printf("entity0 has transform component: %i\n", ezecsHasTransform(myScene, entity0));

	ezecsDestroyEntity(&myScene, entity0);

	return 0;
}