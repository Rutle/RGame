#ifndef DATALOADER_HH
#define DATALOADER_HH
#include <iostream>
#include <map>
#include <vector>

struct GameObjectTypes
{
    std::string typeName_;
    bool attackable_;
    bool behaviour_;
    bool body_;
    bool container_;
    bool destroyable_;
    bool pickup_;
    GameObjectTypes(std::string typeName, bool attackable, bool behaviour,
                 bool body, bool container, bool destroyable, bool pickup) :
        typeName_{typeName}, attackable_{attackable}, behaviour_{behaviour},
        body_{body}, container_{container}, destroyable_{destroyable},
        pickup_{pickup} {}
    GameObjectTypes(std::string name, const std::vector<bool> &data) :
        typeName_{name}, attackable_{data.at(0)}, behaviour_{data.at(1)},
        body_{data.at(2)}, container_{data.at(3)}, destroyable_{data.at(4)},
        pickup_{data.at(5)} {}
};

struct Monster
{
    std::string name_;
    std::string raceName_;
    std::string typeName_;
    std::string character_;
    std::string color_;
    std::string bodyType_;
    std::string hostility_;
    int str_;
    int dex_;
    int con_;
    int wis_;
    Monster(const std::vector<std::string> &data) :
    name_{data.at(0)}, raceName_{data.at(1)}, typeName_{data.at(2)},
    character_{data.at(3)}, color_{data.at(4)}, bodyType_{data.at(5)},
    hostility_{data.at(6)}
    {
        str_ = std::stoi(data.at(7));
        dex_ = std::stoi(data.at(8));
        con_ = std::stoi(data.at(9));
        wis_ = std::stoi(data.at(10));
    }
};
struct Item
{
    std::string itemName_;
    std::string typeName_;
    Item(const std::vector<std::string> &data) : itemName_{data.at(0)},
         typeName_{data.at(1)}{}
};
enum TileType {
    BASE = 0,
    THIN
};

struct Tile
{
    std::string id_;
    std::string tileName_;
    std::string type_;
    bool walkable_;
    int code_;                  // ASCII code
    std::string description_;
    Tile(const std::vector<std::string> &data, bool walkable, int code) :
        id_{data.at(0)}, tileName_{data.at(1)}, type_{data.at(2)},
        walkable_{walkable}, code_{code}, description_{data.at(3)} {}

};

class DataLoader
{
    public:
        enum DataType {
            TILE = 0,
            ITEM,
            OBJECTTYPE,
            MONSTER
        };

        DataLoader();
        bool init();
        std::map<std::string, std::vector<Monster> > &getMonsterData();
        std::map<std::string, GameObjectTypes> &getObjectTypeData();
        std::map<std::string, Item> &getItemData();
        std::map<std::string, Tile> &getTileData();
    private:
        bool readData(DataLoader::DataType typeToLoad);
        bool readTileData();
        bool readItemData();
        bool readObjectTypeData();
        bool readMonsterData();
        //          TYPENAME, COMPONENTS
        std::map<std::string, GameObjectTypes> gameObjectTypes_;
        //              TYPE, PARAMETERS
        std::map<std::string, std::vector<Monster>> monsters_;
        //              NAME,
        std::map<std::string, Item> items_;
        //                ID, PARAMETERS
        std::map<std::string, Tile> tiles_;

};

#endif // DATALOADER_HH
