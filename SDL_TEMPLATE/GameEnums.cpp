#include "GameEnums.h"


std::string getProtoType_Type_Path(Prototype_Type type) {
	std::string path = " ";
	switch (type) {
	case Prototype_Type::PLAYER: path = "assets/images/player-revised.png"; break;
	case Prototype_Type::BULLET: path = "assets/images/bullet.png"; break;
	case Prototype_Type::NORMAL_ENEMY: path = "assets/images/normalEnemy.png"; break;
	case Prototype_Type::MEDIUM_ENEMY: path = "assets/images/mediumEnemy.png"; break;
	case Prototype_Type::LARGE_ENEMY: path = "assets/images/fastEnemy.png"; break;
	default: path = "assets/images/unkown.png"; break;
	}

	return path;
}