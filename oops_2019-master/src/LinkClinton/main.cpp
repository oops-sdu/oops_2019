#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <memory>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

template<typename T>
struct Color {
	T Red = 0;
	T Green = 0;
	T Blue = 0;
	T Alpha = 1;

	Color() = default;

	Color(
		const T& red,
		const T& green,
		const T& blue,
		const T& alpha = 1) :
		Red(red), Green(green), Blue(blue), Alpha(alpha) {}
};

template<typename T>
struct Vec2 {
	T X = 0;
	T Y = 0;

	Vec2() = default;

	Vec2(
		const T& x,
		const T& y) :
		X(x), Y(y) {}

	Vec2 operator-(const Vec2& right) const { return Vec2(X - right.X, Y - right.Y); }

	/*
	 * @brief test a point if in the triangle
	 * @param[in] point
	 * @param[in] v0 the 1st vertex of triangle
	 * @param[in] v1 the 2nd vertex of triangle
	 * @param[in] v2 the 3rd vertex of triangle
	 * @return true means the point is in the triangle, else false
	 */
	static bool isInTriangle(
		const Vec2& point,
		const Vec2& v0,
		const Vec2& v1,
		const Vec2& v2);

	friend std::istream& operator>>(std::istream& input, Vec2& vec) {
		return input >> vec.X >> vec.Y;
	}
};

using Vec2f = Vec2<float>;
using Colorf = Color<float>;

template<typename T>
class Canvas {
public:
	Canvas() = delete;

	/*
	 * @brief ctor of canvas
	 * @param[in] width the width of canvas
	 * @param[in] height the height of canvas
	 */
	explicit Canvas(size_t width, size_t height, Color<T> clear = Color<T>()) :
		mWidth(width), mHeight(height), mFrameBuffer(mWidth* mHeight, clear) {}

	/*
	 * @brief set the color of pixel at (x, y)
	 * @param[in] x x-position of pixel[0, width)
	 * @param[in] y y-position of pixel[0, height)
	 * @param[in] color the color
	 */
	void set(size_t x, size_t y, const Color<T>& color);

	/*
	* @brief get the color of pixel at (x, y)
	* @param[in] x x-position of pixel[0, width)
	* @param[in] y y-position of pixel[0, height)
	* @return the color of pixel
	*/
	auto get(size_t x, size_t y) const noexcept->Color<T>;

	auto width() const noexcept -> size_t { return mWidth; }

	auto height() const noexcept -> size_t { return mHeight; }

	auto frameBuffer() const noexcept -> const Color<T>* { return mFrameBuffer.data(); }
private:
	size_t mWidth;
	size_t mHeight;

	std::vector<Color<T>> mFrameBuffer;
};

class Renderer {
public:
	Renderer() = default;

	/*
	 * @brief ctor or renderer
	 * @param[in] canvas the canvas we will draw to
	 */
	explicit Renderer(const std::shared_ptr<Canvas<float>>& canvas) :
		mCanvas(canvas) {}

	/*
	 * @brief save the canvas to image(.png)
	 * @param[in] fileName name of image file(without .png)
	 * for example, if you want to get a image named "x.png", you should put "x" to "fileName"
	 */
	void saveCanvas(
		const std::string& fileName);

	/*
	 * @brief draw a triangle to canvas
	 * @param[in] v0 the 1st vertex of triangle
	 * @param[in] v1 the 2nd vertex of triangle
	 * @param[in] v2 the 3rd vertex of triangle
	 */
	void drawTriangle(
		const Vec2f& v0,
		const Vec2f& v1,
		const Vec2f& v2);
private:
	std::shared_ptr<Canvas<float>> mCanvas;
};

template<typename T>
bool Vec2<T>::isInTriangle(const Vec2& point, const Vec2& v0, const Vec2& v1, const Vec2& v2) {
	auto cross = [&](const Vec2& u, const Vec2& v) {
		return u.X * v.Y - u.Y * v.X;
	};

	auto area = [&](const Vec2& u, const Vec2& v, const Vec2& p) {
		return cross(v - u, p - u);
	};

	auto triangleArea = area(v0, v1, v2);
	auto subArea0 = area(v1, v2, point) / triangleArea;
	auto subArea1 = area(v2, v0, point) / triangleArea;
	auto subArea2 = area(v0, v1, point) / triangleArea;

	return !(subArea0 < 0 || subArea1 < 0 || subArea2 < 0);
}

template<typename T>
void Canvas<T>::set(size_t x, size_t y, const Color<T>& color) {
	mFrameBuffer[y * mWidth + x] = color;
}

template<typename T>
auto Canvas<T>::get(size_t x, size_t y) const noexcept -> Color<T> {
	return mFrameBuffer[y * mWidth + x];
}

void Renderer::saveCanvas(const std::string& fileName) {
	auto colors = std::vector<Color<unsigned char>>(mCanvas->width() * mCanvas->height());

	for (size_t index = 0; index < colors.size(); index++) {
		auto& hdrColor = mCanvas->frameBuffer()[index];

		colors[index].Red = hdrColor.Red * 255;
		colors[index].Green = hdrColor.Green * 255;
		colors[index].Blue = hdrColor.Blue * 255;
		colors[index].Alpha = (hdrColor.Red != 0 || hdrColor.Green != 0 || hdrColor.Blue != 0) ? 255 : 0;
	}

	stbi_write_png((fileName + ".png").c_str(),
		static_cast<int>(mCanvas->width()),
		static_cast<int>(mCanvas->height()),
		4,
		colors.data(),
		0);
}

void Renderer::drawTriangle(const Vec2f& v0, const Vec2f& v1, const Vec2f& v2) {
	//putting your code and having fun
}

/*
 * @brief
 * @argv[0] program name
 * @argv[1] input data file name
 * @argv[2] output image file name
 */
int main(int argc, char** argv) {

	auto inputFile = std::ifstream(argv[1]);

	size_t width;
	size_t height;
	size_t n;

	inputFile >> n >> width >> height;

	auto canvas = std::make_shared<Canvas<float>>(width, height, Colorf(1, 1, 1, 1));
	auto renderer = std::make_shared<Renderer>(canvas);

	for (size_t index = 0; index < n; index++) {
		Vec2f v0, v1, v2;

		inputFile >> v0 >> v1 >> v2;

		renderer->drawTriangle(v0, v1, v2);
	}

	renderer->saveCanvas(argv[2]);

	inputFile.close();
}