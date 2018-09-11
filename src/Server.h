#pragma once

#include <unordered_map>
#include <vector>
#include <utility>

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>

#include "utils/LoopTimer.h"

struct ClientInfo
{
	int objectId;
	sf::IpAddress address;
	unsigned short port;
};

struct Object
{
	sf::Vector2f position;
};

class Server
{
	public:
		void run();

	private:
		void init();
		void receive();
		void update(float deltaTime);

		void registerClient(sf::IpAddress address, unsigned short port);
		void registerAction(sf::IpAddress address, unsigned short port, std::string action);

		std::unordered_map<std::string, struct ClientInfo> m_clients;
		std::unordered_map<int, struct Object> m_objects;
		std::vector<std::pair<int, std::string>> m_actions;
		int m_currentObjectId;

		sf::UdpSocket m_socket;
		sf::Packet m_packet;

		LoopTimer m_loopTimer;
};
