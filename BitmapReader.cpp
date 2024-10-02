
#include "BitmapReader.h"

namespace bmp {

	BitmapReader::BitmapReader()
		: m_file()
		, m_header{}
		, m_info{}
	{

	}

	BitmapReader::~BitmapReader()
	{
		if (m_file.is_open())
		{
			m_file.close();
		}
	}

	void BitmapReader::openBMP(const std::string& path)
	{
		m_file.open(path, std::ios::binary);

		if (!m_file.is_open())
		{
			throw std::ios_base::failure("Can`t open .bmp file : " + path);
		}

		m_file.read((char*)&m_header, sizeof(BITMAPFILEHEADER));
		m_file.read((char*)&m_info,   sizeof(BITMAPINFOHEADER));

		if (m_header.bfType != BitmapReader::BITMAP_TYPE)
		{
			throw std::ios_base::failure("File isn`t .bmp format : " + path);
		}

		if (m_info.biBitCount != Version::BIT24 && m_info.biBitCount != Version::BIT32)
		{
			throw std::ios_base::failure("Unsupported file format : " + m_info.biBitCount);
		}
	}

	void BitmapReader::displayBMP()
	{
		if (!m_file.is_open())
		{
			throw std::invalid_argument("File is not open!");
		}

		int data   = m_info.biBitCount / 8;
		int height = m_info.biHeight;
		int width  = m_info.biWidth;
		int pos    = m_header.bfSize - (width * data);

		Pixel px{};

		m_file.seekg(pos, std::ios::beg);

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				m_file >> std::hex >> px.b >> px.g >> px.r;

				if (m_info.biBitCount == Version::BIT32)
				{
					m_file >> std::hex >> px.a;
				}

				std::cout << (isMoreBlackPixel(px) ? BLACK_PX : WHITE_PX);
			}
			pos -= width * data;
			std::cout << '\n';
			m_file.seekg(pos, std::ios::beg);
		}
	}

	void BitmapReader::closeBMP()
	{
		std::memset(&m_header, 0, sizeof(BITMAPFILEHEADER));
		std::memset(&m_info,   0, sizeof(BITMAPINFOHEADER));
		m_file.close();
	}

	bool BitmapReader::isMoreBlackPixel(const Pixel& px)
	{
		double distanceToBlack = distance(px, { 0, 0, 0 });
		double distanceToWhite = distance(px, { 255, 255, 255 });
		return distanceToBlack < distanceToWhite;
	}

	double BitmapReader::distance(const Pixel& px, const Pixel& color)
	{
		return std::sqrt(std::pow(px.r - color.r, 2) +
						 std::pow(px.g - color.g, 2) +
						 std::pow(px.b - color.b, 2));
	}
}