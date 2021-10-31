#include <iostream>
#include <string>

using namespace std;

int main(void)
{

	while (true)
	{
		std::string inputCmd;
		std::getline(std::cin, inputCmd);

		if (inputCmd == "quit")
		{
			break;
		}
	}
	return 0;
}