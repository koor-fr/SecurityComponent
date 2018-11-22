/*
 * Role.h
 *
 *  Created on: 16 nov. 2018
 *      Author: dominique
 */

#ifndef API_ROLE_H_
#define API_ROLE_H_

#include <memory>
#include <string>

#include "Common.h"


namespace fr::koor::security {

	/**
	 * This class represents the concept of role. A role is associated with a or more users
	 * (eg the user John Doe who has an administrator role).
	 *
	 * @author KooR.fr
	 */
	class Role {
		uint identifier;
		std::string roleName;
	public:

		/**
		 * You cannot directly create a Role. Instead of, use an RoleManager instance.
		 *
		 * @param identifier	The role identifier.
		 * @param roleName		The name of the new role.
		 *
		 * @see fr.koor.security.SecurityManager
		 */
		Role( uint identifier = 0, const std::string & roleName = "unknown" );

		/**
		 * Class destructor.
		 */
		virtual ~Role();


		/**
		 * Returns the unique identifier for this role.
		 *
		 * @return The unique identifier.
		 *
		 * @see fr.koor.security.impl.RoleImpl#setIdentifier
		 */
		uint getIdentifier() const {
			return this->identifier;
		}

		/**
		 * Changes the identifier for this user. Only classes of the <code>fr.koor.security</code> package can use this method.
		 *
		 * @param newIdentifier		The new identifier for this role.
		 *
		 * @see fr.koor.security.Role#getIdentifier
		 */
		void setIdentifier( uint newIdentifier ) {
			this->identifier = newIdentifier;
		}

		/**
		 * Returns the name of this role.
		 *
		 * @return Role name.
		 *
		 * @see fr.koor.security.impl.RoleImpl#setRoleName
		 */
		const std::string & getRoleName() const {
			return this->roleName;
		}

		/**
		 * Changes the name of this role.
		 *
		 * @param newRoleName	The new name of the role.
		 *
		 * @see fr.koor.security.Role#getRoleName
		 */
		void setRoleName( const std::string & newRoleName ) {
			this->roleName = newRoleName;
		}

		/**
		 * Compare two role instances.
		 * @param otherRole The second role object to compare.
		 * @return true if the two objects are equals.
		 */
		bool operator==( const Role & otherRole ) const;
	};

	typedef std::shared_ptr<Role> RolePtr;

}

#endif /* API_ROLE_H_ */
