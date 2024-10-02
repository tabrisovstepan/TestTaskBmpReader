#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>

namespace bmp {

	enum Version {
		BIT24 = 24,
		BIT32 = 32
	};

	class BitmapReader {
	public:
		BitmapReader();
		~BitmapReader();

		BitmapReader(const BitmapReader&)  = delete;
		BitmapReader(const BitmapReader&&) = delete;

		BitmapReader& operator= (const BitmapReader&)  = delete;
		BitmapReader& operator= (const BitmapReader&&) = delete;

		void openBMP(const std::string& path);
		void displayBMP();
		void closeBMP();

		struct Pixel {
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};

	private:
		bool   isMoreBlackPixel(const Pixel& px);
		double distance(const Pixel&px, const Pixel& color);

	private:
		static const uint16_t BITMAP_TYPE = 0x4D42; // 'BM' in hex
		static const char 	  BLACK_PX    = '#';
		static const char 	  WHITE_PX    = '-';

		std::ifstream    m_file;
		BITMAPFILEHEADER m_header;
		BITMAPINFOHEADER m_info;
	};
}