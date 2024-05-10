    #include "ball.h"
    #include "raylib.h"
    #include "raymath.h"
    #include "Hitbox.h"


    Ball::Ball() : position({400, 300}), radius(6), color(PINK), lives(5), hitbox({400.0f, 300.0f}, 20, 20) {
        }

    int Ball::GetLives() const {
        return lives;
    }
    void Ball::DecreaseLives() {
        lives--;
    }


    void Ball::Draw() const
    {
        DrawCircleV(position, radius, color);
        hitbox.Draw(color);
    }

    void Ball::Move(int deltaX, int deltaY)
    {
        position.x += deltaX;
        position.y += deltaY;
        hitbox.SetRect ({position.x - 10, position.y - 10, static_cast<float>(3.5 * radius), static_cast<float>(3.5 * radius)});
    }

    Vector2 Ball::GetPosition() const
    {
        return position;
    }

    int Ball::GetRadius() const
    {
        return radius;
    }

    void Ball::setPosition(Vector2 pos)
    {
        position = pos;

       hitbox.SetRect({position.x-radius,position.y-radius,static_cast<float>(radius * 2) , static_cast<float>(radius *2)});
    }

    bool Ball::CheckCollisionWithEnemy(const Enemy &enemy) const {
    //    float distance = Vector2Distance(position, enemy.GetPosition());
    //    return distance < radius + enemy.GetRadius();

        return hitbox.CheckCollision(enemy.GetPosition());
    }

    bool Ball::GetSafeRoom()
    {
        return safeRoom;
    }

    void Ball::SetSafeRoom(bool safe)
    {
        safeRoom = safe;
    }

    void Ball::ResetLives() {
        lives = INNITIAL_LIVES;
    }