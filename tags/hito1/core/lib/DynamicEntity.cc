/*
 * DynamicEntity.cpp
 *
 *  Created on: 12/11/2011
 *      Author: Team Chutaos
 */

#include "DynamicEntity.h"

DynamicEntity::DynamicEntity() {
	setMovable(true);

}

DynamicEntity::~DynamicEntity() {
	setMovable(false);
}
