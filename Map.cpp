#include "Map.h"
#include "AssetStore.h"
#include "GameStatus.h"
#include "WinScreen.h"

Map::Map() {
    this->screenHeight = 0;
    this->screenWidth = 0;
    this->timesAtTheBeginning = 0;
    this->lastDoorTraversed = (Tilemap::FloorValues)0;
    this->currentRoom = nullptr;
    this->previousRoom = nullptr;
}

void Map::buildMap() {
    // Load all the tilemaps once
    const Texture2D tileset = AssetStore::getInstance().getTilesetTexture();
    Tilemap *startTilemap = new Tilemap("resources/tilemaps/start.bmp", "resources/tilemaps/start-colliders.bmp", tileset);
    startTilemap->load();
    startTilemap->setTileSize(16);
    startTilemap->setTileScale(2);
    startTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(startTilemap);
    Tilemap *fourDoorsTilemap = new Tilemap("resources/tilemaps/4-doors.bmp", "resources/tilemaps/4-doors-colliders.bmp", tileset);
    fourDoorsTilemap->load();
    fourDoorsTilemap->setTileSize(16);
    fourDoorsTilemap->setTileScale(2);
    fourDoorsTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(fourDoorsTilemap);
    Tilemap *downBlockedTilemap = new Tilemap("resources/tilemaps/down-blocked.bmp", "resources/tilemaps/down-blocked-colliders.bmp", tileset);
    downBlockedTilemap->load();
    downBlockedTilemap->setTileSize(16);
    downBlockedTilemap->setTileScale(2);
    downBlockedTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(downBlockedTilemap);
    Tilemap *upBlockedTilemap = new Tilemap("resources/tilemaps/up-blocked.bmp", "resources/tilemaps/up-blocked-colliders.bmp", tileset);
    upBlockedTilemap->load();
    upBlockedTilemap->setTileSize(16);
    upBlockedTilemap->setTileScale(2);
    upBlockedTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(upBlockedTilemap);
    Tilemap *leftBlockedTilemap = new Tilemap("resources/tilemaps/left-blocked.bmp", "resources/tilemaps/left-blocked-colliders.bmp", tileset);
    leftBlockedTilemap->load();
    leftBlockedTilemap->setTileSize(16);
    leftBlockedTilemap->setTileScale(2);
    leftBlockedTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(leftBlockedTilemap);
    Tilemap *rightBlockedTilemap = new Tilemap("resources/tilemaps/right-blocked.bmp", "resources/tilemaps/right-blocked-colliders.bmp", tileset);
    rightBlockedTilemap->load();
    rightBlockedTilemap->setTileSize(16);
    rightBlockedTilemap->setTileScale(2);
    rightBlockedTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(rightBlockedTilemap);
    Tilemap *exitTilemap = new Tilemap("resources/tilemaps/exit.bmp", "resources/tilemaps/exit-colliders.bmp", tileset);
    exitTilemap->load();
    exitTilemap->setTileSize(16);
    exitTilemap->setTileScale(2);
    exitTilemap->setScreenSize(this->screenWidth, this->screenHeight);
    this->tilemaps.push_back(exitTilemap);

    // Create all the needed rooms
    Room *start = new Room(Room::RoomType::Start, startTilemap);
    this->rooms.push_back(start);
    Room *fourDoors1 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects1.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors1);
    Room *fourDoors2 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects2.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors2);
    Room *fourDoors3 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects3.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors3);
    Room *fourDoors4 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects4.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors4);
    Room *fourDoors5 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects5.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors5);
    Room *fourDoors6 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects6.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors6);
    Room *fourDoors7 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects7.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors7);
    Room *fourDoors8 = new Room(Room::RoomType::FourDoors, fourDoorsTilemap, "resources/tilemaps/objects8.txt", this->screenWidth, this->screenHeight);
    this->rooms.push_back(fourDoors8);
    Room *exit = new Room(Room::RoomType::Exit, exitTilemap);
    this->rooms.push_back(exit);
    Room *upBlocked = new Room(Room::RoomType::UpBlocked, upBlockedTilemap);
    this->rooms.push_back(upBlocked);
    Room *downBlocked = new Room(Room::RoomType::DownBlocked, downBlockedTilemap);
    this->rooms.push_back(downBlocked);
    Room *leftBlocked = new Room(Room::RoomType::LeftBlocked, leftBlockedTilemap);
    this->rooms.push_back(leftBlocked);
    Room *rightBlocked = new Room(Room::RoomType::RightBlocked, rightBlockedTilemap);
    this->rooms.push_back(rightBlocked);

    // Link rooms between them
    // Rooms follow the konami code: start - ^ - ^ - v - v - < - > - < - > - exit
    start->setUpRoom(fourDoors1);
    fourDoors1->setUpRoom(fourDoors2);
    fourDoors1->setDownRoom(downBlocked);
    fourDoors1->setLeftRoom(leftBlocked);
    fourDoors1->setRightRoom(rightBlocked);
    fourDoors2->setUpRoom(fourDoors3);
    fourDoors2->setDownRoom(downBlocked);
    fourDoors2->setLeftRoom(leftBlocked);
    fourDoors2->setRightRoom(rightBlocked);
    fourDoors3->setUpRoom(upBlocked);
    fourDoors3->setDownRoom(fourDoors4);
    fourDoors3->setLeftRoom(leftBlocked);
    fourDoors3->setRightRoom(rightBlocked);
    fourDoors4->setUpRoom(upBlocked);
    fourDoors4->setDownRoom(fourDoors5);
    fourDoors4->setLeftRoom(leftBlocked);
    fourDoors4->setRightRoom(rightBlocked);
    fourDoors5->setUpRoom(upBlocked);
    fourDoors5->setDownRoom(downBlocked);
    fourDoors5->setLeftRoom(fourDoors6);
    fourDoors5->setRightRoom(rightBlocked);
    fourDoors6->setUpRoom(upBlocked);
    fourDoors6->setDownRoom(downBlocked);
    fourDoors6->setLeftRoom(leftBlocked);
    fourDoors6->setRightRoom(fourDoors7);
    fourDoors7->setUpRoom(upBlocked);
    fourDoors7->setDownRoom(downBlocked);
    fourDoors7->setLeftRoom(fourDoors8);
    fourDoors7->setRightRoom(rightBlocked);
    fourDoors8->setUpRoom(upBlocked);
    fourDoors8->setDownRoom(downBlocked);
    fourDoors8->setLeftRoom(leftBlocked);
    fourDoors8->setRightRoom(exit);
}

void Map::reset() {
    this->timesAtTheBeginning = 0;
    this->changeRoom(this->rooms[0]);
}

void Map::setScreenSize(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->buildMap();
    this->reset();
}

void Map::draw() {
    this->currentRoom->draw();
}

Vector2 Map::getPlayerStartingPosition() {
    // TODO: This could be a cell value in each tilemap
    const int offset = 170;
    if (this->currentRoom->getType() == Room::RoomType::Start) { return { this->screenWidth / 2.0f, this->screenHeight / 2.0f + offset / 2.0f }; }
    else if (this->currentRoom->getType() == Room::RoomType::DownBlocked) { return { this->screenWidth / 2.0f, this->screenHeight / 2.0f - offset }; }
    else if (this->currentRoom->getType() == Room::RoomType::UpBlocked) { return { this->screenWidth / 2.0f, this->screenHeight / 2.0f + offset }; }
    else if (this->currentRoom->getType() == Room::RoomType::LeftBlocked) { return { this->screenWidth / 2.0f + offset, this->screenHeight / 2.0f }; }
    else if (this->currentRoom->getType() == Room::RoomType::RightBlocked) { return { this->screenWidth / 2.0f - offset, this->screenHeight / 2.0f}; }
    else if (this->currentRoom->getType() == Room::RoomType::Exit) { return { this->screenWidth / 2.0f - offset, this->screenHeight / 2.0f }; }
    else if (this->currentRoom->getType() == Room::RoomType::FourDoors) {
        if (this->lastDoorTraversed == Tilemap::FloorValues::DownDoor) { return { this->screenWidth / 2.0f, this->screenHeight / 2.0f - offset }; }
        else if (this->lastDoorTraversed == Tilemap::FloorValues::UpDoor) { return { this->screenWidth / 2.0f, this->screenHeight / 2.0f + offset }; }
        else if (this->lastDoorTraversed == Tilemap::FloorValues::LeftDoor) { return { this->screenWidth / 2.0f + offset, this->screenHeight / 2.0f }; }
        else { return { this->screenWidth / 2.0f - offset, this->screenHeight / 2.0f }; }

    }
    return { 0, 0 };
}

Map &Map::getInstance() {
    static Map instance;
    return instance;
}

void Map::unload() {
    for (Tilemap *t : this->tilemaps) {
        delete t;
    }

    for (Room *r : this->rooms) {
        delete r;
    }
}

Vector2 Map::movePlayer(Rectangle oldPlayer, Rectangle newPlayer) {
    std::vector<int> values = this->currentRoom->getTilemap()->getRectValues(newPlayer);
    if (this->currentRoom->getObjectsTilemap()) {
        // We add objects as colliders
        std::vector<int> objectValues = this->currentRoom->getObjectsTilemap()->getRectValues(newPlayer);
        for (int i : objectValues) {
            if (i != 0) values.push_back((int)Tilemap::FloorValues::Collision);
        }
    }
    std::vector<int>::iterator it = std::find(values.begin(), values.end(), (int)Tilemap::FloorValues::Collision);
    Vector2 newPosition = { (float)newPlayer.x, (float)newPlayer.y };
    if (it != values.end()) newPosition = { (float)oldPlayer.x, (float)oldPlayer.y };
    else {
        for (int i : values) {
            if (i == (int)Tilemap::FloorValues::DownDoor) {
                this->lastDoorTraversed = Tilemap::FloorValues::DownDoor;
                if (this->currentRoom->getType() == Room::RoomType::UpBlocked) {
                    this->changeRoom(this->previousRoom);
                } else this->changeRoom(this->currentRoom->getDownRoom());
                newPosition = this->getPlayerStartingPosition();
                break;
            } else if (i == (int)Tilemap::FloorValues::UpDoor) {
                this->lastDoorTraversed = Tilemap::FloorValues::UpDoor;
                if (this->currentRoom->getType() == Room::RoomType::DownBlocked) {
                    this->changeRoom(this->previousRoom);
                }
                else this->changeRoom(this->currentRoom->getUpRoom());
                newPosition = this->getPlayerStartingPosition();
                break;
            } else if (i == (int)Tilemap::FloorValues::RightDoor) {
                this->lastDoorTraversed = Tilemap::FloorValues::RightDoor;
                if (this->currentRoom->getType() == Room::RoomType::LeftBlocked) {
                    this->changeRoom(this->previousRoom);
                }
                else if (this->currentRoom->getType() == Room::RoomType::Exit) {
                    GameStatus::getInstance().changeCurrentScreen(new WinScreen(this->screenWidth, this->screenWidth));
                }
                else this->changeRoom(this->currentRoom->getRightRoom());
                newPosition = this->getPlayerStartingPosition();
                break;
            } else if (i == (int)Tilemap::FloorValues::LeftDoor) {
                this->lastDoorTraversed = Tilemap::FloorValues::LeftDoor;
                if (this->currentRoom->getType() == Room::RoomType::RightBlocked) {
                    this->changeRoom(this->previousRoom);
                } else this->changeRoom(this->currentRoom->getLeftRoom());
                newPosition = this->getPlayerStartingPosition();
                break;
            } else if (i == (int)Tilemap::FloorValues::Start) {
                this->changeRoom(this->rooms[0]);
                newPosition = this->getPlayerStartingPosition();
                break;
            }
        }
    }
    return newPosition;
}

void Map::changeRoom(Room *nextRoom) {
    this->previousRoom = this->currentRoom;
    this->currentRoom = nextRoom;
    if (this->currentRoom->getType() == Room::RoomType::Start) {
        this->timesAtTheBeginning++;
    }
}

int Map::getTimesAtTheBeginning() { return this->timesAtTheBeginning; }