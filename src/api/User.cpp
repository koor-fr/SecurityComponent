/*
 * User.cpp
 *
 *  Created on: 16 nov. 2018
 *      Author: dominique
 */

#include "User.h"
#include "SecurityManager.h"

using namespace fr::koor::security;

User::User( SecurityManager & securityManager, uint identifier, const std::string &login, const std::string  & encryptedPassword )
	: securityManager(securityManager), identifier(identifier), login(login), password(encryptedPassword) {
}

User::~User() {
}

bool User::isSamePassword( const std::string & password ) const {
	return this->securityManager.getUserManager()->encryptPassword( password ) == this->password;
}

void User::setPassword( const std::string & newPassword ) {
	this->password = this->securityManager.getUserManager()->encryptPassword( newPassword );
}


std::string User::getFullName() const {
	return this->firstName + " " + this->lastName;
}


bool User::isMemberOfRole( const Role & role ) const {
	for( RolePtr aRole : this->roles ) {
		if ( *aRole == role ) return true;
	}
	return false;
}

bool User::isMemberOfRole( RolePtr role ) const {
	for( RolePtr aRole : this->roles ) {
		if ( *aRole == *role ) return true;
	}
	return false;
}


const std::set<RolePtr> & User::getRoles() const {
	return this->roles;
}


void User::addRole( RolePtr role ) {
	this->roles.insert( role );
}


void User::removeRole( RolePtr role ) {
	this->roles.erase( role );
}
