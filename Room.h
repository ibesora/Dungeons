#pragma once
#include "Tilemap.h"
class Room
{
public:
	enum class RoomType { Start = 0, FourDoors, DownBlocked, UpBlocked, RightBlocked, LeftBlocked, Exit };
	Room(RoomType type, Tilemap *tilemap);
	RoomType getType() { return this->type; }
	Tilemap *getTilemap() { return this->tilemap; }
	void setUpRoom(Room *room) { this->up = room; }
	void setDownRoom(Room *room) { this->down = room; }
	void setLeftRoom(Room *room) { this->left = room; }
	void setRightRoom(Room *room) { this->right = room; }
	Room *getUpRoom() { return this->up; }
	Room *getDownRoom() { return this->down; }
	Room *getLeftRoom() { return this->left; }
	Room *getRightRoom() { return this->right; }
	void draw() { this->tilemap->draw(); }
private:
	RoomType type;
	Tilemap *tilemap;
	Room *up;
	Room *down;
	Room *left;
	Room *right;
};

