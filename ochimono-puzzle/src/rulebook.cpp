/*
 * rulebook.cpp
 *
 *  Created on: 2023/03/28
 *      Author: askw
 */

// 標準入出力
#include <iostream>

// 文字詰め、文字埋め
#include <ios>     // std::left, std::right
#include <iomanip> // std::setw(int), std::setfill(char)

// ファイル読み取り・書き出し
#include <fstream>

// string
#include <string>

// ヘッダーファイル
#include "rulebook.h"

using namespace std; // stdの記述を省略

// ルール文表示関数
void Rulebook::rule(){
	ifstream file("rule.txt");
	string line;

	string str;

	cout << "落ちものパズルです。" << endl;

	while(getline(file, line)){// １行ずつ読み取り
		cout << line << endl;
	}

	cout << "メニューに戻るには\n";
	cout << "いずれかのボタンを\n";
	cout << "押してください.." << endl;

	cin >> str;
}
