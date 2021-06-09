# EZ-ECS

A simple Entity Component System

## Using the EZ-ECS

It's very straitforward: you have to include [`EZ_ECS.hpp`](https://github.com/MrSinho/EZ-ECS/tree/main/EZ_ECS/include) 

```cpp
#include <EZ_ECS/include/EZ_ECS.hpp>
```

## Example:

Start by defining `EZ_ECS_MAX_ENTITIES` and `EZ_ECS_MAX_COMPONENTS` as unsigned integers of any value. 
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
EZ_ECS::AddComponent<MyComponent>(entity);


EZ_ECS::RemoveComponent<MyComponent>(entity);
bool hascomp = EZ_ECS::HasComponent<MyComponent>(entity);

```

### Accessing your components

```cpp
MyComponent *mycomp = EZ_ECS::GetComponent<MyComponent>(entity);

```

If you want to get an 