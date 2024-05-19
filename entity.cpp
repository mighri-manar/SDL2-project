#include "entity.hpp"

Entity::Entity(int x, int y, bool visible) : x(x), y(y), visible(visible), image(nullptr) {}

Entity::~Entity() {}