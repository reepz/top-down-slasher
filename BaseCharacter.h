#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
protected:
  Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
  Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};;
  Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};;
  Vector2 worldPos{};
  // 1: facing right, -1: facing left
  float rightLeft{1.f};
  // animation variables
  float runningTime{};
  int frame{};
  int maxFrames{6};
  float updateTime{1.f/12.f};
  float speed{2.f};
  float width{};
  float height{};
  Vector2 worldPosLastFrame{};
  float scale{4.0};
  Vector2 velocity{};
public:
  BaseCharacter();
  Vector2 getWorldPos() { return worldPos; }
  void undoMovement();
  Rectangle getCollisionRec();
  virtual void tick(float deltaTime);
  virtual Vector2 getScreenPos() = 0;
  bool getAlive() {return alive;} 
  void setAlive(bool isAlive) {alive = isAlive;}
  ~BaseCharacter();
private:
  bool alive{true};
};

#endif