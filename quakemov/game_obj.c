#include "game_obj.h"

int OBJ_collisionCheckFab(struct obj* a, struct obj* b) {
    return (
        fabsf(a->pos.f[0] - b->pos.f[0]) * 2.0f < (a->size.f[0] + b->size.f[0]) &&
        fabsf(a->pos.f[1] - b->pos.f[1]) * 2.0f < (a->size.f[1] + b->size.f[1]) &&
        fabsf(a->pos.f[2] - b->pos.f[2]) * 2.0f < (a->size.f[2] + b->size.f[2])
        );
}

int OBJ_collisionCheck(struct obj* a, struct obj* b) {
    return (
        a->pos.f[0] - a->size.f[0] < b->pos.f[0] + b->size.f[0] &&
        a->pos.f[0] + a->size.f[0] > b->pos.f[0] - b->size.f[0] &&
        a->pos.f[1] - a->size.f[1] < b->pos.f[1] + b->size.f[1] &&
        a->pos.f[1] + a->size.f[1] > b->pos.f[1] - b->size.f[1] &&
        a->pos.f[2] - a->size.f[2] < b->pos.f[2] + b->size.f[2] &&
        a->pos.f[2] + a->size.f[2] > b->pos.f[2] - b->size.f[2]
        );
}