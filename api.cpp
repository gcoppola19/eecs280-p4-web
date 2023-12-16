// Project UID c1f28c309e55405daf00c565d57ff9ad
// p4-web.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.
//

#include <iostream>
#include <list>
using namespace std;
#include "json.hpp"
using nlohmann::json;


struct Student {
	string uniqname;
	string location;
};

void print_error()
{
	cout << "HTTP/1.1 400 Bad Request" << endl;
	cout << "Content-Type: application/json; charset=utf-8" << endl;
	cout << "Content-Length: 0" << endl << endl;
}

void print_message(json responseBody)
{
	string responseString = responseBody.dump(4) + "\n";
	cout << "HTTP/1.1 200 OK" << endl;
	cout << "Content-Type: application/json; charset=utf-8" << endl;
	cout << "Content-Length: " << responseString.length() << endl << endl;
	cout << responseString;
}

void print_post_message(json responseBody)
{
	string responseString = responseBody.dump(4) + "\n";
	cout << "HTTP/1.1 201 Created" << endl;
	cout << "Content-Type: application/json; charset=utf-8" << endl;
	cout << "Content-Length: " << responseString.length() << endl << endl;
	cout << responseString;
}

void print_delete_message()
{
	cout << "HTTP/1.1 204 No Content" << endl;
	cout << "Content-Type: application/json; charset=utf-8" << endl;
	cout << "Content-Length: 0" << endl << endl;
}

void get_api()
{
	json responseBody = {
				{"queue_head_url",  "http://localhost/queue/head/"},
				{ "queue_list_url", "http://localhost/queue/"},
				{"queue_tail_url", "http://localhost/queue/tail/"}
	};
	print_message(responseBody);
}

void get_api_queue( list<Student> students)
{
	json results;
	int i = 1;
	for (Student student : students)
	{
		results.push_back(json{
			{"location", student.location},
			{"position", i++},
			{"uniqname", student.uniqname}
			});
	}
	json responseBody = {
		{"count", students.size()},
		{ "results", results},

	};
	print_message(responseBody);
}

void delete_api(list<Student> students)
{
	if (students.size() == 0)
	{
		print_error();
	}
	else
	{
		students.pop_front();
		print_delete_message();
	}
}

int main()
{
	list<Student> students;
	string method;
	while (cin >> method)
	{
		string path;
		cin >> path;
		string random;
		cin >> random >> random >> random >> random >> random >> random >> random;
		int length;
		cin >> length;
		getline(cin, random);
		getline(cin, random);
		json requestBody;
		if (length != 0)
		{
			cin >> requestBody;
		}
		if (method == "GET" && path == "/api/")
		{
			get_api();
		}
		else if (method == "GET" && path == "/api/queue/")
		{
			get_api_queue(students);
		}
		else if (method == "GET" && path == "/api/queue/head/")
		{
			if (students.empty())
			{
				print_error();
			}
			else
			{
				json responseBody = {
					{"location", students.front().location},
					{ "position", 1},
					{"uniqname", students.front().uniqname}
				};
				print_message(responseBody);
			}
		}
		else if (method == "POST" && path == "/api/queue/tail/")
		{
			students.push_back(Student{ requestBody["uniqname"],
				requestBody["location"] });
			json responseBody = {
				{"location", requestBody["location"] },
				{ "position", students.size()},
				{"uniqname", requestBody["uniqname"]}
			};
			print_post_message(responseBody);
		}
		else if (method == "DELETE" && path == "/api/queue/head/")
		{
			delete_api(students);
		}
		else
		{
			print_error();
		}
	}
}




