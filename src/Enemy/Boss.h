#ifndef SELDA_BOSS_H
#define SELDA_BOSS_H

#include "Enemy.h"
#include "Slime.h"

class Boss : public Enemy {
private:
    int BossLives;
public:
    Boss() {
        spritesheet = LoadTexture("../assets/enemyPack/chara_slime.png");
        BossLives = 5;
    }

    virtual void Draw() const override;
    void SpawnSlime(Vector<Slime> &slimes);

};

#endif // SELDA_BOSS_H
