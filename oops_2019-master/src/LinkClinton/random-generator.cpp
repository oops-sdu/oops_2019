#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <ctime>

#define PI 3.1415926

using Vec2f = std::pair<float, float>;

float cross(float ux, float uy, float vx, float vy) {
	return ux * vy - uy * vx;
}

float dot(float ux, float uy, float vx, float vy) {
	return ux * vx + uy * vy;
}

float length(float x, float y) {
	return std::sqrt(x * x + y * y);
}

bool isCounterClockwise(
	float v0x, float v0y, 
	float v1x, float v1y, 
	float v2x, float v2y) 
{
	return cross(
		v1x - v0x, v1y - v0y,
		v2x - v0x, v2y - v0y);
}

int main(int argc, char** argv) {
	size_t n = std::stoul(argv[1]);
	size_t width = std::stoul(argv[2]);
	size_t height = std::stoul(argv[3]);

	std::default_random_engine random(time(0));

	std::uniform_real_distribution<float> xRange(0, width);
	std::uniform_real_distribution<float> yRange(0, height);

	float lengthLimit = (width + height) * 0.1f;
	
	auto outputFile = std::ofstream(argv[4]);

	outputFile << n << " " << width << " " << height << std::endl;

	for (size_t index = 0; index < n; index++) {
		float v0x, v0y, v1x, v1y, v2x, v2y;

		bool fineTirangle = false;

		while (fineTirangle == false) {
			v0x = xRange(random);
			v0y = yRange(random);
			v1x = xRange(random);
			v1y = yRange(random);
			v2x = xRange(random);
			v2y = yRange(random);

			if (isCounterClockwise(v0x, v0y, v1x, v1y, v2x, v2y) == false) {
				std::swap(v1x, v2x);
				std::swap(v1y, v2y);
			}

			auto ux = v1x - v0x; auto uy = v1y - v0y;
			auto vx = v2x - v0x; auto vy = v2y - v0y;

			auto arc0 = std::acos(dot(ux, uy, vx, vy) / (length(ux, uy) * length(vx, vy)));

			if (arc0 > 0.25f * PI && arc0 < 0.75f * PI && 
				length(ux, uy) < lengthLimit &&
				length(vx, vy) < lengthLimit) fineTirangle = true;
		}

		outputFile << v0x << " " << v0y << " ";
		outputFile << v1x << " " << v1y << " ";
		outputFile << v2x << " " << v2y << " ";
		outputFile << std::endl;
	}
	
	outputFile.close();
}