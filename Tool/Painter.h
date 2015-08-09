#ifndef _MEMORYPAINTER_H_
#define _MEMORYPAINTER_H_

#include "../Tool/ImgDevice.h"
#include "../Tool/Geometry.h"

namespace MyTools
{

	template <typename T = int>
	class QQQQ
	{
	public:
		QQQQ(){};
		~QQQQ(){};

	private:

	};
	template <typename ImgDeviceType = MemoryImgDevice<unsigned char,int>>
	class Painter
	{
	public:
		typedef ImgDeviceType Device;
		typedef typename ImgDeviceType::ImgDataType DataType;
		typedef typename ImgDeviceType::CoordinateType CoorType;
		typedef DataType* DataPtr;
		typedef typename MyTools::Point<CoorType> Point;
	public:
		Painter(int width, int height,int channel)
			:device(width, height,channel)
		{
		}

		~Painter()
		{
		}
		void DrawPoint(CoorType x, CoorType y)
		{
			device.DrawPoint(x, y);
		}
		void DrawLine(CoorType x1, CoorType y1, CoorType x2, CoorType y2)
		{
			drawLineBresenham(x1, y1, x2, y2);
		}
		void DrawLine(const Point &pt1, const Point &pt2)
		{
			drawLineBresenham(pt1.x,pt1.y, pt2.x,pt2.y);
		}
		void DrawCircle(CoorType centre_x, CoorType centre_y, CoorType radius)
		{
			drawCircleBresenham(centre_x, centre_y, radius);
		}
		void DrawCircle(const Point& centre, CoorType radius)
		{
			drawCircleBresenham(centre.x,centre.y, radius);
		}

		DataPtr GetImgData()
		{
			return device.GetImgData();
		}

		int GetWidth()
		{
			return device.GetWidth();
		}

		int GetHeight()
		{
			return device.GetHeight();
		}

		int GetChannelCount()
		{
			return device.GetChannelCount();
		}
	private:
		void drawCircleBresenham(CoorType centre_x, CoorType centre_y,CoorType radius)
		{
			CoorType x = 0,
				y = radius,
				delta = 2 * (1 - radius);
			Point centre(centre_x, centre_y);
			while (y >= 0)
			{
				draw4SymmetryPoint4(x, y, centre);
				int direction;
				if (delta<0)
				{
					CoorType delta1 = 2 * (delta + y) - 1;
					if (delta1 <= 0)direction = 1; else direction = 2;
				}
				else if (delta>0)
				{
					CoorType delta2 = 2 * (delta - x) - 1;
					if (delta2 <= 0)direction = 2; else direction = 3;
				}
				else  direction = 2;
				switch (direction)
				{
				case 1:
					x++; delta += 2 * x + 1; break;
				case 2:
					x++; y--; delta += 2 * (x - y + 1); break;
				case 3:
					y--; delta += (-2 * y + 1); break;
				}
			}
		}
		void draw4SymmetryPoint4(CoorType x, CoorType y,const Point &centre)
		{
			CoorType x_offset = centre.x;
			CoorType y_offset = centre.y;
			device.DrawPoint(x + x_offset, y + y_offset);
			device.DrawPoint(-x + x_offset, y + y_offset);
			device.DrawPoint(-x + x_offset, -y + y_offset);
			device.DrawPoint(x + x_offset, -y + y_offset);
		}
		void drawLineBresenham(CoorType x1, CoorType y1, CoorType x2, CoorType y2)
		{
			CoorType x = x1, y = y1, dx = x2 - x1, dy = y2 - y1, e = -dx;
			for (int i = 0; i <= dx; ++i)
			{
				device.DrawPoint(x, y);
				x += 1;
				e += 2 * dy;
				if (e >= 0)
				{
					y += 1;
					e -= 2 * dx;
				}
			}
		}
	private:
		Device device;
	};
}

#endif