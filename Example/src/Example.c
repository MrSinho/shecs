//max entities and max components can have any value, for the example i'll make them equal to 2
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
	
	printf("Camera component ID: %i\n", ezecsCameraComponentID);
	printf("Transform component ID: %i\n", ezecsTransformComponentID);
	printf("Player component ID: %i\n", ezecsPlayerComponentID);

	printf("entity0 has transform component: %i\n", ezecsHasTransformComponent(myScene, entity0));
	Transform *transform = ezecsAddTransformComponent(&myScene, entity0);
	transform->position[0] = 33.33f;
	printf("entity0 has transform component: %i\n", ezecsHasTransformComponent(myScene, entity0));
	
	printf("entity0 transform x position: %f \n", ezecsGetTransformComponent(myScene, entity0)->position[0]);

	ezecsRemoveTransformComponent(&myScene, entity0);
	printf("entity0 has transform component: %i\n", ezecsHasTransformComponent(myScene, entity0));

	ezecsDestroyEntity(&myScene, entity0);

	return 0;
}