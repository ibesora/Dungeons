#include "Room.h"
#include "AssetStore.h"

Room::Room(RoomType type, Tilemap* tilemap, const char* objectsLayer, int screenWidth, int screenHeight) {
	this->type = type;
	this->tilemap = tilemap;
	if (objectsLayer != "") {
		this->objectsTilemap = new Tilemap(objectsLayer, "", AssetStore::getInstance().getTilesetTexture());
		this->objectsTilemap->load();
		this->objectsTilemap->setTileSize(16);
		this->objectsTilemap->setTileScale(2);
		this->objectsTilemap->setScreenSize(screenWidth, screenHeight);
	}
	else {
		this->objectsTilemap = nullptr;
	}
	this->up = nullptr;
	this->down = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

void Room::draw() {
	this->tilemap->draw();
	if (this->objectsTilemap) this->objectsTilemap->draw();
}

Room::~Room() {
	delete this->objectsTilemap;
}