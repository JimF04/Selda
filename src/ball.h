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
    #include "Objects/Fireball.h"

    enum PlayerDir {
        Player_RIGHT,
        Player_LEFT,
        Player_DOWN,
        Player_UP,
        Player_IDLE
    };

    class Enemy;
    class Ball
    {
    public:

        Ball();
        void Draw() const;
        void Move(int deltaX, int deltaY);
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
        bool IsDefending;
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

        void LaunchFireball() {
            FireBall fireball(position, "player");
            if (lastFireballTime >= fireballCooldown) {
                Vector2 fireballVelocity = {0, 0};


                switch (currentDir) {
                    case Player_RIGHT:
                        fireballVelocity.x = 1.5f;
                        break;
                    case Player_LEFT:
                        fireballVelocity.x = -1.5f;
                        break;
                    case Player_DOWN:
                        fireballVelocity.y = 1.5f;
                        break;
                    case Player_UP:
                        fireballVelocity.y = -1.5f;
                        break;
                    case Player_IDLE:
                        fireballVelocity.x = 1.5f;
                        break;
                    default:

                        break;
                }

                fireball.SetVelocity(fireballVelocity);

                activeFireballs.push_back(fireball);

                lastFireballTime = 0.0f;
            }
        }


        void UpdateFireballs() {

            for (size_t i = 0; i < activeFireballs.size(); ++i) {
                activeFireballs[i].UpdatePosition();
                activeFireballs[i].UpdateAnimation();


                if (Vector2Distance(activeFireballs[i].GetPosition(), position) > maxFireballDistance * 16) {

                    activeFireballs.erase(activeFireballs.begin() + i);

                    --i;
                }
            }
            lastFireballTime += GetFrameTime();
        }

        void DrawFireballs() const {

            for (size_t i = 0; i < activeFireballs.size(); ++i) {
                activeFireballs[i].Draw();
            }
        }

        PlayerDir currentDir;


    private:
        Texture2D sprite;
        Vector2 position;
        int radius;
        Color color;
        std::vector<FireBall> activeFireballs;
        int maxFireballDistance = 3;
        float lastFireballTime;
        float fireballCooldown = 1.0f;

    };


    #endif //RAYLIB_TEMPLATE_BALL_H
