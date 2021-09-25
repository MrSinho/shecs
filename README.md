# FggECS

A header only Entity Component System written in C. 

## Build status:

Linux: [![Build Status](https://travis-ci.com/MrSinho/FggECS.svg?branch=main)](https://travis-ci.com/MrSinho/FggECS)

## Example:

### Build example

Use cmake to build the [`Example`](https://github.com/MrSinho/FggECS/tree/main/Example/src/Example.c):

```bash
cmake . 
cmake --build .
./bin/Debug/Example
```

## Implementation

Start by defining `FGG_ECS_MAX_ENTITIES` and `FGG_ECS_MAX_COMPONENTS` as unsigned integers of any value. Then include [`FGG_ECS.h`](https://github.com/MrSinho/FggECS/tree/main/FggECS/include/FggECS.h):

```c
#define FGG_ECS_MAX_ENTITIES 10
#define FGG_ECS_MAX_COMPONENTS 20
#include <FGG_ECS.h>
``` 

### Create an entity and add a component

Define your components and call the macro function `FGG_ECS_MAKE_COMPONENT_DEFINITIONS` and specify the ID you're going to give to the type. This allows to generate the required functions for using the ecs. 

```c
typedef struct Transform{
	
	float position[3];

} Transform;

FGG_ECS_MAKE_COMPONENT_DEFINITIONS(MyComponent, 0)
```

Now you're able to call functions such as the following:

```c
uint32_t entity = fggCreateEntity();

FggScene myScene;
fggCreateScene(myScene); //scene handle: stores entities and components


fggAddTransformComponent(scene, entity); //adds a new component

Transform *t = FggECSGetTransformComponent(scene, entity);
transform->position[0] = 33.33f;

printf("%f, \n"FggECSGetTransformComponent(scene, entity)->position[0]);

fggRemoveTransformComponent(scene, entity); //removes that component

int hasTransform = fggHasTransformComponent(scene, entity);
```
