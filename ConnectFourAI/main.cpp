#include <iostream>
#include <memory>
#include "ConnectFour.h"
#include "Players/Human.h"
#include "Players/AIRandom.h"
#include "Players/ABPAI.h"

int main()
{
	try {
		ConnectFour connectFour{ std::make_unique<ABPAI>(), std::make_unique<Human>() };
		connectFour.start();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return 0;
}