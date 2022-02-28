#include "mvl_math.h"

Vec2i addVec2i(Vec2i a, Vec2i b) { return (Vec2i){a.x + b.x, a.y + b.y}; }
Vec2i subVec2i(Vec2i a, Vec2i b) { return (Vec2i){a.x - b.x, a.y - b.y}; }
Vec2i mulVec2i(Vec2i a, Vec2i b) { return (Vec2i){a.x * b.x, a.y * b.y}; }
Vec2f divVec2i(Vec2i a, Vec2i b) { return (Vec2f){a.x / (float)b.x, a.y / (float)b.y}; }

Vec2f addVec2f(Vec2f a, Vec2f b) { return (Vec2f){a.x + b.x, a.y + b.y}; }
Vec2f subVec2f(Vec2f a, Vec2f b) { return (Vec2f){a.x - b.x, a.y - b.y}; }
Vec2f mulVec2f(Vec2f a, Vec2f b) { return (Vec2f){a.x * b.x, a.y * b.y}; }
Vec2f divVec2f(Vec2f a, Vec2f b) { return (Vec2f){a.x / b.x, a.y / b.y}; }

Vec3i addVec3i(Vec3i a, Vec3i b) { return (Vec3i){a.x + b.x, a.y + b.y, a.z + b.z}; }
Vec3i subVec3i(Vec3i a, Vec3i b) { return (Vec3i){a.x - b.x, a.y - b.y, a.z - b.z}; }
Vec3i mulVec3i(Vec3i a, Vec3i b) { return (Vec3i){a.x * b.x, a.y * b.y, a.z * b.z}; }
Vec3f divVec3i(Vec3i a, Vec3i b) { return (Vec3f){a.x / (float)b.x, a.y / (float)b.y, a.z / (float)b.z}; }

Vec3f addVec3f(Vec3f a, Vec3f b) { return (Vec3f){a.x + b.x, a.y + b.y, a.z + b.z}; }
Vec3f subVec3f(Vec3f a, Vec3f b) { return (Vec3f){a.x - b.x, a.y - b.y, a.z - b.z}; }
Vec3f mulVec3f(Vec3f a, Vec3f b) { return (Vec3f){a.x * b.x, a.y * b.y, a.z * b.z}; }
Vec3f divVec3f(Vec3f a, Vec3f b) { return (Vec3f){a.x / b.x, a.y / b.y, a.z / b.z}; }