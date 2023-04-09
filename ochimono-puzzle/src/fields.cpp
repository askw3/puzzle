/*
 * fields.cpp
 *
 *  Created on: 2023/03/28
 *      Author: askw
 */

// 標準入出力
#include <iostream>
// string
#include <string>

// コンソールの内容をクリアするsystem("cls")
#include <cstdlib>

// 処理を止める
#include <thread>
//#include <unistd.h>

// 乱数の生成
#include <random>

// _getch()
#include <conio.h>

// キー入力読み込み
#include <windows.h>

// vector
#include <vector>
#include <algorithm>
// set
#include <set>

// 1秒ごとに更新処理
#include <chrono>
#include <thread>

// ヘッダーファイル
#include "fields.h"

#include "blocks.h"
#include "scores.h"

using namespace std; // stdの記述を省略
using std::this_thread::sleep_for;

const int FIELD_WIDTH = 18;
const int FIELD_DEPTH = 26;


// フィールドの初期化
void initialize_field(vector<vector<int>> &mat){
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 18; j++){
			if(i <= 1){
				mat[i][j] = -1;
			}
			else if(i >= 23){
				mat[i][j] = -2;
			}
			else if(j < 3 || j > 14){
				mat[i][j] = -1;
			}
			else if(i == 22){// 床部分
				mat[i][j] = 4;
			}
			else if(j == 3 || j == 14){// 壁部分
				mat[i][j] = 3;
			}
			else{// 空白部分
				mat[i][j] = 0;
			}
		}
	}
}

// ブロックの回転
void spin_block(vector<vector<int>>& block, int num, int angle){
	Blocks blocks;

	num = num % 7;

	if(num == 0){
		if(angle == 0){
			block = blocks.block0.b0;
		}
		else if(angle == 90){
			block = blocks.block0.b90;
		}
		else if(angle == 180){
			block = blocks.block0.b180;
		}
		else if(angle == 270){
			block = blocks.block0.b270;
		}
	}
	else if(num == 1){
		if(angle == 0){
			block = blocks.block1.b0;
		}
		else if(angle == 90){
			block = blocks.block1.b90;
		}
		else if(angle == 180){
			block = blocks.block1.b180;
		}
		else if(angle == 270){
			block = blocks.block1.b270;
		}
	}
	else if(num == 2){
		if(angle == 0){
			block = blocks.block2.b0;
		}
		else if(angle == 90){
			block = blocks.block2.b90;
		}
		else if(angle == 180){
			block = blocks.block2.b180;
		}
		else if(angle == 270){
			block = blocks.block2.b270;
		}
	}
	else if(num == 3){
		if(angle == 0){
			block = blocks.block3.b0;
		}
		else if(angle == 90){
			block = blocks.block3.b90;
		}
		else if(angle == 180){
			block = blocks.block3.b180;
		}
		else if(angle == 270){
			block = blocks.block3.b270;
		}
	}
	else if(num == 4){
		if(angle == 0){
			block = blocks.block4.b0;
		}
		else if(angle == 90){
			block = blocks.block4.b90;
		}
		else if(angle == 180){
			block = blocks.block4.b180;
		}
		else if(angle == 270){
			block = blocks.block4.b270;
		}
	}
	else if(num == 5){
		if(angle == 0){
			block = blocks.block5.b0;
		}
		else if(angle == 90){
			block = blocks.block5.b90;
		}
		else if(angle == 180){
			block = blocks.block5.b180;
		}
		else if(angle == 270){
			block = blocks.block5.b270;
		}
	}
	else if(num == 6){
		if(angle == 0){
			block = blocks.block6.b0;
		}
		else if(angle == 90){
			block = blocks.block6.b90;
		}
		else if(angle == 180){
			block = blocks.block6.b180;
		}
		else if(angle == 270){
			block = blocks.block6.b270;
		}
	}
}

// 回転可能の判定
bool check_spin_able(vector<vector<int>> field, vector<vector<int>> block, int& rPos, int& cPos){
	Blocks blocks;
	bool able_spin = true;

	int i, j;
	int missI = 0;
	int missJ = 0;

	int default_rPos = rPos;
	int default_cPos = cPos;

	// ブロック回転後のフィールドの仮計算
	for (i = rPos; i < rPos + 4; i++){
		for (j = cPos; j < cPos + 4; j++){
			field[i][j] += block[i - rPos][j - cPos];
			if(block[i - rPos][j - cPos] == 1){
				if(field[i][j] == 3 || field[i][j] == 5){
					missI = 1;
				}
				else if(field[i][j] == -1){
					missI ++;
				}
				else if(field[i][j] == 4){
					missJ = 1;
				}
				else if(field[i][j] == 0){
					missJ ++;
				}
			}
		}
	}

	// ブロック位置の再計算
	if(missI != 0){
		rPos -= missI;
	}
	if(missJ != 0){
		cPos -= missJ;
	}

	// 再び仮計算し、また回転不可能だった場合回転不可能判定しブロックを元の位置に
	i = rPos;
	j = cPos;
	while(able_spin && i < rPos + 4 && j < cPos + 4){
		field[i][j] += block[i - rPos][j - cPos];
		if(missI == 0 && block[i - rPos][j - cPos] == 1 && (field[i][j] == 3 || field[i][j] == 5 || field[i][j] == -1)){
			able_spin = false;
			rPos = default_rPos;
			cPos = default_cPos;
		}
		if(missJ == 0 && block[i - rPos][j - cPos] == 1 && (field[i][j] == 4 || field[i][j] == 0)){
			able_spin = false;
			rPos = default_rPos;
			cPos = default_cPos;
		}
//		field[i][j] += block[i - rPos][j - cPos];
//		if(field[i][j] >= 3){
//			able_spin = false;
//			rPos = default_rPos;
//			cPos = default_cPos;
//		}
		i ++;
		j ++;
	}

	return able_spin;
}

// ブロックの取得
void get_block(vector<vector<int>> &block, int num){
	Blocks blocks;

	num = num % 7;

	if(num == 0){
		block = blocks.block0.b0;
	}
	else if(num == 1){
		block = blocks.block1.b0;
	}
	else if(num == 2){
		block = blocks.block2.b0;
	}
	else if(num == 3){
		block = blocks.block3.b0;
	}
	else if(num == 4){
		block = blocks.block4.b0;
	}
	else if(num == 5){
		block = blocks.block5.b0;
	}
	else if(num == 6){
		block = blocks.block6.b0;
	}
}

// 前のブロックの情報の消去
void erase_prev_block(vector<vector<int>> &field, int rPos, int cPos){
	int i, j;

	for (i = rPos; i < rPos + 4; i++){
		for (j = cPos; j < cPos + 4; j++){
			if(field[i][j] == 1 && i <= 1){
				field[i][j] = -1;
			}
			else if(field[i][j] == 1 && i <= 21){
				field[i][j] = 0;
			}
		}
	}
}

// 落下しているブロックの計算
void calc_dropBlock(vector<vector<int>> &field, vector<vector<int>> dropBlock, int rPos, int cPos){
	int i, j;

	for (i = rPos; i < rPos + 4; i++){
		for (j = cPos; j < cPos + 4; j++){
			field[i][j] += dropBlock[i - rPos][j - cPos];
		}
	}
}

// 左移動可能判定
bool check_left_move(vector<vector<int>> field, int rPos, int cPos){
	bool able_left = true;

	// 左の壁に対しその右隣りに"1"があるかを判定する
	for (int i = rPos; i < rPos + 4; i++){
		for (int j = cPos; j < cPos + 4; j++){
			if((field[i][j - 1] == 3 || field[i][j - 1] == 2) && field[i][j] == 1){
				able_left = false;
			}
		}
	}

	return able_left;
}
// 右移動可能判定
bool check_right_move(vector<vector<int>> field, int rPos, int cPos){
	bool able_right = true;

	// 右の壁に対しその左隣りに"1"があるかを判定する
	for (int i = rPos; i < rPos + 4; i++){
		for (int j = cPos; j < cPos + 4; j++){
			if((field[i][j + 1] == 3 || field[i][j + 1] == 2) && field[i][j] == 1){
				able_right = false;
			}
		}
	}

	return able_right;
}
// 下移動可能判定
bool check_down_move(vector<vector<int>> field){
	bool able_down = true;

	return able_down;
}


// プレイ画面の表示
void field_display(vector<vector<int>> field,int countBlocks, int goalScore, vector<vector<int>> nextBlock){
	int i, j, k;

	// プレイ画面本体
	cout << "\n残りライン：" << goalScore << "\n" << endl;

	for (i = 0; i < 23; i++){
		if(!(i == 0 || i == 1)){
			// フィールドの表示
			for (j = 0; j < 18; j++){
				if(field[i][j] >= 3){
					cout << "■";
				}
				else if(field[i][j] == 1 || field[i][j] == 2){
					cout << "□";
				}
				else if(field[i][j] == 0){
					cout << "　";
				}
			}

			// 以下UIの表示
			// NEXTブロックの表示
			if(i == 4){
				cout << "　　　  NEXT";
			}
			if(i == 5){
				cout << "　　============";
			}
			if(i == 7){
				cout << "　　　";
				for (k = 0; k < 4; k ++){
					if(nextBlock[0][k] >= 1){
						cout << "□";
					}
					else{
						cout << "　";
					}
				}
			}
			if(i == 8){
				cout << "　　　";
				for (k = 0; k < 4; k ++){
					if(nextBlock[1][k] >= 1){
						cout << "□";
					}
					else{
						cout << "　";
					}
				}
			}
			if(i == 10){
				cout << "　　============";
			}

			// 現在ブロック数の表示
			if(i == 13){
				cout << "　　現在：" << countBlocks << "個目";
			}

			// 操作説明文
			if(i == 18){
				cout << "　　w：回転";
			}
			if(i == 19){
				cout << "　　d：右移動";
			}
			if(i == 20){
				cout << "　　a：左移動";
			}
			if(i == 21){
				cout << "　　s：下移動";
			}
			cout << "\n";
		}
	}
}

// ブロックの着地判定
bool landing_check(vector<vector<int>> field, int rPos, int cPos){
	bool is_landing = false;
	int i, j;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(field[rPos + i][cPos + j] == 1 && field[rPos + i + 1][cPos + j] > field[rPos + i][cPos + j]){
				is_landing = true;
			}
		}
	}

	return is_landing;
}

// 接地したブロックの計算
void calc_droppedBlock(vector<vector<int>> &field, int rPos, int cPos){
	int i, j;

	for (i = rPos; i < rPos + 4; i++){
		for (j = cPos; j < cPos + 4; j++){
			if(field[i][j] == 1){
				field[i][j] = 2;
			}
		}
	}
}

// ブロックで満たされた行をチェックし消去
vector<int> erase_column(vector<vector<int>>& field){
	vector<int> vec = {};

	for(int i = 2; i < 22; i++){
		if(count(field[i].begin(), field[i].end(), 2) == 10){
			vec.push_back(i);
			field[i] = {-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1};
		}
	}

	return vec;
}

// 消された列の分だけ詰める
void close_column(vector<vector<int>>& field, int num){
	field.erase(field.begin() + num);
	field.insert(field.begin() + 2, {-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1});
}

// ゲームオーバーの判定
bool gameover_check(vector<vector<int>> field){
	bool is_gameover = false;
	int i, j;

	for(i = 0; i <= 2; i++){
		for(j = 7; j < 11; j++){
			if(field[i][j] == 2){
				is_gameover = true;
			}
		}
	}

	return is_gameover;
}
// 実行部分
int Fields::start(){

	Blocks blocks;

	int goalScore = 10;
	int nowScore = 0;
	int countBlocks = 0;

	int spinAngle;

	int initialRPos = 0;
	int initialCPos = 7;

	int cPos, rPos;

	long long int x, y;

	bool is_landing;
	bool is_gameover;

	bool able_left;
	bool able_right;

	random_device rnd;

	Scores scores;

	using namespace std::literals::chrono_literals;
	using clock = std::chrono::steady_clock;
	auto prev_end = clock::now();

	auto erase_end = clock::now();

	// デフォルトのフィールドの状態
	// -1, -2:緩衝材, 0:空, 1:落下中のブロック, 2:落下後のブロック, 3:側面, 4:床
	// 緩衝材が二種類なのは、回転可能判定の都合上
	vector<vector<int>> field = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
							{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, -1, -1},
							{-1, -1, -1, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, -1, -1, -1},
							{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
							{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2},
							{-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2}
	};

	vector<vector<int>> dropBlock = blocks.block0.b0;

	x = rnd();
	x = x % 7;

	vector<vector<int>> nextBlock;
	get_block(nextBlock, x);
	y = x;

	// フィールドの初期化
	initialize_field(field);
	is_gameover = false;

	// アイデア：switch caseを用いて、操作時と非操作時で処理を分ける
	while(!(is_gameover) && goalScore >= 1){
		// ブロックの取得
		dropBlock = nextBlock;
		y = x;
		x = rnd();
		x = x % 7;
		get_block(nextBlock, x);

		// ブロック初期位置
		rPos = initialRPos;
		cPos = initialCPos;
		able_right = true;
		able_left = true;
		spinAngle = 0;

		// 接地フラグの初期化
		is_landing = false;

		// 消えるラインの管理
		vector<int> bn_line = {};

		// 落下制限
		while(!(is_landing)) {

			// 移動可能判定
			able_left = check_left_move(field, rPos, cPos);
			able_right = check_right_move(field, rPos, cPos);
			// 前ブロック情報の消去
			erase_prev_block(field, rPos, cPos);

			// ブロック位置の移動
			if((GetAsyncKeyState( 'A' ) & 0x01) && able_left && rPos >= 2) {
			    cPos --;
			}
			else if((GetAsyncKeyState( 'D' ) & 0x01) && able_right && rPos >= 2) {
				cPos ++;
			}
			else if( GetAsyncKeyState( 'W' ) & 0x01 && rPos >= 2) {
				spinAngle = (spinAngle + 90) % 360;
				spin_block(dropBlock, y, spinAngle);
				if(!(check_spin_able(field, dropBlock, rPos, cPos))){
					spinAngle = (spinAngle - 90) % 360;
					spin_block(dropBlock, y, spinAngle);
				}
			}
			else if( GetAsyncKeyState( 'S' ) & 0x01) {
				rPos ++;
			}
			else{
				// 0.5秒ごとに画面を更新する
				std::this_thread::sleep_until(prev_end + 0.5s);
				prev_end = clock::now();
				rPos += 1;
			}

			// ブロック位置の計算
			calc_dropBlock(field, dropBlock, rPos, cPos);


			// 床部分への判定
			is_landing = landing_check(field, rPos, cPos);
			// 落下したブロックを落下済みにする
			if(is_landing){
				calc_droppedBlock(field, rPos, cPos);
				countBlocks ++;

				// ブロックで詰まった列を消去
				bn_line = erase_column(field);
				goalScore -= bn_line.size();
				if(goalScore < 0){
					goalScore = 0;
				}
				// 消去の演出を表示
				field_display(field, countBlocks, goalScore, nextBlock);
				erase_end = clock::now();
				std::this_thread::sleep_until(erase_end + 1s);
				erase_end = clock::now();
				// 間を詰める
				for(auto &el : bn_line){
					close_column(field, el);
				}
				// GAME OVERの判定
				is_gameover = gameover_check(field);
			}

			// フィールドの表示
			cout << "\x1B[3J\x1B[H";
			field_display(field, countBlocks, goalScore, nextBlock);

			//char a;
			//cin >> a;
			cin.clear();
		}
	}

	int final_score = scores.updateScore(nowScore, countBlocks);

	return final_score;
}
