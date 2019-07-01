//保存图片函数 
bool savebmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable)
{
    if(!imgBuf)
      {
	     return 0;
	  }//如果位图数据指针为0，则没有数据传入，函数返回 

    int colorTablesize=0;
    if(biBitCount==8)
      {
          colorTablesize=1024;
      }//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0 

	int lineByte=(width * biBitCount/8+3)/4*4;
    //待存储图像数据每行字节数为4的倍数

    FILE *fp=fopen(bmpName,"wb");
    //以二进制写的方式打开文件
    if(fp==0)
      {
          return 0;
      }

    BITMAPFILEHEADER fileHead;
    //申请位图文件头结构变量，填写文件头信息

    fileHead.bfType = 0x4D42;
	//bmp类型

    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ colorTablesize + lineByte*height;
    //bfSize是图像文件4个组成部分之和

    fileHead.bfReserved1 = 0;
    fileHead.bfReserved2 = 0;

    fileHead.bfOffBits=54+colorTablesize;
    //bfOffBits是图像文件前3个部分所需空间之和

    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
      //写文件头进文件

    BITMAPINFOHEADER head;  //申请位图信息头结构变量，填写信息头信息
    head.biBitCount=biBitCount;
    head.biClrImportant=0;
    head.biClrUsed=0;
    head.biCompression=0;
    head.biHeight=height;
    head.biPlanes=1;
    head.biSize=40;
    head.biSizeImage=lineByte*height;
    head.biWidth=width;
    head.biXPelsPerMeter=0;
    head.biYPelsPerMeter=0;

    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
    //写位图信息头进内存

    if(biBitCount==8)
       {
	       fwrite(pColorTable, sizeof(RGBQUAD),256, fp); //如果灰度图像，有颜色表，写入文件 
       }

    fwrite(imgBuf, height*lineByte, 1, fp);
     //写位图数据进文件

    fclose(fp);
    //关闭文件
    
    return 1;
}
