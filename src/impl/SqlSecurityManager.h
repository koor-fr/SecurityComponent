/*
 * SqlSecurityManager.h
 *
 *  Created on: 17 nov. 2018
 *      Author: dominique
 */

#ifndef IMPL_SQLSECURITYMANAGER_H_
#define IMPL_SQLSECURITYMANAGER_H_

#include <QtSql/QSqlDatabase>

#include "../api/SecurityManager.h"

namespace fr::koor::security {


	/**
	 * <p>
	 *     This security manager (see interface fr.koor.security.SercurityManager)  use a relational database to store the security informations.
	 *     Actually two relational database management systems (also known as RDBMS) are supported : Apache Derby or Maria DB. In future versions, other RDBMS
	 * 	   will be supported. The Qt API is used by this implementation to provide RDBMS access.
	 * </p>
	 *
	 * @see fr.koor.security.SecurityManager
	 *
	 * @author KooR.fr
	 */
	class SqlSecurityManager : public SecurityManager {

		static QSqlDatabase connection;

		UserManagerPtr userManager;
		RoleManagerPtr roleManager;

		std::string hostname;
		std::string database;
		std::string login;
		std::string password;

	public:
		/**
		 * Class constructor.
		 * @param hostname	The hostname or the ip address of the RDBMS.
		 * @param database	The name of the used database.
		 * @param login		The login used to establish the connection.
		 * @param password  The login password to establish the connection.
		 */
		SqlSecurityManager( const std::string & hostname, const std::string & database, const std::string & login, const std::string & password );

		/**
		 * Class destructor.
		 */
		virtual ~SqlSecurityManager();

		/**
		 * Open a session to the considered security service.
		 *
		 * @throws SecurityManagerException	Thrown when connection to the security
		 * 	       service cannot be established.
		 */
		void openSession() override;

		/**
		 * Close the session with the considered security service.
		 *
		 * @throws SecurityManagerException	Thrown when connection to the security
		 *         service cannot be closed.
		 */
		void close() override;

		/**
		 * Returns the role manager associated to this security manager.
		 * A role manager provided methods to manage roles.
		 *
		 * @return The role manager associated to this security manager.
		 */
		RoleManagerPtr getRoleManager() const override {
			return this->roleManager;
		}

		/**
		 * Returns the user manager associated to this security manager.
		 * A user manager provided methods to manage users.
		 *
		 * @return The user manager associated to this security manager.
		 */
		UserManagerPtr getUserManager() const override {
			return this->userManager;
		}


	private:

		/**
		 * SQL implementation for the UserManager interface.
		 *
		 * @author KooR.fr
		 */
		class SqlUserManager : public UserManager {
			SqlSecurityManager & securityManager;
		public:
			SqlUserManager( const SqlSecurityManager & securityManager );
			~SqlUserManager() override;

			UserPtr checkCredentials( const std::string & userLogin, const std::string & userPassword ) override;

			UserPtr getUserById( uint userId ) const override;

			UserPtr getUserByLogin( const std::string & login ) const override;

			std::vector<UserPtr> getUsersByRole( RolePtr role ) const override;

			UserPtr insertUser( const std::string & login, const std::string & password ) override;

			void updateUser( UserPtr user ) override;

			void deleteUser( UserPtr user ) override;

			std::string encryptPassword( const std::string & clearPassword ) const override;

		};

		/**
		 * SQL implementation for the RoleManager interface.
		 *
		 * @author KooR.fr
		 */
		class SqlRoleManager : public RoleManager {
			SqlSecurityManager & securityManager;
		public:
			SqlRoleManager( const SqlSecurityManager & securityManager );
			~SqlRoleManager() override;


			RolePtr selectRoleById( uint roleIdentifier ) override;

			RolePtr selectRoleByName( const std::string & roleName ) override;

			RolePtr insertRole( const std::string & roleName ) override;

			void updateRole( RolePtr role ) override;

			void deleteRole( RolePtr role ) override;

		};

		//friend class SqlRoleManager;
	};

}

#endif /* IMPL_SQLSECURITYMANAGER_H_ */
