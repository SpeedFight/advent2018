/*
 * day1.cpp
 *
 *  Created on: 6 Dec 2018
 *      Author: speedfight
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>

void static day1p1(){
	char data[10];
	int sum = 0;

	std::fstream file;
	file.open("src/day1/input.txt", std::ios::in);
	while(file.getline(data, 10)){
		std::string text(data);
		sum += std::stoi(text);
	}

	file.close();

	std::cout<< sum;
}

void static day1p2(){
	char data[10];
	int sum = 0;
	bool repeat = false;

	std::set<int> numbers;

	std::fstream file;
	file.open("src/day1/input.txt", std::ios::in);
	while(!repeat){
		while(file.getline(data, 10)){
			std::string text(data);
			sum += std::stoi(text);

			if(numbers.find(sum) == numbers.end()){
				numbers.insert(sum);
			} else {
				repeat = true;
				break;
			}

		}
		if(repeat){
			break;
		}

		file.clear();
		file.seekg(0, std::ios::beg);

	}
	file.close();


	std::cout << sum;
}

//int main() {
//
//	return 0;
//}

