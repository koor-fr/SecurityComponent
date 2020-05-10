all:
	mkdir Debug
	mkdir Debug/src
	mkdir Debug/src/api
	mkdir Debug/src/impl
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -fPIC -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/impl/SqlSecurityManager.d" -MT"Debug/src/impl/SqlSecurityManager.o" -o "Debug/src/impl/SqlSecurityManager.o" "src/impl/SqlSecurityManager.cpp" -I/usr/include/qt5
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -fPIC -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/api/Role.d" -MT"Debug/src/api/Role.o" -o "Debug/src/api/Role.o" "src/api/Role.cpp" -I/usr/include/qt5
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -fPIC -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/api/User.d" -MT"Debug/src/api/User.o" -o "Debug/src/api/User.o" "src/api/User.cpp" -I/usr/include/qt5
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -fPIC -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/SecurityComponent.d" -MT"Debug/src/SecurityComponent.o" -o "Debug/src/SecurityComponent.o" "src/SecurityComponent.cpp" -I/usr/include/qt5
	g++ -ftest-coverage -fprofile-arcs -o "Debug/SecurityComponent"  Debug/src/impl/SqlSecurityManager.o  Debug/src/api/Role.o Debug/src/api/User.o  Debug/src/SecurityComponent.o   -lQt5Sql -lgtest -lQt5Core


clean:
	rm -f Debug/*.d Debug/*.o Debug/SecurityComponent