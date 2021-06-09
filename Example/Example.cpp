#include <iostream>
#include <array>

//max entities and max components can have any value, for the example i'll make them equal to 2
#define EZ_ECS_MAX_ENTITIES 2
#define EZ_ECS_MAX_COMPONENTS 2 //is the maximum number of component *types* used in total, in all ECSs, not for each object
#include <EZ_ECS.hpp>

struct Transform {
	std::array<float, 3> position = {20};
	std::array<float, 3> rotation;
	std::array<float, 3> scale;
};

struct Mesh {
	const char* path;
	float vertices[10];
	float indices[2];
};

struct Button {
	bool pressed;
};

int main() {

	uint32_t entity = EZ_ECS::CreateEntity();
	uint32_t entity1 = EZ_ECS::CreateEntity();

	std::cout << "Entity ID: " << entity << std::endl;
	std::cout << "Entity ID: " << entity1 << std::endl;

	EZ_ECS::AddComponent<Transform>(entity);

	std::cout << "entity has Transform:  " << EZ_ECS::HasComponent<Transform>(entity) << std::endl;
	std::cout << "entity has Mesh:       " << EZ_ECS::HasComponent<Mesh>(entity) << std::endl;
	EZ_ECS::AddComponent<Mesh>(entity);
	std::cout << "entity has Mesh:       " << EZ_ECS::HasComponent<Mesh>(entity) << std::endl;
	EZ_ECS::RemoveComponent<Mesh>(entity);
	std::cout << "entity has Mesh:       " << EZ_ECS::HasComponent<Mesh>(entity) << std::endl;

	//uint32_t entity3 = ECS::CreateEntity(); //throws error: reached maximum entities!!
	//ECS::AddComponent<Button>(entity1); //throws error: reached maximum component types!!

	EZ_ECS::AddComponent<Transform>(entity1);
	std::cout << "entity1 has Transform: " << EZ_ECS::HasComponent<Transform>(entity1) << std::endl;

	EZ_ECS::GetComponent<Transform>(entity1)->position[0] = 15;

	std::cout << "Accessing all transforms: " << std::endl;
	for (Transform *trans : EZ_ECS::View<Transform>()) {
		std::cout << "		  	  " <<  trans->position[0] << std::endl;
	}

	std::cin.get();

	return 0;
}