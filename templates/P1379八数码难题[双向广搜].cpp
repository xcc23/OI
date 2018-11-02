//已知初始状态和目标状态时可用双向搜索
//玄学:这份代码开O2才AC, 要少用STL
#include<cstdio>
#include<map>
#include<queue>
#define re register
using namespace std;
int str,endd=123804765;//矩阵只有3*3大小, 用int存方便放入queue
queue<int> shun,ni;
map<int,int> step,b;
//step[x]为达到x状态需要的步数(存放最先走到x状态的那个方向(顺推/逆推)的步数)
//b为标记数组, b[x]=1 则顺推已走过x状态 , b[x]=2 则逆推已走过x状态
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int a[4][4];//临时存矩阵
int x0,y0;//存0的位置
inline void zhuan(int x) //将状态x转存到二维数组里
{
	for(re int i=3;i>=1;--i)
	{
		for(re int j=3;j>=1;--j)
		{
			a[i][j]=x%10,x/=10;
			if(a[i][j]==0) x0=i,y0=j;
		}
	}
}
inline int zhuan() //将二位数组里的东西转化为int数
{
	int s=0;
	for(re int i=1;i<=3;++i)
		for(re int j=1;j<=3;++j)
			s=s*10+a[i][j];
	return s;
}
void bfs()
{
	shun.push(str);
	step[str]=0;
	ni.push(endd);
	step[endd]=0;
	//把起始状态放入顺推的搜索队列, 目标状态放入逆推的搜索队列
	if(str==endd)
	{
		printf("0\n");
		return;
	}
	while(!shun.empty() || !ni.empty()) //每次循环顺推逆推各走一步(拓展一层)
	{
		int x=shun.front();
		shun.pop();
		zhuan(x);
		for(re int i=0;i<4;i++)
		{
			
			int x1=x0+dx[i],y1=y0+dy[i];
			if(x1>=1 && x1<=3 && y1>=1 && y1<=3)
			{
				a[x0][y0]=a[x1][y1];
				a[x1][y1]=0;
				//上面是交换
				int t=zhuan();
				if(b[t]!=2)
				{
					shun.push(t);
					step[t]=step[x]+1;
					b[t]=1;
				}
				else{//若b[t]==2, 则逆推已走到这一状态, 现在顺推也到了这一状态, 顺推逆推汇合了
					printf("%d\n",step[x]+1+step[t]);
//step[x]是顺推到这一状态的上一步的步数, step[t]是逆推到这一状态的步数,总步数要加起来并再加1(x也要走到t,所以+1)
					return;
				}
				a[x1][y1]=a[x0][y0];
				a[x0][y0]=0;
				//为了枚举这一层的下一种情况, 要还原
			}
		}
		x=ni.front();
		ni.pop();
		zhuan(x);
		for(re int i=0;i<4;i++)
		{
			
			int x1=x0+dx[i],y1=y0+dy[i];
			if(x1>=1 && x1<=3 && y1>=1 && y1<=3)
			{
				a[x0][y0]=a[x1][y1];
				a[x1][y1]=0;
				int t=zhuan();
				if(b[t]!=1)
				{
					ni.push(t);
					step[t]=step[x]+1;
					b[t]=2;
				}
				else{
					printf("%d\n",step[x]+1+step[t]);
					return;
				}
				a[x1][y1]=a[x0][y0];
				a[x0][y0]=0;

			}
		}
	}
}
int main()
{
	scanf("%d",&str);
	bfs();
	return 0;
}
