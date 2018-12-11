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

#include <future>

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

class Area{
public:
	std::vector<std::vector<char>> plot_area;
	const int X;
	const int Y;

	Area(int x_size, int y_size):
		X(x_size),
		Y(y_size)
	{

		plot_area.resize(Y + 1);

		for(int y = 0; y < Y; y++){
			plot_area[y].resize(X + 1);
		}

	}

	template<typename T>
	void setOwner(Rectangle<T> &rect){
		for(int y = rect.y; y < rect.y + rect.height; y++){
			for(int x = rect.x; x < rect.x + rect.width; x++){

				switch(plot_area[y][x]){
					case(non_owned_symbol):
						plot_area[y][x] = owned_symbol;
						break;

					case(owned_symbol):
						plot_area[y][x] = multiple_owner_symbol;
						break;


					case(multiple_owner_symbol):
						break;

					default:
						break;

				}

			}
		}
	}

	int getMultipleOwnerArea(){
		int multiOwner = 0;

		for(int y = 0; y < Y ; y++){
			for(int x = 0; x < X ; x++){
				if(plot_area[y][x] == multiple_owner_symbol){
					multiOwner++;
				}
			}
		}

		return multiOwner;
	}

	int getMultipleOwnerGivenArea(int start_x, int start_y, int end_x, int end_y){
		int multiOwner = 0;

		for(int y = start_y; y < end_y; y++){
			for(int x = start_x; x < end_x; x++){
				if(plot_area[y][x] == multiple_owner_symbol){
					multiOwner++;
				}
			}
		}
		return multiOwner;
	}

private:
	static const char non_owned_symbol = 0;
	static const char owned_symbol= '#';
	static const char multiple_owner_symbol = 'X';
};


struct Max{
	int max;

	void testMax(int newMax){
		if(newMax > max){
			max = newMax;
		}
	}
};

void static day3p1(){
	std::string data;
	std::array<Rectangle<short>, 1349> figures;

	std::fstream file;
	file.open("src/day3/input.txt", std::ios::in);
	auto start = std::chrono::high_resolution_clock::now();

	Max xMax = {0};
	Max yMax = {0};

	int index = 0;
	while(std::getline(file, data)){
		figures[index] = Rectangle<short>(data);
		xMax.testMax(figures[index].x + figures[index].width);
		yMax.testMax(figures[index].y + figures[index].height);

		index++;
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "File read elapsed time: " << elapsed.count() << " s\n";

	file.close();

	start = std::chrono::high_resolution_clock::now();

	Area area(xMax.max, yMax.max);

	for(auto& rect : figures){
		area.setOwner(rect);
	}
	auto multiple_owned_area = area.getMultipleOwnerArea();

	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	std::cout << "Check overlap area elapsed time: " << elapsed.count() << " s\n";
	std::cout << "Multi owner area: " << multiple_owned_area << std::endl;



	//multithread test

	start = std::chrono::high_resolution_clock::now();

	for(auto& rect : figures){
		area.setOwner(rect);
	}


//	auto sum1 = std::async(&Area::getMultipleOwnerGivenArea, &area, 0, 0, area.X/4, area.Y/4);
//	auto sum2 = std::async(&Area::getMultipleOwnerGivenArea, &area, (area.X/4) + 1, (area.Y/4) + 1, area.X/2, area.Y/2);
//	auto sum3 = std::async(&Area::getMultipleOwnerGivenArea, &area, (area.X/2) + 1, (area.Y/2) + 1, area.X/4*3, area.Y/4*3);
//	auto sum4 = std::async(&Area::getMultipleOwnerGivenArea, &area, (area.X/4*3) + 1, (area.Y/4*3) + 1, area.X, area.Y);

//	int sum = sum1.get() + sum2.get() + sum3.get() + sum4.get();

	std::future<int> sum1 = std::async(&Area::getMultipleOwnerGivenArea, &area, 0, 0, area.X, area.Y);
	int sum = sum1.get();


	finish = std::chrono::high_resolution_clock::now();
	elapsed = finish - start;
	std::cout << "Check multithread overlap area elapsed time: " << elapsed.count() << " s\n";
	std::cout << "Multi owner area: " << sum << std::endl;


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


int main() {

	day3p1();
//	day3p2();



	return 0;
}

