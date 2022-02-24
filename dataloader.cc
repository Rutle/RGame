#include <fstream>
#include <sstream>
#include "dataloader.hh"

DataLoader::DataLoader()
{
    std::cout << "Dataloader Constructor" << std::endl;
}

bool DataLoader::init()
{
    if (readData(DataType::TILE) && readData(DataType::ITEM) && readData(DataType::MONSTER) && readData(DataType::OBJECTTYPE)) {
        return true;
    }
    return false;
}

std::map<std::string, std::vector<Monster> > &DataLoader::getMonsterData()
{
    return monsters_;
}

std::map<std::string, GameObjectTypes> &DataLoader::getObjectTypeData()
{
    return gameObjectTypes_;
}

std::map<std::string, Item> &DataLoader::getItemData()
{
    return items_;
}

std::map<std::string, Tile> &DataLoader::getTileData()
{
    return tiles_;
}

bool DataLoader::readData(DataType typeToLoad)
{
    switch (typeToLoad) {
        case DataType::TILE:
            if (!readTileData()) return false;
            break;
        case DataType::ITEM:
            if (!readItemData()) return false;
            break;
        case DataType::MONSTER:
            if (!readMonsterData()) return false;
            break;
        case DataType::OBJECTTYPE:
            if (!readObjectTypeData()) return false;
            break;
        default:
            std::cout << "WRONG TYPE!" << std::endl;
            break;
    }
    return true;

}

bool DataLoader::readTileData()
{
    std::ifstream file{"./gameworld/objects/tiles.txt"};

    if ( !file.is_open() ) {
        std::cout << "<TileData>Failed to open file!" << std::endl;
        return false;
    }
    std::string item;
    std::string key;
    bool walkable;
    int code;
    std::vector<std::string> temp;
    std::string line;
    std::stringstream stream;
    while ( file ) {
        line.clear();
        getline(file, line);
        item.clear();
        key.clear();
        temp.clear();
        stream.str("");
        stream.clear();
        stream << line;
        if ( stream.peek() == EOF) {
            continue;
        }
        if ( line.find("//") == std::string::npos ||
             line.find("", 0) == std::string::npos ) {
            while ( stream >> item ) {

                if ( item != ";" ) {
                    if ( isdigit(item.at(0)) ) {
                        code = std::stoi(item);
                    } else if ( item == "no" ) {
                        walkable = false;
                    } else if ( item == "yes" ) {
                        walkable = true;
                    } else {
                        temp.push_back(item);
                    }
                }

            }
            tiles_.insert({temp.at(0), {temp, walkable, code}});

        }

    }
    file.close();
    std::cout << "Tile data read. Size of map: [" << tiles_.size() << "]" << std::endl;
    return true;
}

bool DataLoader::readItemData()
{
    std::ifstream file{"gameworld/objects/items.txt"};
    if ( !file.is_open() ) {
        std::cout << "<ItemData>Failed to open file!" << std::endl;
        return false;
    }

    std::string item;
    std::string key;
    std::vector<std::string> temp;


    std::string line;
    std::stringstream stream;
    while ( file ) {
        line.clear();
        getline(file, line);
        item.clear();
        key.clear();
        temp.clear();
        stream.str("");
        stream.clear();
        stream << line;
        if ( stream.peek() == EOF) {
            continue;
        }
        if ( line.find("//") == std::string::npos ||
             line.find("", 0) == std::string::npos ) {
            // MUUTA OTTAAN TALTEEN SITEN, ETTÄ TYPE ON AVAIN
            stream >> std::ws >> key >> std::ws;
            while ( stream >> item ) {
                if ( item != ";" ) {
                    temp.push_back(item);
                }

            }
            items_.insert({key, Item{temp}});
        }

    }
    file.close();
    std::cout << "Item data read. Size of map: [" << items_.size() << "]" << std::endl;
    return true;
}

bool DataLoader::readObjectTypeData()
{

    std::ifstream file{"gameworld/objects/types.txt"};
    if ( !file.is_open() ) {
        std::cout << "<ObjectTypeData>Failed to open file!" << std::endl;
        return false;
    }

    std::string item;
    std::string key;
    std::vector<bool> temp;
    std::string line;
    std::stringstream stream;
    while ( file ) {
        line.clear();
        getline(file, line);
        item.clear();
        key.clear();
        temp.clear();
        stream.str("");
        stream.clear();
        stream << line;
        if ( stream.peek() == EOF) {
            continue;
        }
        if ( line.find("//") == std::string::npos ||
             line.find("", 0) == std::string::npos ) {
            stream >> std::ws >> key >> std::ws;
            while ( stream >> item ) {
                if ( item != ";" ) {
                    temp.push_back(item == "yes" ? true : false);

                }

            }
            gameObjectTypes_.insert({key, {key, temp}});
        }

    }
    file.close();
    std::cout << "Gameobject data read. Size of map: [" << gameObjectTypes_.size() << "]" << std::endl;
    return true;
}

bool DataLoader::readMonsterData()
{
    std::ifstream file{"gameworld/objects/monsters.txt"};
    if ( !file.is_open() ) {
        std::cout << "<MonsterData>Failed to open file!" << std::endl;
        return false;
    }

    std::string item;
    std::string key;
    std::vector<std::string> temp;
    std::string line;
    std::stringstream stream;
    while ( file ) {
        line.clear();
        getline(file, line);
        item.clear();
        key.clear();
        temp.clear();
        stream.str("");
        stream.clear();
        stream << line;
        if ( stream.peek() == EOF) {
            continue;
        }
        if ( line.find("//") == std::string::npos ||
             line.find("", 0) == std::string::npos ) {

            while ( stream >> item ) {
                if ( item != ";" ) {
                    temp.push_back(item);
                }

            }
            if ( monsters_.find(temp.at(2)) != monsters_.end() ) {
                monsters_.at(temp.at(2)).push_back({temp});
            } else {
                monsters_.insert({temp.at(2), {temp}});
            }

        }

    }
    file.close();
    std::cout << "Monster data read. Size of map: [" << monsters_.size() << "]" << std::endl;
    return true;
}
