#ifndef ENTITY_H
#define ENTITY_H


#include <vector>
#include <string>
#include <map>
#include "./EntityManager.h"
#include "./Component.h"
#include "./Constants.h"

class Component;
class EntityManager;

class Entity {
private:
  EntityManager& manager;
  bool m_isActive;
  std::vector<Component*> components;
  std::map<const std::type_info*, Component*> componentTypeMap;
public:
  std::string name;
  Entity(EntityManager& manager);
  Entity(EntityManager& manager, std::string name);
  void Update(float deltaTime);
  void Render();
  void Destroy();
  bool isActive() const;
  void listAllComponents();

  template <typename T, typename... TArgs>
  T& AddComponent(TArgs&&... args) {
    T* newComponent(new T(std::forward<TArgs>(args)...));
    newComponent -> owner = this;
    components.emplace_back(newComponent);
    componentTypeMap[&typeid(*newComponent)] = newComponent;
    newComponent->Initialize();
    return *newComponent;
  }

  template <typename T>
  bool HasComponent() const {
    return componentTypeMap.count(&typeid(T));
  }

  template <typename T>
  T* GetComponent() {
    return static_cast<T*> (componentTypeMap[&typeid(T)]);
  }
};

#endif
