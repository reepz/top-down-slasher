#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
  int windowWidth{640};
  int windowHeight{480};
  InitWindow(windowWidth, windowHeight, "Top Down Slasher");
  
  Texture2D tileset= LoadTexture("nature_tileset/nature_tileset.png");
  Vector2 mapPos{0.0, 0.0};
  const float mapScale{4.0f};

  Character knight{windowWidth, windowHeight};
  
  Prop props[2]{
    {Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
    {Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
  };


  Enemy goblin{
              Vector2{800.f, 300.f}, 
              LoadTexture("characters/goblin_idle_spritesheet.png"),
              LoadTexture("characters/goblin_run_spritesheet.png")
              };

  Enemy slime{
            Vector2{500.f, 700.f}, 
            LoadTexture("characters/slime_idle_spritesheet.png"),
            LoadTexture("characters/slime_run_spritesheet.png")
           };

  Enemy* enemies[]{
    &goblin,
    &slime
  };

  for (auto enemy : enemies)
  {
    enemy->setTarget(&knight);
  }

  SetTargetFPS(144);

  while(!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
    // draw the map
    DrawTextureEx(tileset, mapPos, 0.0, mapScale, WHITE);
    
    // draw the props
    for (auto prop : props)
    {
      prop.Render(knight.getWorldPos());
    }
    
    if (!knight.getAlive())
    {
      DrawText("game over!", 55.f, 45.f, 40.f, RED);

      EndDrawing();
      continue;
    }
    else
    {
      std::string knightsHealth = "Health: ";
      knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
      DrawText(knightsHealth.c_str(), 55.f, 45.f, 40.f, RED);
    }
    

    knight.tick(GetFrameTime());

    // check map bounds
    if (knight.getWorldPos().x < 0.f ||
        knight.getWorldPos().y < 0.f ||
        knight.getWorldPos().x + windowWidth > tileset.width * mapScale ||
        knight.getWorldPos().y + windowHeight > tileset.height * mapScale)
    {
      knight.undoMovement();
    }
    
    // check prop coillision
    for (auto prop : props)
    {
      if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
      {
        knight.undoMovement();
      };
    }

    for (auto enemy : enemies)
    {
      enemy->tick(GetFrameTime());
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      for (auto enemy : enemies)
      {
      if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
        {
          enemy->setAlive(false);
        }
      }
    }
    EndDrawing();
  }

  UnloadTexture(tileset);
  CloseWindow();
}