# ShECS

A header only Entity Component System written in C. 

## [Build status](https://github.com/MrSinho/ShECS/tree/main/.ShCI)

[![linux_badge](.ShCI/linux-status.svg)](https://github.com/MrSinho/ShECS/tree/main/.ShCI/linux-log.md)
[![windows_badge](.ShCI/windows-status.svg)](https://github.com/MrSinho/ShECS/tree/main/.ShCI/windows-log.md)

## Tutorial:

### Clone

```bash
git clone https://github.com/mrsinho/shecs
cd shecs
```

### Build example

Use cmake to build the [`Example`](https://github.com/MrSinho/ShECS/tree/main/Example/src/Example.c):

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

```bash
./../bin/shecs-example
```

## Implementation

```c
#include <shecs/shEcs.h>
``` 

### Setup component

```c
typedef struct Transform{
	float position[3];
} Transform;

SH_ECS_MAKE_COMPONENT_DEFINITIONS(Transform, 0)
```

### Setup scene and create entity

```c
uint32_t entity = shCreateEntity();

ShScene scene = { 0 };
shCreateScene(&scene, 16, 16); //scene handle: stores entities and components

uint32_t entity = shCreateEntity(&scene);//create an entity

```

### Add components

```c
shAddTransformComponent(scene, entity); //adds a new component

Transform* t = shGetTransform(&scene, entity);
t->position[0] = 33.33f;

printf("%f, \n"t->position[0]);

shRemoveTransformComponent(scene, entity); //removes that component

int hasTransform = shHasTransformComponent(scene, entity);
```

## [Full example](shecs-example/src/shecs-example.c):

```c
#include <shecs/shEcs.h>
#include <stdio.h>


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
	shCreateScene(&scene, 16, 16);

	const uint32_t entity0 = shCreateEntity(&scene);
	const uint32_t entity1 = shCreateEntity(&scene);
	const uint32_t entity2 = shCreateEntity(&scene);
	const uint32_t entity3 = shCreateEntity(&scene);
	
	printf("Scene and components infos:\n");
	printf("Entities:----------%i, %i, %i, %i\n", entity0, entity1, entity2, entity3);
	printf("Camera component ID:--------%i\n", shCameraID);
	printf("Transform component ID:-----%i\n", shTransformID);
	printf("Player component ID:--------%i\n", shPlayerID);

	//edit entity0
	shAddTransform(&scene, entity0)->position[0] = 33.33f;
	shAddCamera(&scene, entity0)->FOV = 45.0f;
	
	//edit entity1
	shAddPlayer(&scene, entity1)->intelligence = -20;

	//edit entity2
	shAddCamera(&scene, entity2);
	shRemoveCamera(&scene, entity2);

	//set material on entity0 and entity1
	Material* mat = calloc(1, sizeof(Material)); 
	if (mat == NULL) { return -1; };
	mat->color = 1;
	mat->shaderPath = "myShader.spv";
	shSetMaterial(&scene, mat, entity0);
	shSetMaterial(&scene, mat, entity1);

	puts("\n");

	printf("Transform info:\n");
	printf("Transform size:-----%i\n", shTransformSize);
	printf("Transform id:-------%i\n", shTransformID);
	
	puts("\n");

	for (uint32_t entity = 0; entity < scene.entity_count; entity++) {

		printf("Entity:---------------------%i\n", entity);
		if (shHasTransform(&scene, entity)) {
			printf("Transform x pos:------------%f\n", shGetTransform(&scene, entity)->position[0]);
		}
		if (shHasCamera(&scene, entity)) {
			printf("Camera fov:-----------------%f\n", shGetCamera(&scene, entity)->FOV);
		}
		if (shHasPlayer(&scene, entity)) {
			printf("Player intelligence:-------%i\n", shGetPlayer(&scene, entity)->intelligence);
		}
		if (shHasMaterial(&scene, entity)) {
			printf("Material color:-------------%i\n", shGetMaterial(&scene, entity)->color);
			printf("Material shader path:-------%s\n", shGetMaterial(&scene, entity)->shaderPath);
		}

		puts("\n");
	}

	puts("\n");

	printf("Components count:\n");
	printf("Transform:------%i\n", shGetTransformCount(scene));
	printf("Camera:---------%i\n", shGetTransformCount(scene));
	printf("Player:---------%i\n", shGetCameraCount(scene));
	printf("Material:-------%i\n", shGetMaterialCount(scene));

	puts("\n");

	shSceneRelease(&scene);

#ifdef _WIN32
	system("pause");
#endif//_WIN32

	return 0;
}

```
