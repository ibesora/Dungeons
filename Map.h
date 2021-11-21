#pragma once
#include "Tilemap.h"
#include <vector>
#include "Room.h"

class Map
{
public:
	Map(Map &other) = delete;
	void operator=(const Map &) = delete;
	static Map &getInstance();
	void setScreenSize(int screenWidth, int screenHeight);
	void draw();
	void reset();
	Vector2 getPlayerStartingPosition();
	void unload();
	Vector2 movePlayer(Rectangle oldPlayer, Rectangle newPlayer);
	int getTimesAtTheBeginning();
	int getTimesWTF();
protected:
    Map();
	void buildMap();
	void changeRoom(Room*);
	Room* currentRoom;
	Room* previousRoom;
	Tilemap::FloorValues lastDoorTraversed;
	int screenWidth;
	int screenHeight;
	int timesAtTheBeginning;
	int timesWTF;
	std::vector<Room*> rooms;
	std::vector<Tilemap *> tilemaps;
};

