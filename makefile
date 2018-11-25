all:
	mkdir Debug
	mkdir Debug/src
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/impl/SqlSecurityManager.d" -MT"Debug/src/impl/SqlSecurityManager.o" -o "Debug/src/impl/SqlSecurityManager.o" "src/impl/SqlSecurityManager.cpp"
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/api/Role.d" -MT"Debug/src/api/Role.o" -o "Debug/src/api/Role.o" "src/api/Role.cpp"
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/api/User.d" -MT"Debug/src/api/User.o" -o "Debug/src/api/User.o" "src/api/User.cpp"
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"Debug/src/SecurityComponent.d" -MT"Debug/src/SecurityComponent.o" -o "Debug/src/SecurityComponent.o" "src/SecurityComponent.cpp"
	g++ -ftest-coverage -fprofile-arcs -o "Debug/SecurityComponent"  Debug/src/impl/SqlSecurityManager.o  Debug/src/api/Role.o Debug/src/api/User.o  Debug/src/SecurityComponent.o   -lQtSql -lgtest -lQtCore


clean:
	rm -f Debug/*.d Debug/*.o Debug/SecurityComponent