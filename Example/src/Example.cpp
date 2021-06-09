#include <iostream>

#include <array>
#include <vector>

#define MAX_ENTITIES 2
#define MAX_COMPONENTS 2
#include <UE_ECS.h>

struct Transform {
	std::array<float, 3> position;
	std::array<float, 3> rotation;
	std::array<float, 3> scale;
};

struct Mesh {
	const char* path;
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
};

struct Button {
	bool pressed;
};

int main() {

	Scene *scene = new Scene();
	uint32_t entity = scene->CreateEntity();
	uint32_t entity2 = scene->CreateEntity();

	std::cout << "Entity ID: " << entity << std::endl;
	std::cout << "Entity ID: " << entity2 << std::endl;

	
	std::cout << "Component ID: " << GetComponentID<Transform>() << std::endl;
	std::cout << "Component ID: " << GetComponentID<Transform>() << std::endl;
	std::cout << "Component ID: " << GetComponentID<Mesh>() << std::endl;

	scene->AddComponent<Transform>(entity);

	std::cout << "Has Transform: " << scene->HasComponent<Transform>(entity) << std::endl;
	std::cout << "Has Mesh:      " << scene->HasComponent<Mesh>(entity) << std::endl;
	scene->AddComponent<Mesh>(entity);
	std::cout << "Has Mesh:      " << scene->HasComponent<Mesh>(entity) << std::endl;
	scene->RemoveComponent<Mesh>(entity);
	std::cout << "Has Mesh:      " << scene->HasComponent<Mesh>(entity) << std::endl;

	//uint32_t entity3 = scene->CreateEntity(); //throws error: reached maximum entities!!
	scene->AddComponent<Button>(entity2); //issue: max components is applied to every single object!!

	std::cin.get();

	return 0;
}