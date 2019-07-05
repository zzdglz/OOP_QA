bool readbmp(char *bmpName) //给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中的函数 
{
    FILE *fp=fopen(bmpName,"rb");
	//二进制读方式打开指定的图像文件
    if(fp==0)
      { 
	     return 0;		 
      }
      
    fseek(fp, sizeof(BITMAPFILEHEADER),0);//跳过位图文件头结构BITMAPFILEHEADER
    
    BITMAPINFOHEADER infoheader;  
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量infoheader中
    
	fread(&infoheader, sizeof(BITMAPINFOHEADER), 1,fp); 
	//获取图像宽、高、每像素所占位数等信息
    
	bmpWidth = infoheader.biWidth;
    bmpHeight = infoheader.biHeight;    
	biBitCount = infoheader.biBitCount;

	int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	    
	if(biBitCount==8)//灰度图像有颜色表，且颜色表表项为256
      {
        pColorTable=new RGBQUAD[256];
		//申请颜色表所需要的空间，读颜色表进内存
        fread(pColorTable,sizeof(RGBQUAD),256,fp);
      }
    
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf=new unsigned char[lineByte * bmpHeight];
	pBmpBuf0=new unsigned char[lineByte * bmpHeight];
	pBmpBuf1=new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf,1,lineByte * bmpHeight,fp);
	fread(pBmpBuf0,1,lineByte * bmpHeight,fp);
	fread(pBmpBuf1,1,lineByte * bmpHeight,fp);
    fclose(fp);//关闭文件
    return 1;//读取文件成功
}
