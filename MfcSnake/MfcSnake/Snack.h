#pragma once
struct Point  // 具体的每一个点
{
	int x;
	int y;
};

class CSnake
{
public:
	CSnake();
	~CSnake(); 
	int len;  // 蛇的长度
	Point body[1255];  // 蛇的身体
	int direc;   // 运动方向
	void UpMove();  // 向上运动
	void DownMove();  // 向下运动 
	void LeftMove();  // 向左运动
	void RightMove();  // 向右运动
	void init();


private:

};
