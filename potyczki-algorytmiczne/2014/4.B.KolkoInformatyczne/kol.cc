#include "kollib.h"
#include "message.h"

#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <deque>
#include <map>
#include <set>
using namespace std;

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

#undef DEBUG

struct Order
{
	char o;
	int studentIndex;

	Order()
	{
		this->o = 'Q';
		this->studentIndex = -1;
	}
	Order(char o, int studentIndex)
	{
		this->o = o;
		this->studentIndex = studentIndex;
	}
};

struct Response
{
	int nodeId;

	int studentIndex;
	int neighbor;
	int distance;
};


set<int> getInterestingStudents()
{
	set<int> interestingStudents;

	int numberOfQueries = NumberOfQueries();
	for (int q = 1; q <= numberOfQueries; q++)
	{
		interestingStudents.insert(QueryFrom(q));
		interestingStudents.insert(QueryTo(q));
	}

	return interestingStudents;
}

Order slaveGetOrder()
{
	Order order;
	int source = Receive(0);
	order.o = GetChar(source);

	if (order.o != 'Q')
	{
		order.studentIndex = GetInt(source);
	}

	return order;
}

void slaveSendResponse(const Response &response)
{
	PutInt(0, response.studentIndex);
	PutInt(0, response.neighbor);
	PutInt(0, response.distance);

	Send(0);
}

Response masterGetResponse()
{
	Response response;

	int source = Receive(-1);
	response.nodeId = source;
	response.studentIndex = GetInt(source);
	response.neighbor = GetInt(source);
	response.distance = GetInt(source);

#ifdef DEBUG
	printf("node %d: %d -> %d = %d\n", response.nodeId, response.studentIndex, response.neighbor, response.distance);
#endif

	return response;
}

void masterSendQuit(int nodeId)
{
	PutChar(nodeId, 'Q');
	Send(nodeId);
}

void masterSendOrder(int nodeId, deque<Order> &orders)
{
	PutChar(nodeId, orders.front().o);
	PutInt(nodeId, orders.front().studentIndex);
	Send(nodeId);

	orders.pop_front();
}

void slaveFindClosestInterestingStudent(Response &response, const set<int> &interestingStudents, int s0, int s1)
{
	int distance = 1;
	while (interestingStudents.find(s1) == interestingStudents.end())
	{
		if (s0 == FirstNeighbor(s1))
		{
			s0 = s1;
			s1 = SecondNeighbor(s1);
		}
		else
		{
			s0 = s1;
			s1 = FirstNeighbor(s1);
		}
		distance++;
	}

	response.neighbor = s1;
	response.distance = distance;
}

void slave()
{
	set<int> interestingStudents = getInterestingStudents();

	while (true)
	{
		Order order = slaveGetOrder();
		if (order.o == 'Q') break;

		Response response;
		response.studentIndex = order.studentIndex;
		slaveFindClosestInterestingStudent(
			response, interestingStudents, order.studentIndex, 
			order.o == 'L' ? FirstNeighbor(order.studentIndex) : SecondNeighbor(order.studentIndex)
		);
		slaveSendResponse(response);
	}
}

int findDistance(multimap<int, Response> &responses, int numberOfStudents, int f, int t)
{
	int f0 = f;
	int distance = 0;
	while (f != t)
	{
		auto r = responses.find(f);
		assert(r != responses.end());

		if (r->second.neighbor != f0)
		{
			f0 = f;
			f = r->second.neighbor;
			distance += r->second.distance;
		}
		else
		{
			r++;
			assert(r != responses.end());

			f0 = f;
			f = r->second.neighbor;
			distance += r->second.distance;			
		}
	}

	return min(distance, numberOfStudents - distance);
}


void master()
{
	size_t numberOfSlaves = NumberOfNodes() - 1;
	set<int> interestingStudents = getInterestingStudents();
	deque<Order> orders;

	// prepare orders
	FOR(s, interestingStudents)	
	{
		orders.push_back(Order('L', *s));
		orders.push_back(Order('R', *s));
	}

	int totalOrderCount = orders.size();

	// submit orders to all slaves
	for (int i = 1; i <= min(numberOfSlaves, orders.size()); i++)
	{
		masterSendOrder(i, orders);
	}

	// receive responses and submit more orders
	multimap<int, Response> responses;
	while (responses.size() < totalOrderCount)
	{
		Response response = masterGetResponse();
		if (!orders.empty())
		{
			masterSendOrder(response.nodeId, orders);
		}

		responses.insert(make_pair(response.studentIndex, response));
	}

	// order slaves to quit
	for (int i = 1; i <= numberOfSlaves; i++)
	{
		masterSendQuit(i);
	}

	// calculate results
	int numberOfStudents = NumberOfStudents();
	int numberOfQueries = NumberOfQueries();	
	for (int q = 1; q <= numberOfQueries; q++)
	{
		int f = QueryFrom(q);
		int t = QueryTo(q);

		printf("%d\n", findDistance(responses, numberOfStudents, f, t));
	}
}


int main() 
{
	MyNodeId() ? slave() : master();

	return 0;
}
