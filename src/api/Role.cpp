/*
 * Role.cpp
 *
 *  Created on: 16 nov. 2018
 *      Author: dominique
 */

#include "Role.h"

using namespace fr::koor::security;

Role::Role( uint identifier, const std::string & roleName ) : identifier(identifier), roleName(roleName) {
}

Role::~Role() {
}

bool Role::operator==( const Role & otherRole ) const {
	return this->identifier == otherRole.identifier;
}
