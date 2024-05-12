    //
    // Created by jimmy on 30/04/24.
    //

    #ifndef RAYLIB_TEMPLATE_BALL_H
    #define RAYLIB_TEMPLATE_BALL_H

    #include "raylib.h"
    #include <vector>

#include "Lives/Vidas.h"
    #include "raymath.h"
    #include "Hitbox.h"
    #include "Enemy/Enemy.h"



    class Enemy;
    class Ball
    {
    public:

        Ball();
        void Draw() const;
        void Move(int deltaX, int deltaY); // Declaración del método Move
        Vector2 GetPosition() const;
        int GetRadius() const;
        void setPosition(Vector2 pos);
        bool GetSafeRoom();
        void SetSafeRoom(bool safe);
        bool safeRoom;
        Vector2 crums;
        void GetCrumbs();
        void UpdateAnimation();
        void Atacar();

        int frameCounter;
        int currentFrame;
        int frameSpeed;
        Texture2D spritesheet;
        Rectangle sourceRec;
        int time_for_crums;
        int GetLives() const;
        void DecreaseLives();
        bool CheckCollisionWithEnemy(const  Enemy& enemy) const;
        void ResetLives();
        int GetRemainingLives() const;

    private:
        Texture2D sprite;
        Vector2 position;
        int radius;
        Color color;
        int lives;
        static const int INNITIAL_LIVES = 5;
        Vidas vidas;
    };


    #endif //RAYLIB_TEMPLATE_BALL_H
