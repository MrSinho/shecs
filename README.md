# EZ-ECS

A simple Entity Component System, not the purest. 

## Example:

### Build example

Use cmake to build the [`Example`](https://github.com/MrSinho/EZ-ECS/blob/main/Example/Example.cpp):

```cpp
cmake . 
cmake --build .
start bin/Debug/Example.exe
```

## Implementation

Start by defining `EZ_ECS_MAX_ENTITIES` and `EZ_ECS_MAX_COMPONENTS` as unsigned integers of any value. Then include [`EZ_ECS.hpp`](https://github.com/MrSinho/EZ-ECS/tree/main/EZ_ECS/include):

```cpp
#define EZ_ECS_MAX_ENTITIES 64
#define EZ_ECS_MAX_COMPONENTS 128
#include <EZ_ECS/include/EZ_ECS.hpp>
``` 

### Create an entity and add a component

Define your components and use the following functions to create an entity, add and remove components from the entity.

```cpp
struct MyComponent {
	float myFloat = 0.0f;
};

uint32_t entity = EZ_ECS::CreateEntity();

EZ_ECS::AddComponent<MyComponent>(entity); //adds a new component

EZ_ECS::RemoveComponent<MyComponent>(entity); //removes that component

bool hascomp = EZ_ECS::HasComponent<MyComponent>(entity);

```

### Accessing your components

```cpp
MyComponent *mycomp = EZ_ECS::GetComponent<MyComponent>(entity); //returns the component of the given type, relative to the entity

std::vector<MyComponent*> compArray = EZ_ECS::View<MyComponent>(); //returns a vector of all components of the given type 

```
