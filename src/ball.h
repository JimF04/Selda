    //
    // Created by jimmy on 30/04/24.
    //

    #ifndef RAYLIB_TEMPLATE_BALL_H
    #define RAYLIB_TEMPLATE_BALL_H

    #include "raylib.h"
    #include <vector>
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
        void Defender();
        void Dano();

        Vector4 collisionBox;

        int frameCounter;
        int currentFrame;
        int frameSpeed;
        int lives;
        Texture2D spritesheet;
        Rectangle sourceRec;
        int time_for_crums;
        int GetLives() const;
        void DecreaseLives(int damageDealt);
        bool CheckCollisionWithEnemy(const  Enemy& enemy) const;
        bool CheckDeath();
        int ResetLives();
        void DrawHearts(Camera2D camera) const;
        void IncreaseLives();
        Texture2D heartTexture;



    private:
        Texture2D sprite;
        Vector2 position;
        int radius;
        Color color;

        //Vidas vidas;
    };


    #endif //RAYLIB_TEMPLATE_BALL_H
