#include "GameEnums.h"


std::string getProtoType_Type_Path(Prototype_Type type) {
	std::string path = " ";
	switch (type) {
	case Prototype_Type::PLAYER: path = "assets/images/player-Sheet.png"; break;
	case Prototype_Type::SMALL_ENEMY: path = "assets/images/small_enemy-Sheet.png"; break;
	default: path = "assets/images/unkown.png"; break;
	}

	return path;
}