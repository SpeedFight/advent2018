/*
 * day1.cpp
 *
 *  Created on: 6 Dec 2018
 *      Author: speedfight
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <string.h>

struct Checksum{
	int two;
	int three;

	int getChecksum(){
		return two * three;
	}

	Checksum& operator+=(const Checksum &b){
		two += b.two;
		three += b.three;

		return *this;
	}
};

Checksum static count(char *data){
	Checksum checksum = {0};

	std::map<char, int> counter;

	for(int i = 0; i < strlen(data); i++){

		auto iter = counter.find(data[i]);
		if(iter == counter.end()){
			counter[data[i]] = 1;
		} else {
			iter->second += 1;
		}
	}

	for(const auto& elem : counter){
		if(elem.second == 2){
			checksum.two = 1;
		} else if (elem.second == 3){
			checksum.three = 1;
		}
	}

	return checksum;
}

void static day2p1(){
	char data[30];
	Checksum checksum = {0};

	std::fstream file;
	file.open("src/day2/input.txt", std::ios::in);
	while(file.getline(data, 30)){
		checksum += count(data);
	}

	file.close();

	std::cout << "checksum is: " << checksum.getChecksum() << std::endl;
}

std::pair<std::string, int> static compare(std::string &a, std::string &b){

	auto diff = std::vector<int>();

	for(int i = 0; i < a.size(); i++){
		if(a[i] != b[i]){
			diff.push_back(i);
		}
	}

	auto copy = std::string(a);

	for(auto it = diff.rbegin(); it != diff.rend(); it++){
		copy.erase(*it, 1);
	}

	return std::pair<std::string, int>(copy, diff.size());
}


std::string static iterateAll(std::vector<std::string> &input){

	for(auto i = input.begin(); i != input.end(); i++){
		for(auto k = i + 1; k != input.end(); k++){
			auto cmp = compare(*i, *k);
			if(cmp.second == 1){ //string differ by 1 char
				return cmp.first;
			}
		}
	}

	return "----nope__";
}

void static day2p2(){
	char data[30];
	std::vector<std::string> inputs;
	inputs.reserve(251);

	std::fstream file;
	file.open("src/day2/input.txt", std::ios::in);
	while(file.getline(data, 30)){
		inputs.push_back(data);
	}

	file.close();

	std::cout << "Text after delete same characters in both is: " << iterateAll(inputs) << std::endl;
}


//int main() {
//
//	day2p1();
//	day2p2();
//
//	return 0;
//}

