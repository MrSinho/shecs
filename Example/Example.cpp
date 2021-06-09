#include <iostream>
#include <array>

#define MAX_ENTITIES 2
#define MAX_COMPONENTS 2 //is the maximum number of component *types* used in total, in all ECSs, not for each object
#include <UE_ECS.hpp>

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

	uint32_t entity = ECS::CreateEntity();
	uint32_t entity1 = ECS::CreateEntity();

	std::cout << "Entity ID: " << entity << std::endl;
	std::cout << "Entity ID: " << entity1 << std::endl;

	
	std::cout << "Component ID: " << ECS::GetComponentID<Transform>() << std::endl;
	std::cout << "Component ID: " << ECS::GetComponentID<Transform>() << std::endl;
	std::cout << "Component ID: " << ECS::GetComponentID<Mesh>() << std::endl;

	ECS::AddComponent<Transform>(entity);

	std::cout << "entity has Transform:  " << ECS::HasComponent<Transform>(entity) << std::endl;
	std::cout << "entity has Mesh:       " << ECS::HasComponent<Mesh>(entity) << std::endl;
	ECS::AddComponent<Mesh>(entity);
	std::cout << "entity has Mesh:       " << ECS::HasComponent<Mesh>(entity) << std::endl;
	ECS::RemoveComponent<Mesh>(entity);
	std::cout << "entity has Mesh:       " << ECS::HasComponent<Mesh>(entity) << std::endl;

	//uint32_t entity3 = ECS::CreateEntity(); //throws error: reached maximum entities!!
	//ECS::AddComponent<Button>(entity1); //throws error: reached maximum component types!!

	ECS::AddComponent<Transform>(entity1);
	std::cout << "entity1 has Transform: " << ECS::HasComponent<Transform>(entity1) << std::endl;

	std::cout << ECS::GetComponent<Transform>(entity1)->position[0] << std::endl;

	std::cin.get();

	return 0;
}