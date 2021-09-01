#include "rdata.hh"
namespace Data {
std::map<MonsterTypes, std::string> mTypeData{
    {MonsterTypes::BEAST, "Beast"}, {MonsterTypes::DRAGON, "Dragon"},
    {MonsterTypes::ELEMENTAL, "Elemental"},
    {MonsterTypes::HUMANOID, "Humanoid"}, {MonsterTypes::UNDEAD, "Undead"},
    {MonsterTypes::DEMON, "Demon"}};

std::string mTypeS(MonsterTypes type) {
    return mTypeData.at(type);
}

} // Data
