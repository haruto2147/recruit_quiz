#include "exam_japanese.h"
#include "utility.h"
#include "random"
using namespace std;

/*
* 漢字の読み取り問題を作成する
*/
QuestionList CreateKanjiExam()
{
	static const struct {
		const char* kanji;		//漢字
		const char* reading;	//読み
		const char* meaning;	//意味
	} data[] = {
		{ "市井", "しせい", "人が多く集まって暮らすところ、町" },
		{ "捺印", "なついん", "(署名と共に)印鑑をおすこと" },
		{ "相殺", "そうさい", "足し引きの結果、差がなくなること" },
		{ "凡例", "はんれい", "本や図表のはじめに、使い方や約束事を箇条書きにしたもの" },
		{ "約定", "やくじょう", "約束してきめること、契約" },
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	//問題の種類を選ぶ
	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0) {
		//漢字の読みを答える問題
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"「" + string(e.kanji) + "」の読みをひらがなで答えよ",
				e.reading });
		}
	}
	else {
		//正しい熟語を答える問題
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].meaning) +
				"」を意味する熟語の番号を選べ";
			for (int j = 0; j < 3; j++) {
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].kanji;
			}

			questions.push_back({ s, to_string(correctNo) });
		}
	}//if type
	return questions;
}