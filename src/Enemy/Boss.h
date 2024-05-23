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
        BossLives = 15;
    }

    virtual void Draw() const override;
    void SpawnSlime(Vector<Slime> &slimes);
    int GetBossLives();

    void DecreaseBossLives();
};

#endif // SELDA_BOSS_H
