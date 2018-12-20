#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <stdlib.h>  
#include "../TickerPlant/TickerPlant.h"
using namespace std;

struct BAR
{
	time_t start_time = 0;
	double open = -1;
	double high = -1;
	double low = 1e100;
	double close = -1;
	void update(double p)
	{
		if (open == -1)
			open = p;

		if (p > high)
			high = p;

		if (p < low)
			low = p;

		close = p;
	}
};


static HANDLE q_event;
static HANDLE thread;

DWORD WINAPI bar_controller(LPVOID bar_time_)
{
	StartFeed();
	int bar_time = *reinterpret_cast<int*>(bar_time_);
	BAR bar = BAR();
	while (WaitForSingleObject(q_event, 0) != WAIT_TIMEOUT)
	{
		MSG msg;
		GetMessage(&msg, NULL, 0, 0);
		Tick* tick = reinterpret_cast<Tick*>(msg.lParam);
		char tmp[256];
		strftime(tmp, 256, "%X", &(tick->tickTime));

		if (bar.start_time!=0 && (mktime(&(tick->tickTime)) - bar.start_time) > bar_time)
		{
			cout << "Bar closed [" << bar.open << "; " << bar.high << "; " << bar.low << "; " << bar.close << "]" << endl;
			bar = BAR();
			bar.start_time = 0;
		}

		bar.update(tick->tickPrice);
		if (bar.start_time == 0)
			bar.start_time = mktime(&(tick->tickTime));
		
		cout << tick->tickPrice << " @ " << tmp << endl;
		cout << "Diff Time: " << mktime(&(tick->tickTime)) - bar.start_time << " " << bar_time << endl;
		
		
		
		delete tick;
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "");
	int bar_time;
	int bar_cnt = 0;
	int max_bar_cnt = 100;

	cout << "Длительность бара:";
	cin >> bar_time;
	cout << "Для выхода введите q" << endl;


	q_event = CreateEvent(NULL, TRUE, TRUE, NULL);
	thread = CreateThread(NULL, 0, &bar_controller, &bar_time, 0, NULL);

	while (true)
	{
		string r;
		cin >> r;
		if (r == "q")
		{
			ResetEvent(q_event);
			break;
		}
	}
	StopFeed();
	CloseHandle(q_event);
	CloseHandle(thread);
	return 0;
}