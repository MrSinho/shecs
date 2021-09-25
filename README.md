# FggECS

A header only Entity Component System written in C. 

## Build status:

Linux: [![Build Status](https://travis-ci.com/MrSinho/EZ-ECS.svg?branch=main)](https://travis-ci.com/MrSinho/EZ-ECS)

## Example:

### Build example

Use cmake to build the [`Example`](https://github.com/MrSinho/EZ-ECS/tree/main/Example/src/Example.c):

```bash
cmake . 
cmake --build .
./bin/Debug/Example
```

## Implementation

Start by defining `EZ_ECS_MAX_ENTITIES` and `EZ_ECS_MAX_COMPONENTS` as unsigned integers of any value. Then include [`EZ_ECS.h`](https://github.com/MrSinho/EZ-ECS/tree/main/EZ-ECS/include/EZ_ECS.h):

```c
#define EZ_ECS_MAX_ENTITIES 10
#define EZ_ECS_MAX_COMPONENTS 20
#include <EZ_ECS.h>
``` 

### Create an entity and add a component

Define your components and call the macro function `EZ_ECS_MAKE_COMPONENT_DEFINITIONS` and specify the ID you're going to give to the type. This allows to generate the required functions for using the ecs. 

```c
typedef struct Transform{
	
	float position[3];

} Transform;

EZ_ECS_MAKE_COMPONENT_DEFINITIONS(MyComponent, 0)
```

Now you're able to call functions such as the following:

```c
uint32_t entity = ezecsCreateEntity();

ezecsScene myScene;
ezecsCreateScene(myScene); //scene handle: stores entities and components


ezecsAddTransformComponent(scene, entity); //adds a new component

Transform *t = ezecsGetTransformComponent(scene, entity);
transform->position[0] = 33.33f;

printf("%f, \n"ezecsGetTransformComponent(scene, entity)->position[0]);

ezecsRemoveTransformComponent(scene, entity); //removes that component

int hasTransform = ezecsHasTransformComponent(scene, entity);
```
