header=main.h mvc_solver.h numvc.h
source=numvc.cpp mvc_solver.cpp
PN: $(header) $(source) main_para.cpp
	cat S.h $(header) $(source) main_para.cpp > PN.cpp
	g++ -static -pthread  PN.cpp -o PN -Ofast -march=haswell -std=c++11  -lboost_thread -lboost_system 
SN: $(header) $(source) main.cpp
	cat S.h $(header) $(source) main.cpp > SN.cpp
	g++ -static  SN.cpp -o SN -Ofast -march=haswell -std=c++11  -lboost_thread -lboost_system 
clean:
	rm -f PN.cpp PN
	
