#include <iostream>
#include "./Editor.h"

int main(int argc, char *args[]){
  Editor *editor = new Editor();

  editor -> Initialize(800,600);

  while (editor -> IsRunning()){
    editor -> ProcessInput();
    editor -> Update();
    editor -> Render();
  }

  editor -> Destroy();

  return 0;
}
