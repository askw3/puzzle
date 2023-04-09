//============================================================================
// Name        : main.cpp
// Author      : askw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// 標準入出力
#include <iostream>
// 文字詰め、文字埋め
#include <ios>     // std::left, std::right
#include <iomanip> // std::setw(int), std::setfill(char)

using namespace std; // stdの記述を省略

#include "rulebook.h"
#include "fields.h"

class Main{

};

int main() {
	int topScore = 0;
	char ch;

	bool endflag = false;

	Rulebook rule;
	Fields fld;

	while(!(endflag)){
		// ゲームタイトル
		cout << "\n\n\n";
		cout << "　落ちものパズル\n" << endl;

		// TOP SCOREの表示
		cout << "===================\n" << endl;
		cout << "   TOP-SCORE:" << topScore << "\n" << endl;
		cout << "===================\n" << endl;

		// キー入力を促す
		cout << right << setw(17) << "GAME START : \"Y\" " << endl;
		cout << right << setw(17) << "GAME RULE : \"R\" " << endl;
		cout << right << setw(17) << "EXIT : \"N\" " << endl;

		cin.exceptions(ios::failbit);

		// キー入力を受け取る
		cin >> ch;

		if(ch == 'Y'){
			cout << "\n\n\n" << endl;
			topScore = fld.start();
		}
		else if(ch == 'R'){
			cout << "ルール表示" << endl;
			rule.rule();
		}
		else if(ch == 'N'){
			cout << "ゲーム終了" << endl;
			endflag = true;
		}
		else{
			cout << "その他の入力" << endl;
		}
	}


	// 例外処理
	//try{
	//	cin >> ch;
	//}
	//catch(char c){
	//	cout << "だめです。" << endl;
	//	cin.clear();
	//	cin.seekg(0);
	//}

	return 0;
}
