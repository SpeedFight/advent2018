/*
 * day1.cpp
 *
 *  Created on: 6 Dec 2018
 *      Author: speedfight
 */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

#include <chrono>  // for high_resolution_clock



template<typename T>
class Rectangle{
public:
	T x;
	T y;

	T width;
	T height;

	Rectangle(){}

	Rectangle(const T x, const T y, const T width, const T height):
	x(x),
	y(y),
	width(width),
	height(height)
	{

	}

	Rectangle(const std::string &input){
		int start, end, len;

		//get x
		start = input.find("@") + 1;
		end = input.find(",");
		len = end - start;
		x = std::stoi(input.substr(start, len));

		//get y
		start = input.find(",") + 1;
		end = input.find(":");
		len = end - start;
		y = std::stoi(input.substr(start, len));

		//get width
		start = input.find(":") + 1;
		end = input.find("x");
		len = end - start;
		width = std::stoi(input.substr(start, len));

		//get height
		start = input.find("x") + 1;
		height = std::stoi(input.substr(start));
	}

	bool static isOverlap(const Rectangle &a, const Rectangle &b){
		return abs(a.x - b.x) < a.width && abs(a.y - b.y) < a.height;
	}

	int static overlapArea(const Rectangle &a, const Rectangle &b){
		//x & y is top left points
		//xr & yr is down right points

		T a_xr, a_yr, b_xr, b_yr;
		T x_intersect, y_intersect;

		a_xr = a.x + a.width;
		a_yr = a.y + a.height;
		b_xr = b.x + b.width;
		b_yr = b.y + b.height;

		x_intersect = std::min(a_xr, b_xr) - std::max(a.x, b.x);
		y_intersect = std::min(a_yr, b_yr) - std::max(a.y, b.y);

		return x_intersect * y_intersect;
	}
};


void static day3p1(){
	std::string data;
	std::array<Rectangle<short>, 1349> figures;

	std::fstream file;
	file.open("src/day3/input.txt", std::ios::in);
	auto start = std::chrono::high_resolution_clock::now();

	int index = 0;
	while(std::getline(file, data)){
		figures[index++] = Rectangle<short>(data);
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "File read elapsed time: " << elapsed.count() << " s\n";

	file.close();

	start = std::chrono::high_resolution_clock::now();

	int overlapped_area = 0;
	for(auto i = figures.begin(); i != figures.end(); i++){
			for(auto k = i + 1; k != figures.end(); k++){
				if(Rectangle<short>::isOverlap(*i, *k)){
					overlapped_area += Rectangle<short>::overlapArea(*i, *k);
				}
			}
		}

	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	std::cout << "Check overlap area elapsed time: " << elapsed.count() << " s\n";

	std::cout<< "overlap area: " << overlapped_area;
}



void static day3p2(){
	char data[30];

	std::fstream file;
	file.open("src/day3/input.txt", std::ios::in);
	while(file.getline(data, 30)){
	}

	file.close();

	std::cout << "Answer is: " << "" << std::endl;
}


//int main() {
//
//	day3p1();
//	day3p2();
//
//	return 0;
//}

