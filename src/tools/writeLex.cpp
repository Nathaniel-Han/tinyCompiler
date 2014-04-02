#include<stdio.h>


#define INDEX(N) index##N

int main()
{
   
   
   int tbl[30][128];
   int i,j;
   
   for(j=0;i<128;i++)
      tbl[0][j] = 0;

   
   for(i=0;i<30;i++)
      for(j=0;j<128;j++)
	      tbl[i][j] = -99;
	
    
   int index[78]; // 0-9:0-9 
                  // 16-67:a-zA-Z
   index[0]='0';
   for(i=1;i<=9;i++)
   {
      index[i] = index[0]+i;
   }
   index[10] = '(';
   index[11] = ')';
   index[12] = '+';
   index[13] = '-';
   index[14] = '*';
   index[15] = '/';
   index[16] = 'A';
   
   for(i=1;i<=25;i++)
   {
      index[16+i] = index[16]+i;
   }
   
   index[42] = 'a';
   for(i=1;i<=25;i++)
   {
      index[42+i] = index[42] + i;
   }
   
   index[68] = 'E',
   index[69] = 'e', //可能需要特殊处理 
   index[70] = '!',
   index[71] = '=',
   index[72] = '<',
   index[73] = '>',
   index[74] = '{',
   index[75] = '}',
   index[76] = ';',
   index[77] = '\n',
   index[78] = '.';
   
   for(i=0;i<=9;i++)
       tbl[1][index[i]]=10;
	
   tbl[1]['(']=2;
   tbl[1][')']=3;
   tbl[1]['+']=4;
   tbl[1]['-']=6;
   tbl[1]['*']=5;
   tbl[1]['/']=7;
  
   for(i=16;i<=67;i++)
      tbl[1][index[i]]=25;
	 
    tbl[1]['!']=16;
	tbl[1]['=']=18;
	tbl[1]['<']=19;
	tbl[1]['>']=21;
	tbl[1]['{']=23;
	tbl[1]['}']=24;
	tbl[1][';']=17;
	tbl[1]['\n']=1;
	tbl[1]['\r']=1;
	tbl[1]['\t']=1;
	
	for(i=0;i<128;i++)
	{
	   tbl[2][i]=-1;
	   tbl[3][i]=-2;
	   tbl[4][i]=-3;
	   tbl[5][i]=-4;
	   tbl[6][i]=-5;
	   tbl[7][i]=-7;
	   tbl[8][i]=8;
	   tbl[9][i]=-6;
	   tbl[10][i]=-8;
	   //tbl[11][i]=-10;
	   tbl[12][i]=-9;
	   tbl[14][i]=-10;
	   tbl[15][i]=-11;
	   tbl[16][i]=-13;
	   tbl[17][i]=-14;
	   tbl[18][i]=-15;
	   tbl[19][i]=-17;
	   tbl[20][i]=-18;
	   tbl[21][i]=-20;
	   tbl[22][i]=-19;
	   tbl[23][i]=-21;
	   tbl[24][i]=-22;
	   tbl[25][i]=-23;
	   tbl[26][i]=-16;
	   tbl[27][i]=-12;
	}
	
	tbl[7]['/']=8;
	tbl[8]['\n']=tbl[8]['\r']=9;
	tbl[10]['E']=tbl[10]['e']=13;
	tbl[10]['.']=11;
	for(i=0;i<=9;i++)
	{
	   tbl[10][index[i]]=10;
	   tbl[11][index[i]]=12;
	   tbl[12][index[i]]=12;
	   tbl[13][index[i]]=15;
	   tbl[14][index[i]]=15;
	   tbl[15][index[i]]=15;
	}
	tbl[12]['E']=tbl[12]['e']=13;
	tbl[13]['+']=tbl[13]['-']=14;
	tbl[16]['=']=27;
	tbl[18]['=']=26;
	tbl[19]['=']=20;
	tbl[21]['=']=22;
	   
	   
	//补充 关于0状态到1状态的转化
	for(int i=0;i<=32;i++)
	   tbl[1][i]=1;
	
	//标识符识别状态转换
	for(i=0;i<9;i++)
	   tbl[25][index[i]]=25;
	
	for(i=16;i<=67;i++)
       tbl[25][index[i]]=25;
	
	
	FILE *fp = fopen("lex.txt","w");
	for(i=0;i<30;i++)
	{
	  {
	     for(j=0;j<128;j++)
	       fprintf(fp, "%d ", tbl[i][j]);
	  }
	  
	  //fprintf(fp,"\n");
	}
	
	
	fclose(fp);
	
	return 0;
}
		
	    
	   