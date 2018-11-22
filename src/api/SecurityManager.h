/*
 * SecurityManager.h
 *
 *  Created on: 16 nov. 2018
 *      Author: dominique
 */

#ifndef API_SECURITYMANAGER_H_
#define API_SECURITYMANAGER_H_

#include <stdexcept>
#include <string>
#include <vector>

#include "Common.h"
#include "Role.h"
#include "User.h"


namespace fr::koor::security {

	/**
	 * This base class of exceptions is thrown when a user attempt a bad access into the secure system.
	 *
	 * @see fr.koor.security.SecurityManagerException
	 *
	 * @author KooR.fr
	 */
	class SecurityManagerException : public std::runtime_error {
	public:
		/**
		 * Class constructor.
		 *
		 * @param message The specific exception message to display.
		 */
		SecurityManagerException( const std::string & errorMessage ) : runtime_error( errorMessage ) {}
	};

	/**
	 * This exception type is thrown when the provided account informations there invalid.
	 *
	 * @author KooR.fr
	 */
	class BadCredentialsException : public SecurityManagerException {
	public:
		/**
		 * Class constructor
		 * @param errorMessage	The exception message
		 */
		BadCredentialsException( const std::string & errorMessage ) : SecurityManagerException( errorMessage ) {}
	};

	/**
	 * This exception type is thrown when the account is disabled.
	 *
	 * @author KooR.fr
	 */
	class AccountDisabledException : public SecurityManagerException {
	public:
		/**
		 * Class constructor
		 * @param errorMessage	The exception message
		 */
		AccountDisabledException( const std::string & errorMessage ) : SecurityManagerException( errorMessage ) {}
	};

	/**
	 * This type of exceptions is thrown when a role is already registered into the security manager.
	 *
	 * @see fr.koor.security.SecurityManagerException
	 *
	 * @author KooR.fr
	 */
	class RoleAlreadyRegisteredException : public SecurityManagerException {
	public:
		/**
		 * Class constructor
		 * @param errorMessage	The exception message
		 */
		RoleAlreadyRegisteredException( const std::string & errorMessage ) : SecurityManagerException( errorMessage ) {}
	};

	/**
	 * This type of exceptions is thrown when a unauthorized user attempt to login into the secure system.
	 *
	 * @see fr.koor.security.SecurityManagerException
	 *
	 * @author KooR.fr
	 */
	class UnauthorizedException : public SecurityManagerException {
	public:
		/**
		 * Class constructor
		 * @param errorMessage	The exception message
		 */
		UnauthorizedException( const std::string & errorMessage ) : SecurityManagerException( errorMessage ) {}
	};

	/**
	 * This type of exceptions is thrown when a user is already registered into the security manager.
	 *
	 * @see fr.koor.security.SecurityManagerException
	 *
	 * @author KooR.fr
	 */
	class UserAlreadyRegisteredException : public SecurityManagerException {
	public:
		/**
		 * Class constructor
		 * @param errorMessage	The exception message
		 */
		UserAlreadyRegisteredException( const std::string & errorMessage ) : SecurityManagerException( errorMessage ) {}
	};


	/**
	 * This interface defines the methods used to manage User instances.
	 * To can get a UserManager instance by asking it at your SecurityManager.
	 *
	 * @see fr.koor.security.SecurityManager
	 * @see fr.koor.security.User
	 *
	 * @author KooR.fr
	 */
	class UserManager {
	public:

		/**
		 * Class constructor
		 */
		UserManager() {}

		/**
		 * Class destructor
		 */
		virtual ~UserManager() {}

		/**
		 * Copies are forbidden
		 */
		UserManager( const UserManager & original ) = delete;
		/**
		 * Copies are forbidden
		 */
		UserManager & operator=( const UserManager & original ) = delete;

		/**
		 * Check if the pair login/password represents an autorized user for the considered
		 * application. If the identity is rejected, an exception will thrown. If the
		 * identity is accepted, the connection number of the considered user is increased.
		 *
		 * @param userLogin     The login for the considered user.
		 * @param userPassword  The password for the considered user.
		 * @return              The considered user instance.
		 *
		 * @throws AccountDisabledException  Thrown when the provided account informations there invalid.
		 * @throws BadCredentialsException   Thrown if the identity is rejected.
		 */
		 virtual UserPtr checkCredentials( const std::string & userLogin, const std::string & userPassword ) = 0;

		/**
		 * Retreive the user instance that have the desired identifier.
		 *
		 * @param userId	The user identifier (the primary key into the security database).
		 * @return The selected user instance.

		 * @exception SecurityManagerException
		 *            Thrown if the searched user don't exists.
		 *
		 * @see #checkCredentials(const std::string &, const std::string &)
		 * @see #getUserByLogin(const std::string &)
		 */
		virtual UserPtr getUserById( uint userId ) const = 0;

		/**
		 * Retreive the user instance by its login.
		 *
		 * @param login		The user login.
		 * @return The selected user instance.

		 * @exception SecurityManagerException
		 *            Thrown if the searched user don't exists.
		 *
		 * @see #checkCredentials(const std::string &,const std::string &)
		 * @see #getUserById(int)
		 */
		virtual UserPtr getUserByLogin( const std::string & login ) const = 0;

		/**
		 * Retreive all user instances associated to the specified role.
		 *
		 * @param role		The role that contains expected users.
		 * @return A list of users member of this role.

		 * @exception SecurityManagerException
		 *            Thrown when the search can't finish.
		 *
		 * @see #checkCredentials(const std::string &,const std::string &)
		 * @see #getUserById(int)
		 * @see #getUserByLogin(const std::string &)
		 */
		virtual std::vector<UserPtr> getUsersByRole( RolePtr role ) const = 0;

		/**
		 * Insert a new user in the security system. The new used has the specified
		 * login and the specified password.
		 *
		 * @param login         The login for the considered user.
		 * @param password      The password for the considered user. The specified password
		 *                      is automaticly encoded by this method.
		 * @return              The new user instance.
		 *
		 * @exception SecurityManagerException
		 *            Thrown if the new user cannot be inserted in the security system.
		 * @exception UserAlreadyRegisteredException
		 *            Thrown if the specified login is already registered in the security system.
		 */
		virtual UserPtr insertUser( const std::string & login, const std::string & password ) = 0;

		/**
		 * Update informations, in the security system, for the specified user.
		 *
		 * @param user  The user instance to update.
		 *
		 * @throws SecurityManagerException
		 *         Thrown if this manager cannot update the user informations.
		 */
		virtual void updateUser( UserPtr user ) = 0;

		/**
		 * Delete the specified user from the security system.
		 *
		 * @param user    The user to delete.
		 *
		 * @throws SecurityManagerException
		 *         Thrown if this manager cannot remove the user.
		 */
		virtual void deleteUser( UserPtr user ) = 0;

		/**
		 * Defines the algorithm used for encode password. User password is stored in
		 * encoded format.
		 *
		 * @param clearPassword       A password (in clear).
		 * @return                    The encoded password.
		 *
		 * @throws SecurityManagerException
		 *         Thrown if password encription failed.
		 */
		virtual std::string encryptPassword( const std::string & clearPassword ) const = 0;

	};

	typedef std::shared_ptr<UserManager> UserManagerPtr;


	/**
	 * This interface defines the methods used to manage Role instances.
	 * To can get a RoleManager instance by asking it at your SecurityManager.
	 *
	 * @see fr.koor.security.SecurityManager
	 * @see fr.koor.security.Role
	 *
	 * @author Koor.fr
	 */
	class RoleManager {
	public:
		/**
		 * Class constructor
		 */
		RoleManager() {}

		/**
		 * Class destructor
		 */
		virtual ~RoleManager() {}


		/**
		 * Copies are forbidden
		 */
		RoleManager( const RoleManager & original ) = delete;
		/**
		 * Copies are forbidden
		 */
		RoleManager & operator=( const RoleManager & original ) = delete;


		/**
		 * Select the role with the identifier specified in parameter.
		 *
		 * @param roleIdentifier	The identifier of the role to returns.
		 * @return					The selected role.
		 *
		 * @exception SecurityManagerException
		 * 		Thrown if the searched role don't exists.
		 */
		virtual RolePtr selectRoleById( uint roleIdentifier ) = 0;

		/**
		 * Select the role with the name specified in parameter.
		 *
		 * @param roleName		The name of the role to returns.
		 * @return 				The selected role.
		 *
		 * @exception SecurityManagerException
		 * 		Thrown if the searched role don't exists.
		 */
		virtual RolePtr selectRoleByName( const std::string & roleName ) = 0;

		/**
		 * Insert a new role into the used security system.
		 *
		 * @param roleName		The name of the new role.
		 * @return				The new role.
		 *
		 * @exception SecurityManagerException
		 * 		Thrown if the role cannot be inserted into the security system.
		 * @exception RoleAlreadyRegisteredException
		 * 		Thrown if the specified role name already exists in the security system.
		 */
		virtual RolePtr insertRole( const std::string & roleName ) = 0;

		/**
		 * Update the informations for this role (actually, only the role name).
		 *
		 * @param role	The role to update.
		 *
		 * @exception SecurityManagerException
		 * 		Thrown if the role cannot be updated into the security system.
		 */
		virtual void updateRole( RolePtr role ) = 0;

		/**
		 * Delete, on the security system, the specified role.
		 *
		 * @param role	The role to delete.
		 * @exception SecurityManagerException
		 * 		Thrown if the specified role cannot be deleted from the security system.
		 */
		virtual void deleteRole( RolePtr role ) = 0;

	};

	typedef std::shared_ptr<RoleManager> RoleManagerPtr;


	/**
	 * <p>
	 *     This interface defines methods for access to a security service. A security
	 *     service must provide two mechanisms: authentication and permissions management.
	 *     Authentication consist to identify a user and enable him (or not) connecting
	 *     to the considered system. The management of permissions allows, once the user
	 *     authenticated, him to have an access (or not) to resources.
	 * </p>
	 *
	 * <p>
	 *     In the current version of the Ellipse framework, only authentication is supported.
	 *     But a future version of the framework will add the concepts of permissions. The
	 *     Ellipse framework provides the JdbcSecurityManager class : this is, of course,
	 *     an implementation of this interface that use a relational database to store
	 *     the security informations.
	 * </p>
	 *
	 * @see fr.koor.security.providers.JdbcSecurityManager
	 * @see fr.koor.security.RoleManager
	 * @see fr.koor.security.UserManager
	 *
	 * @author KooR.fr
	 */
	class SecurityManager {
	public:
		/**
		 * Class default constructor.
		 */
		SecurityManager() {}

		/**
		 * Class destructor
		 */
		virtual ~SecurityManager() {}


		/**
		 * Copies are forbidden
		 */
		SecurityManager( const SecurityManager & original ) = delete;
		/**
		 * Copies are forbidden
		 */
		SecurityManager & operator=( const SecurityManager & original ) = delete;


		/**
		 * Open a session to the considered security service.
		 *
		 * @throws SecurityManagerException	Thrown when connection to the security
		 * 	       service cannot be established.
		 */
		virtual void openSession() = 0;

		/**
		 * Close the session with the considered security service.
		 *
		 * @throws SecurityManagerException	Thrown when connection to the security
		 *         service cannot be closed.
		 */
		virtual void close() = 0;

		/**
		 * Returns the role manager associated to this security manager.
		 * A role manager provided methods to manage roles.
		 *
		 * @return The role manager associated to this security manager.
		 */
		virtual RoleManagerPtr getRoleManager() const = 0;

		/**
		 * Returns the user manager associated to this security manager.
		 * A user manager provided methods to manage users.
		 *
		 * @return The user manager associated to this security manager.
		 */
		virtual UserManagerPtr getUserManager() const = 0;
	};

	typedef std::shared_ptr<SecurityManager> SecurityManagerPtr;

}

#endif /* API_SECURITYMANAGER_H_ */
