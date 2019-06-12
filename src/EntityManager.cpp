#include "./EntityManager.h"
#include <iostream>
#include <string>

void EntityManager::ClearData() {
  for (auto& entity: entities) {
    entity -> Destroy();
  }
}

bool EntityManager::hasNoEntities(){
  return entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {

for (int i=0; i< entities.size();i++){
  entities[i]->Update(deltaTime);
    if (!entities[i] -> isActive())
      entities.erase(entities.begin() + i);
  }
}

void EntityManager::Render() {

    for (auto& entity: entities){
      entity->Render();
    }
}

Entity& EntityManager::AddEntity(std::string entityName) {
  Entity *entity = new Entity(*this, entityName);
  entities.emplace_back(entity);
  return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const {
  return entities;
}

Entity* EntityManager::GetEntityByName(std::string entityName)const{
  for (auto* entity:entities){
    if (entity->name.compare(entityName) == 0){
      return entity;
    }
  }
  return NULL;
}

unsigned int EntityManager::getEntityCount() {
  return entities.size();
}

void EntityManager::listAllEntities(){
  for (auto& entity: entities){
    std::cout << "Entity Name: " << entity->name << std::endl;
    //entity->listAllComponents();
  }
}
