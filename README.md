# ShECS

A header only Entity Component System written in C. 

## [Build status](https://github.com/MrSinho/PlyImporter/.ShCI)

[![linux_badge](.ShCI/linux-status.svg)](https://github.com/MrSinho/PlyImporter/.ShCI/linux-log.md)
[![windows_badge](.ShCI/windows-status.svg)](https://github.com/MrSinho/PlyImporter/.ShCI/windows-log.md)

## Example:

### Build example

Use cmake to build the [`Example`](https://github.com/MrSinho/ShECS/tree/main/Example/src/Example.c):

```bash
cmake . 
cmake --build .
./bin/ShECSExample
```

## Implementation

Start by defining `SH_ECS_MAX_ENTITIES` and `SH_ECS_MAX_COMPONENTS` as unsigned integers of any value. Then include [`SH_ECS.h`](https://github.com/MrSinho/ShECS/tree/main/ShECS/include/ShECS.h):

```c
#define SH_ECS_MAX_ENTITIES 10
#define SH_ECS_MAX_COMPONENTS 20
#include <SH_ECS.h>
``` 

### Create an entity and add a component

Define your components and call the macro function `SH_ECS_MAKE_COMPONENT_DEFINITIONS` and specify the ID you're going to give to the type. This allows to generate the required functions for using the ecs. 

```c
typedef struct Transform{
	
	float position[3];

} Transform;

SH_ECS_MAKE_COMPONENT_DEFINITIONS(MyComponent, 0)
```

Now you're able to call functions such as the following:

```c
uint32_t entity = shCreateEntity();

ShScene myScene;
shCreateScene(myScene); //scene handle: stores entities and components


shAddTransformComponent(scene, entity); //adds a new component

Transform *t = ShECSGetTransformComponent(scene, entity);
transform->position[0] = 33.33f;

printf("%f, \n"ShECSGetTransformComponent(scene, entity)->position[0]);

shRemoveTransformComponent(scene, entity); //removes that component

int hasTransform = shHasTransformComponent(scene, entity);
```
