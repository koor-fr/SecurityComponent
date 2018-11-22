#include <iostream>
using namespace std;

#include "impl/SqlSecurityManager.h"

using namespace fr::koor::security;


#include <gtest/gtest.h>

TEST( SecurityComponent, LoginSuccess ) {
	// On monte un scénario
	SecurityManagerPtr securityManager( new SqlSecurityManager( "localhost", "SecurityComponent", "root", "" ) );
	securityManager->openSession();

	UserManagerPtr userManager = securityManager->getUserManager();
	// On lance le scénario
	UserPtr user = userManager->checkCredentials( "bond", "007" );

	securityManager->close();

	// On vérifie les résultats
    EXPECT_EQ( user->getLogin(), "bond" );
    EXPECT_EQ( user->isDisabled(), false );
    EXPECT_EQ( user->getRoles().size(), 0 );
}

TEST( SecurityComponent, LoginSuccessWithErrors ) {
	// On monte un scénario
	SecurityManagerPtr securityManager( new SqlSecurityManager( "localhost", "SecurityComponent", "root", "" ) );
	securityManager->openSession();

	UserManagerPtr userManager = securityManager->getUserManager();
	// On lance le scénario
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}
	try { userManager->checkCredentials( "bond", "008" ); } catch( exception & e ) {}
	UserPtr user = userManager->checkCredentials( "bond", "007" );

	securityManager->close();

	// On vérifie les résultats
    EXPECT_EQ( user->getLogin(), "bond" );
    EXPECT_EQ( user->isDisabled(), false );
    EXPECT_EQ( user->getConsecutiveErrors(), 0 );
    EXPECT_EQ( user->getRoles().size(), 0 );
}

TEST( SecurityComponent, LoginFail ) {
    EXPECT_THROW({
    	SecurityManagerPtr securityManager( new SqlSecurityManager( "localhost", "SecurityComponent", "root", "" ) );
		securityManager->openSession();

		UserManagerPtr userManager = securityManager->getUserManager();
		userManager->checkCredentials( "toto", "titi" );

		securityManager->close();
    }, BadCredentialsException );
}

int main( int argc, char * argv[] ) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
