/*
 * scores.cpp
 *
 *  Created on: 2023/03/28
 *      Author: askw
 */

// 標準入出力
#include <iostream>
// string
#include <string>

// ヘッダーファイル
#include "scores.h"

using namespace std; // stdの記述を省略

// スコアのアップデート、リザルトの表示、トップスコアの受け渡しを行う
int Scores::updateScore(int score, int countBlocks){
	string str;

	// スコアのアップデート
	this->nowScore = score;
	if(this->topScore <= this->nowScore){
		this->topScore = this->nowScore;
	}

	// リザルトの表示
	cout << "リザルト\n\n";

	if(score == 0){
		cout << "クリア!!!!!!" << endl;
	}
	else{
		cout << "ミス..." << endl;
	}

	cout << "使用した個数は：" << countBlocks << "個" << endl;

	cout << "メニューに戻るには\n";
	cout << "いずれかのボタンを\n";
	cout << "押してください.." << endl;

	cin >> str;

	// トップスコアの受け渡し
	return this->topScore;
}
