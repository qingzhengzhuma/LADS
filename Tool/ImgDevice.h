#ifndef _DEVICE_H_
#define _DEVICE_H_

namespace MyTools
{
	template<typename DataType,typename CoorType>
	class ImgDevice
	{
	public:
		typedef CoorType CoordinateType;
		typedef DataType ImgDataType;
		typedef ImgDataType* ImgDataPtr;
	public:
		ImgDevice(int width, int height,int channel) 
			: width(width),
			height(height),
			channel(channel)
		{
		}
		virtual ~ImgDevice()
		{
		}
		int GetWidth(){ return width; }
		int GetHeight(){ return height; }
		int GetChannelCount(){ return channel; }
		virtual void DrawPoint(CoordinateType x, CoordinateType y) = 0;
		virtual ImgDataPtr GetImgData() = 0;
	public:
		int width;
		int height;
		int channel;
	};

	template<typename DataType,typename CoorType>
	class MemoryImgDevice : public ImgDevice<DataType,CoorType>
	{	
	public:
		MemoryImgDevice(int width, int height,int channel)
			: ImgDevice(width,height,channel)
		{
			img = new ImgDataType[width*height*channel];
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width;++j)
				{
					img[i*width + j] = 255;
				}
			}
		}
		~MemoryImgDevice(){ delete[]img; }
		void DrawPoint(CoordinateType x, CoordinateType y)
		{
			if (x < 0 || x >= width || y < 0 || y >= height) return;
			img[y*width + x] = 0;
		}
		ImgDataPtr GetImgData()
		{
			return img;
		}
	private:
		ImgDataPtr img;
	};
}

#endif