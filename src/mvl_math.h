#pragma once

typedef struct {
    int x, y;
} Vec2i;

typedef struct {
    float x, y;
} Vec2f;

typedef struct {
    int x, y, z;
} Vec3i;

typedef struct {
    float x, y, z;
} Vec3f;

Vec2i addVec2i(Vec2i a, Vec2i b);
Vec2i subVec2i(Vec2i a, Vec2i b);
Vec2i mulVec2i(Vec2i a, Vec2i b);
Vec2f divVec2i(Vec2i a, Vec2i b);

Vec2f addVec2f(Vec2f a, Vec2f b);
Vec2f subVec2f(Vec2f a, Vec2f b);
Vec2f mulVec2f(Vec2f a, Vec2f b);
Vec2f divVec2f(Vec2f a, Vec2f b);

Vec3i addVec3i(Vec3i a, Vec3i b);
Vec3i subVec3i(Vec3i a, Vec3i b);
Vec3i mulVec3i(Vec3i a, Vec3i b);
Vec3f divVec3i(Vec3i a, Vec3i b);

Vec3f addVec3f(Vec3f a, Vec3f b);
Vec3f subVec3f(Vec3f a, Vec3f b);
Vec3f mulVec3f(Vec3f a, Vec3f b);
Vec3f divVec3f(Vec3f a, Vec3f b);