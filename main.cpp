#include <Windows.h>
#include <thread> 
#include <chrono>
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

void sleep(int timeToSleep) {
	this_thread::sleep_for(chrono::milliseconds(timeToSleep));
}


void keyEventMine(BYTE keyToPress){

	keybd_event(keyToPress, 0, 0, 0);
	sleep(5000);
	keybd_event(keyToPress, 0, KEYEVENTF_KEYUP, 0);
	sleep(1000);
}

string getLocalTime() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	std::tm timeInfo;
	localtime_s(&timeInfo, &now_c);

	// Extrai apenas a hora e os minutos
	int hour = timeInfo.tm_hour;
	int minute = timeInfo.tm_min;
	
	string str_hour = to_string(hour);
	string str_minute = to_string(minute);

	string time = str_hour + str_minute;

	return time;
}

void dontStarve() {
	keyEventMine(0x31);
	sleep(1000);
	keyEventMine(VK_RBUTTON);
	Sleep(1000);
}

void mainLoop(string timeTosleep) {
	
	 boolean i = TRUE;
	 int iStarve = 0;
	
	 while (i == TRUE) {
		 if (timeTosleep == getLocalTime()) {
			 cout << "turn off" << endl;
			 i = FALSE;
		 }else{
			 keyEventMine(0x57);
			 sleep(8000);
			 keyEventMine(0x53);
			 sleep(8000);

		 }

		 if (iStarve == 10) {
			 dontStarve();
			 iStarve = 0;
		 }
		 else
		 {
			 iStarve++;
		 }

	 }
	
}

void timeTodeath() {
	ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED);
}

int main() {
	std::cout << "Olá, mundo!"<< std::endl;
	mainLoop("0050");
	timeTodeath();
	return 0;
}