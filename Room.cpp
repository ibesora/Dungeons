#include "Room.h"
#include "AssetStore.h"

Room::Room(RoomType type, Tilemap* tilemap) {
	this->type = type;
	this->tilemap = tilemap;
	this->up = nullptr;
	this->down = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}