void A()
{
	//定义分块的高和宽 
	int m1=bmpHeight/M;
	int n1=bmpWidth/N;
	int linebyte =(bmpWidth * biBitCount/8+3)/4*4;
	int linebyte1=(n1*biBitCount/8+3)/4*4/3*3;
	int temp=now[ly][lx];
	now[ly][lx]=now[ly][lx-1];
	now[ly][lx-1]=temp;
	for(int x=0;x<m1;x++)
		{
			for(int y=0;y<linebyte1;y++)
				{
					unsigned char temp1 = pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y];
					pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = pBmpBuf[((N-ly-1)*m1+x)*linebyte+(lx-1)*linebyte1+y];
					pBmpBuf[((N-ly-1)*m1+x)*linebyte+(lx-1)*linebyte1+y]=temp1; 
				}
		}
	lx--;
	step++;
	cout <<"A"<<" ";
}
