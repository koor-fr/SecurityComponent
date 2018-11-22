#ifndef API_USER_H_
#define API_USER_H_

#include <ctime>
#include <memory>
#include <set>
#include <string>

#include "Common.h"
#include "Role.h"


namespace fr::koor::security {

	class SecurityManager;

	/**
	 * <p>
	 *     This class represents the concept of user for a considered computer system.
	 *     A user has a number of attributes and a set of roles assigned to it.
	 * </p>
	 * <p>
	 *     Note: you cannot directly create a User. Instead of, use an UserManager instance.
	 * </p>
	 *
	 * @see fr.koor.security.Role
	 * @see fr.koor.security.RoleManager
	 * @see fr.koor.security.SecurityManager
	 * @see fr.koor.security.UserManager
	 *
	 * @author KooR.fr
	 * @since 1.0
	 */
	class User {

		SecurityManager & securityManager;

		int identifier;
		std::string login;
		std::string password;
		uint connectionNumber = 0;
		time_t lastConnection = 0;
		uint consecutiveErrors = 0;
		bool disabled = false;
		std::set<RolePtr> roles;

		std::string firstName = "";
		std::string lastName = "";
		std::string email = "";

	public:

		/**
		 * You cannot directly create a User. The visibility of this constructor is restricted to the <code>fr.koor.security</code> package.
		 * Instead of, use an UserManager instance.
		 *
		 * @param securityManager 	The security manager that produce this user.
		 * @param identifier		The unique identifier of this user.
		 * @param login				The login of this user.
		 * @param encryptedPassword	The password of this user. This password must be already encrypted.
		 *
		 * @throws SecurityManagerException Thrown when you forget to pass a valid SecurityManager
		 *
		 * @see fr.koor.security.SecurityManager
		 */
		User( SecurityManager & securityManager, uint identifier, const std::string &login, const std::string  & encryptedPassword );

		/**
		 * Class destructor.
		 */
		virtual ~User();

		/**
		 * Return the identifier of this user. Normaly, this identified is used as the primary key in the security storage
		 * engine (certainly a relational database). It must be unique within the database. Therefore, you cannot change the
		 * user identifier's.
		 *
		 * @return The user identifier.
		 */
		int getIdentifier() const {
			return this->identifier;
		}



		/**
		 * Returns the user login.
		 * @return The user login.
		 */
		std::string getLogin() const {
			return this->login;
		}

		/**
		 * Change the login for this user.
		 * @param newLogin		The new login to store in this user.
		 */
		void setLogin( const std::string & newLogin ) {
			this->login = newLogin;
		}


		/**
		 * Check if the encrypted string (for the specified password) is the same that the encrypted password store in the used security system (certainly a relational
		 * database).
		 *
		 * @param password	The clear password to compare
		 * @return	true if encrypted version of the password is the same that the user encrypted password. false otherwise.
		 *
		 * @throws SecurityManagerException Thrown if passwords cannot be compared.
		 *
		 * @see fr.koor.security.User#setPassword(String)
		 */
		bool isSamePassword( const std::string & password ) const;


		/**
		 * Set the new password for this user. Note that the password is stored in encrypted format.
		 *
		 * @param newPassword	The new password for this user.
		 *
		 * @throws SecurityManagerException Thrown if security system cannot change the password.
		 *
		 * @see fr.koor.security.User#isSamePassword(String)
		 */
		void setPassword( const std::string & newPassword );


		/**
		 * Returns the connection number of this user. The connection number is increased as each connection time.
		 *
		 * @return The actual connection number.
		 */
		uint getConnectionNumber() const {
			return this->connectionNumber;
		}

		/**
		 * Set the connection number for this user. This method is reserved for the <code>fr.koor.security</code> package.
		 *
		 * @param newConnectionNumber	The new connection number.
		 *
		 * @see fr.koor.security.User#getConnectionNumber()
		 */
		void setConnectionNumber( uint newConnectionNumber ) {
			this->connectionNumber = newConnectionNumber;
		}

		/**
		 * Returns the date and the time of the last connection for this user.
		 *
		 * @return The date of the last connection.
		 */
		time_t getLastConnection() const {
			return this->lastConnection;
		}

		/**
		 * Set the date and the time of the last connection for this user.
		 *
		 * @param lastConnection	The new date and the time of the last connection.
		 *
		 * @see fr.koor.security.User#getLastConnection()
		 */
		void setLastConnection( time_t lastConnection ) {
			this->lastConnection = lastConnection;
		}

		/**
		 * Returns if the user account is disabled.
		 *
		 * @return true is the user account is disabled, false otherwise.
		 */
		bool isDisabled() const {
			return this->disabled;
		}

		/**
		 * Set the disabled state for this user.
		 *
		 * @param isDisabled	The disabled state.
		 *
		 * @see fr.koor.security.User#isDisabled()
		 */
		void setDisabled( bool isDisabled ) {
			this->disabled = isDisabled;
		}

		/**
		 * Returns the consecutive errors number
		 * @return The  consecutive errors number.
		 */
		uint getConsecutiveErrors() const {
			return consecutiveErrors;
		}

		/**
		 * Set the  consecutive error number.
		 *
		 * @param consecutiveErrors	The consecutive errors value.
		 *
		 * @see fr.koor.security.User#getConsecutiveErrors()
		 */
		void setConsecutiveErrors( uint consecutiveErrors ) {
			this->consecutiveErrors = consecutiveErrors;
		}

		/**
		 * Returns the first name of this user.
		 * @return The first name.
		 */
		const std::string & getFirstName() const {
			return this->firstName;
		}

		/**
		 * Changes the first name of this user.
		 * @param firstName The new first name.
		 */
		void setFirstName( const std::string & firstName ) {
			this->firstName = firstName;
		}

		/**
		 * Returns the last name of this user.
		 * @return The last name.
		 */
		const std::string & getLastName() const {
			return this->lastName;
		}

		/**
		 * Changes the last name of this user.
		 * @param lastName The new last name.
		 */
		void setLastName( const std::string & lastName ) {
			this->lastName = lastName;
		}

		/**
		 * Returns the full name (first name and last name) of this user.
		 * @return The full name.
		 */
		std::string getFullName() const;

		/**
		 * Returns the email of this user.
		 * @return The email.
		 */
		const std::string getEmail() const {
			return this->email;
		}

		/**
		 * Changes the email of this user.
		 * @param email The new email.
		 */
		void setEmail( const std::string & email ) {
			this->email = email;
		}

		/**
		 * Checks is this user is associated to the specified role.
		 * @param role	The expected role.
		 * @return true is this user has the specified role, false otherwize.
		 */
		bool isMemberOfRole( const Role & role ) const;

		/**
		 * Checks is this user is associated to the specified role.
		 * @param role	The expected role.
		 * @return true is this user has the specified role, false otherwize.
		 */
		bool isMemberOfRole( RolePtr role ) const;

		/**
		 * Returns a set of all roles associated to this user..
		 * @return The set of roles.
		 */
		const std::set<RolePtr> & getRoles() const;

		/**
		 * Adds another role to this user.
		 * @param role	The new role to affect for this user.
		 */
		void addRole( RolePtr role );

		/**
		 * Removes a role to this user.
		 * @param role	The role to remove for this user.
		 */
		void removeRole( RolePtr role );

	};


	typedef std::shared_ptr<User> UserPtr;

}

#endif /* API_USER_H_ */
