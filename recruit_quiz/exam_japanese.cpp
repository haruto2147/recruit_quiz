#include "exam_japanese.h"
#include "utility.h"
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

	for (int i = 0; i < quizCount; i++) {
		const auto& e = data[indices[i]];
		questions.push_back({
			"「" + string(e.kanji) + "」の読みをひらがなで答えよ",
			e.reading });
	}
	return questions;
}