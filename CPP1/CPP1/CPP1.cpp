// CPP1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	//std::ifstream in_stream("a.txt");

	//string source;
	//source.assign(std::istreambuf_iterator<char>(in_stream),
	//	std::istreambuf_iterator<char>()); // �ļ��������������ַ���

	std::ifstream t("a.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	cout << str.c_str() << endl;
	Sleep(10000);
	return 0;
}

