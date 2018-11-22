#include <ctime>

#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>

#include "SqlSecurityManager.h"

using namespace std;

using namespace fr::koor::security;


//--------------------------------------------------------------------------------------------
//--- Utility functions ----------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

/**
 * Returns the next used primary key for the specified table and column.
 * Caution: the type of the specified column must be compatible with the int java type.
 *
 * @param tableName		The name of the considered table.
 * @param columnName	The name of the column that contains primary keys.
 * @return The next used value.
 *
 * @throws SecurityManagerException	Thrown if a Sql error is generated.
 */
uint getNextAvailablePrimaryKey( QString tableName, QString columnName ) {
	try {
		QString strSql = "SELECT max(%1) FROM %2";
		strSql = strSql.arg( columnName ).arg( tableName );
		QSqlQuery query( strSql );
		query.exec();
		uint nextIdentifier = 0;
		if ( query.next() ) {
			nextIdentifier = query.value( 0 ).toInt();
		}
		return ++nextIdentifier;
	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Cannot compute next primary key: %1" ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}
}

//--------------------------------------------------------------------------------------------
//--- SqlUserManager implementation ----------------------------------------------------------
//--------------------------------------------------------------------------------------------

SqlSecurityManager::SqlUserManager::SqlUserManager( const SqlSecurityManager & securityManager ) : securityManager(const_cast<SqlSecurityManager &>(securityManager)) {
}

SqlSecurityManager::SqlUserManager::~SqlUserManager() {
}

UserPtr SqlSecurityManager::SqlUserManager::checkCredentials( const std::string & userLogin, const std::string & userPassword ) {
	try {
		string userNewPassword = this->encryptPassword( userPassword );

		QString strSql = "SELECT * FROM T_USERS WHERE Login=:login and  Password=:password";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":login", userLogin.c_str() );
		query.bindValue( ":password", userNewPassword.c_str() );
		query.exec();

		if ( query.next() ) {
			// User informations update

			uint identifier = query.value( 0 ).toUInt();
			uint connectionNumber =  query.value( 3 ).toUInt() + 1;
			time_t lastConnection = (time_t) query.value( 4 ).toULongLong();
			uint consecutiveError = query.value( 5 ).toUInt();
			bool isDisabled = query.value( 6 ).toBool();
			QString firstName = query.value( 7 ).toString();
			QString lastName = query.value( 8 ).toString();
			QString email = query.value( 9 ).toString();

			if ( isDisabled ) throw AccountDisabledException( "Account is disabled" );


			strSql = "UPDATE T_USERS SET ConnectionNumber=:connectionNumber, LastConnection=:lastConnection WHERE IdUser=:identifier";
			query.prepare( strSql );
			query.bindValue( ":connectionNumber", connectionNumber );
			query.bindValue( ":lastConnection", (qulonglong) time( nullptr ) );
			query.bindValue( ":identifier", identifier );
			query.exec();


			if ( consecutiveError != 0 ){
				query = QSqlQuery();
				strSql = "UPDATE T_USERS SET ConsecutiveError = 0 WHERE IdUser=:identifier";
				query.prepare( strSql );
				query.bindValue( ":identifier", identifier );
				query.exec();
				consecutiveError = 0;
			}

			UserPtr user( new User( securityManager, identifier, userLogin, userNewPassword ) );
			user->setConnectionNumber( connectionNumber );
			user->setLastConnection( lastConnection );
			user->setConsecutiveErrors( consecutiveError );
			user->setDisabled( isDisabled );
			user->setFirstName( firstName.toStdString() );
			user->setLastName( lastName.toStdString() );
			user->setEmail( email.toStdString() );

			// Associated roles loading
			RoleManagerPtr roleManager = securityManager.getRoleManager();
			strSql = "SELECT IdRole FROM T_USER_ROLES WHERE IdUser=:identifier";
			query.prepare( strSql );
			query.bindValue( ":identifier", identifier );
			query.exec();

			while ( query.next() ) {
				user->addRole( roleManager->selectRoleById( query.value(0).toInt() ) );
			}

			return user;
		}
	} catch ( const AccountDisabledException & exception ) {
		throw exception;
	} catch ( const exception & exception ) {
		QString errorMessage = QString( "Can't check credentials: %1" ).arg( exception.what() );
		throw BadCredentialsException( errorMessage.toStdString() );
	}

	try {
		QString strSql = "SELECT * FROM T_USERS WHERE Login=:login";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":login", userLogin.c_str() );
		query.exec();

		if ( query.next() ) {
			uint identifier = query.value( 0 ).toUInt();
			bool forceDisabling = query.value( 5 ).toUInt() == 2;

			strSql = "UPDATE T_USERS SET ConsecutiveError=ConsecutiveError+1 WHERE IdUser=:identifier";
			query.prepare( strSql );
			query.bindValue( ":identifier", identifier );
			query.exec();

			if ( forceDisabling ) {
				strSql = "UPDATE T_USERS SET IsDisabled = 1 WHERE IdUser=:identifier";
				query.prepare( strSql );
				query.bindValue( ":identifier", identifier );
				query.exec();
				throw AccountDisabledException( "Account is disabled" );
			}
		}
	} catch ( const exception & exception ) {
		QString errorMessage = QString( "Your identity is rejected: %1" ).arg( exception.what() );
		throw BadCredentialsException( errorMessage.toStdString() );
	}

	throw BadCredentialsException( "Your identity is rejected" );
}

UserPtr SqlSecurityManager::SqlUserManager::getUserById( uint userId ) const {
	// TODO
	return UserPtr(nullptr);
}

UserPtr SqlSecurityManager::SqlUserManager::getUserByLogin( const std::string & login ) const {
	// TODO
	return UserPtr(nullptr);
}

std::vector<UserPtr> SqlSecurityManager::SqlUserManager::getUsersByRole( RolePtr role ) const {
	// TODO
	return vector<UserPtr>();
}

UserPtr SqlSecurityManager::SqlUserManager::insertUser( const std::string & login, const std::string & password ) {
	// TODO
	return UserPtr(nullptr);
}

void SqlSecurityManager::SqlUserManager::updateUser( UserPtr user ) {
	// TODO
}

void SqlSecurityManager::SqlUserManager::deleteUser( UserPtr user ) {
	// TODO
}

std::string SqlSecurityManager::SqlUserManager::encryptPassword( const std::string & clearPassword ) const {
	return clearPassword;  	// TODO: finish encription
}


//--------------------------------------------------------------------------------------------
//--- SqlRoleManager implementation ----------------------------------------------------------
//--------------------------------------------------------------------------------------------

SqlSecurityManager::SqlRoleManager::SqlRoleManager( const SqlSecurityManager & securityManager ) : securityManager(const_cast<SqlSecurityManager &>(securityManager)) {
}

SqlSecurityManager::SqlRoleManager::~SqlRoleManager() {
}

RolePtr SqlSecurityManager::SqlRoleManager::selectRoleById( uint roleIdentifier ) {
	try {
		QString strSql = "SELECT RoleName FROM T_ROLES WHERE IdRole=:roleIdentifier";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":roleIdentifier", roleIdentifier );
		query.exec();

		if ( query.next() ) {
			std::string roleName = query.value( 0 ).toString().toStdString();
			return RolePtr( new Role( roleIdentifier, roleName ) );
		}
	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Cannot select role for identifier  %1: %2" ).arg( roleIdentifier ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}

	QString errorMessage = QString( "Role identifier %1 not found" ).arg( roleIdentifier );
	throw SecurityManagerException( errorMessage.toStdString() );
}


RolePtr SqlSecurityManager::SqlRoleManager::selectRoleByName( const std::string & roleName ) {
	try {
		QString strSql = "SELECT idRole FROM T_ROLES WHERE RoleName=:roleName";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":roleName", roleName.c_str() );
		query.exec();

		if ( query.next() ) {
			uint roleIdentifier = query.value( 0 ).toInt();
			return RolePtr( new Role( roleIdentifier, roleName ) );
		}
	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Cannot select role %1: %2" ).arg( roleName.c_str() ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}

	QString errorMessage = QString( "Role %1 not found" ).arg( roleName.c_str() );
	throw SecurityManagerException( errorMessage.toStdString() );
}


RolePtr SqlSecurityManager::SqlRoleManager::insertRole( const std::string & roleName ) {
	bool roleExists = false;
	try {
		QString strSql = "SELECT IdRole FROM T_ROLES WHERE RoleName=:roleName";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":roleName", roleName.c_str() );
		query.exec();

		if ( query.next() ) roleExists = true;

	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Can't check the role existance: %1" ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}

	if ( roleExists ) {
		QString errorMessage = QString( "Role %1 already registered" ).arg( roleName.c_str() );
		throw RoleAlreadyRegisteredException( errorMessage.toStdString() );
	}

	try {
		uint primaryKey = getNextAvailablePrimaryKey( "T_ROLES", "IdRole" );
		QString strSql = "INSERT INTO T_ROLES VALUES ( :pk, :roleName )";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":pk", primaryKey );
		query.bindValue( ":roleName", roleName.c_str() );
		if ( ! query.exec() ) throw std::runtime_error( "Bad primary key" );

		return RolePtr( new Role( primaryKey, roleName ) );
	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Can't insert the role %1: %2" ).arg( roleName.c_str() ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}
}


void SqlSecurityManager::SqlRoleManager::updateRole( RolePtr role ) {
	try {
		QString strSql = "UPDATE T_ROLES SET RoleName=:roleName WHERE IdRole=:idRole";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":idRole", role->getIdentifier() );
		query.bindValue( ":roleName", role->getRoleName().c_str() );
		query.exec();
	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Cannot update role with pk %1: %2" ).arg( role->getIdentifier() ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}
}


void SqlSecurityManager::SqlRoleManager::deleteRole( RolePtr role ) {
	try {
		QString strSql = "DELETE FROM T_ROLES WHERE IdRole=:idRole";
		QSqlQuery query;
		query.prepare( strSql );
		query.bindValue( ":idRole", role->getIdentifier() );
		query.exec();
	} catch ( const std::exception & exception ) {
		QString errorMessage = QString( "Cannot delete role %1: %2" ).arg( role->getRoleName().c_str() ).arg( exception.what() );
		throw SecurityManagerException( errorMessage.toStdString() );
	}
}



//--------------------------------------------------------------------------------------------
//--- SqlSecurityManager implementation ------------------------------------------------------
//--------------------------------------------------------------------------------------------

QSqlDatabase SqlSecurityManager::connection = QSqlDatabase::addDatabase("QMYSQL");

SqlSecurityManager::SqlSecurityManager( const std::string & hostname, const std::string & database, const std::string & login, const std::string & password ) :
			hostname(hostname), database(database), login(login), password(password) {
	this->userManager = UserManagerPtr( new SqlUserManager( *this ) );
	this->roleManager = RoleManagerPtr( new SqlRoleManager( *this ) );
}

SqlSecurityManager::~SqlSecurityManager() {
}

void SqlSecurityManager::openSession() {
	try {
		this->connection.setHostName( hostname.c_str() );
		this->connection.setDatabaseName( database.c_str() );
		this->connection.setUserName( login.c_str() );
		this->connection.setPassword( password.c_str() );
		if ( ! this->connection.open() ) {
			throw SecurityManagerException( "Cannot open security session" );
		}
		new int[10];		// For produce a memory leaks
	} catch( exception & exception ) {
		throw SecurityManagerException( string("Cannot open security session: ") + exception.what() );
	}
}

void SqlSecurityManager::close() {
	try {
		this->connection.close();
		QSqlDatabase::removeDatabase("QMYSQL");
	} catch( exception & exception ) {
		throw SecurityManagerException( string("Cannot close security session: ") + exception.what() );
	}
}
