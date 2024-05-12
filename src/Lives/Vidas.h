#ifndef VIDAS_H
#define VIDAS_H

class Vidas {
public:
    Vidas(int initialLives);
    void DecreaseLife();
    int GetLives() const;
    bool IsAlive() const;
    void ResetLives();
private:
    int lives;
    int initialLives;
};

#endif // VIDAS_H
