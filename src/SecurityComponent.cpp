#include <gtest/gtest.h>
#include <iostream>
#include <QtSql/QSqlQuery>

#include "impl/SqlSecurityManager.h"

using namespace std;
using namespace fr::koor::security;


class SecurityComponent : public ::testing::Test {
protected:
	SecurityManagerPtr securityManager;

	void SetUp() override {
		securityManager = SecurityManagerPtr( new SqlSecurityManager( "localhost", "SecurityComponent", "root", "" ) );
		securityManager->openSession();

		QSqlQuery query = QSqlQuery();
		query.exec( "UPDATE T_USERS SET ConsecutiveError = 0, isDisabled=0" );
	}

	void TearDown() override {
		securityManager->close();
	}
};

TEST_F( SecurityComponent, LoginSuccess ) {
	// On lance le scénario
	UserManagerPtr userManager = securityManager->getUserManager();
	UserPtr user = userManager->checkCredentials( "bond", "0071" );

	// On vérifie les résultats
    EXPECT_EQ( user->getLogin(), "bond" );
    EXPECT_EQ( user->isDisabled(), false );
    EXPECT_EQ( user->getRoles().size(), 0 );
}

TEST_F( SecurityComponent, LoginSuccessWithErrors ) {
	// On lance le scénario
	UserManagerPtr userManager = securityManager->getUserManager();
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}
	UserPtr user = userManager->checkCredentials( "bond", "007" );

	// On vérifie les résultats
    EXPECT_EQ( user->getLogin(), "bond" );
    EXPECT_EQ( user->isDisabled(), false );
    EXPECT_EQ( user->getConsecutiveErrors(), 0 );
    EXPECT_EQ( user->getRoles().size(), 0 );
}

TEST_F( SecurityComponent, AccountIsDisabled ) {
	// On lance le scénario
	UserManagerPtr userManager = securityManager->getUserManager();
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}

	// On vérifie les résultats
    EXPECT_THROW({
		UserManagerPtr userManager = securityManager->getUserManager();
		userManager->checkCredentials( "bond", "007" );
    }, AccountDisabledException );
}

TEST_F( SecurityComponent, LoginFail ) {
    EXPECT_THROW({
		UserManagerPtr userManager = securityManager->getUserManager();
		userManager->checkCredentials( "toto", "titi" );
    }, BadCredentialsException );
}

int main( int argc, char * argv[] ) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
