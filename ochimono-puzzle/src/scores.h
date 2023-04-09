/*
 * scores.h
 *
 *  Created on: 2023/03/28
 *      Author: askw
 */

#ifndef SCORES_H_
#define SCORES_H_


class Scores{
public:
	int topScore = 0;
	int nowScore = 0;
	int updateScore(int score, int countBlocks);
};


#endif /* SCORES_H_ */
