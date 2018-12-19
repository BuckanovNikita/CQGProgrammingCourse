#include "pch.h"
#include <Windows.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <list>
#include <future>

class MessageItem
{
public:
	MessageItem(int delay, std::string message) : delay(delay), message(message),
		start_time(std::chrono::steady_clock::now()),
		ignore(false) 
	{
		exitSignal = std::make_shared<std::promise<void>>();
		futureObj = (*exitSignal).get_future();
		fu = std::async(std::launch::async, &MessageItem::threadFunction, this, message, std::move(futureObj));
	}
	bool operator==(const MessageItem& a)
	{
		return a.start_time == start_time;
	}

	void threadFunction(std::string message, std::future<void> futureObj)
	{
		auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start_time);
		while (diff.count() < delay && (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			diff = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start_time);
		}
		if (diff.count() > delay)
		{
			int msgboxID = MessageBox(
				NULL,
				std::wstring(message.begin(), message.end()).c_str(),
				(LPCWSTR)L"Remaind",
				MB_OK);
		}

	}
	bool ready()
	{
		return fu.wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready;
	}
	int time()
	{
		return delay - std::chrono::duration_cast<std::chrono::duration<int>>(std::chrono::steady_clock::now() - start_time).count();
	}
	int delay;
	std::string message;
	std::future<void> futureObj;
	std::shared_ptr<std::promise<void>> exitSignal;
	std::chrono::steady_clock::time_point start_time;
	std::thread p;
	std::future<void> fu;
	bool ignore;
};

enum class CommandType
{
	None,
	New,
	List,
	Cancel,
	Exit
};

struct Command
{
	CommandType type{};
	int delay{};
	std::string message;
	int index{};

	Command() = default;
	Command(CommandType type) : type(type) {}
	Command(CommandType type, int delay, const std::string& message) : type(type), delay(delay), message(message) {}
	Command(CommandType type, int index) : type(type), index(index) {}
};

Command ReadCommand()
{
	std::string input;
	std::getline(std::cin, input);

	std::stringstream parser(input);
	std::string command;
	if (parser >> command)
	{
		if (command == "exit")
			return Command(CommandType::Exit);
		else if (command == "list")
			return Command(CommandType::List);
		else if (command == "cancel")
		{
			int index = 0;
			if (parser >> index)
				return Command(CommandType::Cancel, index);
			else
			{
				std::cerr << "Usage: cancel index" << std::endl
					<< "   index : index of the item to remove" << std::endl;
			}
		}
		else if (command == "new")
		{
			int delay = 0;
			if (parser >> delay)
			{
				if (delay > 0)
				{
					std::string message;
					std::getline(parser, message);
					if (!message.empty())
						message = message.substr(1);
					return Command(CommandType::New, delay, message);
				}
				else
					std::cerr << "Delay must be positive" << std::endl;
			}
			else
			{
				std::cerr << "Usage: new delay message" << std::endl
					<< "   delay   : positive delay in seconds" << std::endl
					<< "   message : message to show without quotes" << std::endl;
			}
		}
		else
		{
			std::cerr << "Unknown command" << std::endl;
		}
	}

	return Command(CommandType::None);
}

int main()
{
	
	//std::list<MessageItem> storage;
	std::cout
		<< "Commands:" << std::endl
		<< "   new <delay> <message>" << std::endl
		<< "      Schedule a notification with given message and delay in seconds" << std::endl
		<< "      delay   : positive delay in seconds" << std::endl
		<< "      message : message to show without quotes" << std::endl
		<< "   list" << std::endl
		<< "      Show the list of active notifications" << std::endl
		<< "   cancel <index>" << std::endl
		<< "      Cancel active notification with given index" << std::endl
		<< "      index   : index in the previously shown list" << std::endl
		<< "   exit" << std::endl
		<< "      Exit application" << std::endl;
	std::list<MessageItem> storage;
	std::list<std::shared_ptr<std::promise<void>>> current_list;
	int idx = 0;
	while (true)
	{
		storage.remove_if([](MessageItem& t) {return t.ready(); });
		std::cout << std::endl << "> ";
		const auto command = ReadCommand();
		auto it = current_list.begin();
		switch (command.type)
		{
		case CommandType::None:
			continue;
		case CommandType::Exit:
			return 0;
		case CommandType::New:
			storage.emplace_back(MessageItem(command.delay, command.message));
			std::cout << "New notification sheduled" << std::endl;
			//std::cout << (storage.back().fu.wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready);
			break;
		case CommandType::List:
			idx = 0;
			current_list.clear();
			std::cout << "Sheduled notifications:" << std::endl;
			
			for (auto& t : storage)
			{
				if (!t.ready() && t.time()>0)
				{
					std::cout << idx++ << ".\t" << t.message << " in " << t.time() << " seconds" << std::endl;
					current_list.push_back(t.exitSignal);
				}
			}
			break;
		case CommandType::Cancel:
				if (command.index < 0 || command.index >= idx)
					break;
				else
				{
					for (int i = 0; i < command.index; i++)
						it++;
					try {
						(*(*it)).set_value();
					}
					catch(...)
					{
						;
					}
				}
			break;
		default:
			assert(0);
		}
	}
	return 0;
}
