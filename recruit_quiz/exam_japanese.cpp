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
		{ "必定", "ひつじょう", "必ずそうなると決まっていること" },
		{ "知己", "ちき", "自分をよく理解してくれる人、親しい友人" },
		{ "境内", "けいだい", "神社、寺院の敷地内" },
		{ "破綻", "はたん", "物事がうまくいかなくなること" },
		{ "拘泥", "こうでい", "ひとつの考え方や行動にこだわること" },
		{ "吟味", "ぎんみ", "物事を念入りに調べること" },
		{ "承る", "うけたまわる", "敬意を持って受ける、「受ける」、「聞く」の謙譲語" },
		{ "寸暇", "すんか", "ほんの少しの空き時間" },
		{ "弄ぶ", "もてあそぶ", "手であれこれいじる、好き勝手に扱う" },
		{ "灰汁", "あく", "食べ物を煮た時に出る渋みやえぐみの成分、独特の個性" },
		{ "潔い", "潔い", "思い切りがよい、道に反することがない" },
		{ "借款", "しゃっかん", "金銭を借りること、国同士の長期的な金銭の貸し借り" },
		{ "培う", "つちかう", "時間をかけて育てること" },
		{ "赴く", "おもむく", "ある場所、方向へ向かって行く" },
		{ "疾病", "しっぺい", "健康でない状態、病気" },
		{ "老舗", "しにせ", "先祖代々同じ商売をしている信用のある店" },
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

/*
*慣用句の意味を答える問題を作成する
*/
QuestionList CreateIdiomExam()
{
	static const struct {
		const char* idiom;		//慣用句
		const char* meaning;	//意味
	}data[] = {
		{ "気のおけない" , "気づかいがいらない" },
		{ "琴線に触れる" , "心から感動する" },
		{ "汚名をそそぐ" , "名誉を回復する" },
		{ "言質を取る" , "証拠となる言葉を聞き出す" },
		{ "二階から目薬" , "回りくどくて効果がない" },
		{ "禁じざるを得ない" , "禁止しなくてはならない" },
		{ "虎の尾を踏む" , "進んで危険なことをする" },
		{ "目から鼻へ抜ける" , "頭の回転が早くて行動が素早い" },
		{ "情けは人の為(ため)ならず" , "親切な行いは、いずれ自分のためになる" },
		{ "意表をつく" , "予想外なことをして驚かせる" },
		{ "青菜に塩" , "元気を失っている様(さま)" },
		{ "他山の石" , "人の失敗を、自分の行いを正す参考にする" },
		{ "口を糊(のり)する" , "余裕のない貧しい生活をする" },
		{ "身命を賭す" , "命を投げ出す覚悟で努力する" },
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++)
	{
		//間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int> answers = CreateWrongIndices(size(data), correctIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;

		//問題文を作成
		string s = "「" + string(data[correctIndex].idiom) + "」の意味として正しい番号を選べ";
		for (int j = 0; j < 3; j++)
		{
			s += "\n　" + to_string(j + 1) + ":" + data[answers[j]].meaning;
		}

		questions.push_back({ s, to_string(correctNo) });
	}
	return questions;

}

/*
* 同じ読みで意味の異なる漢字の問題を作成する
*/
QuestionList CreateHomophoneExam()
{
	const struct {
		const char* reading;	//読み
		struct {
			const char* kanji;		//漢字
			const char* meaning;	//意味
		}words[3];
	}data[] = {
		{ "じき", {
			{ "時期", "何かを行うとき、期間。" },
			{ "時機", "物事を行うのによい機会" }}},
		{ "そうぞう", {
			{ "想像", "実際には経験してない事柄を思い描くこと" },
			{ "創造", "新しいものを作り上げること" }}},
		{ "ほしょう", {
			{ "保証", "間違いがなく確かであると約束すること" },
			{ "保障", "権利や地位などが維持されるように保護し守ること" },
			{ "補償", "損失をおぎなってつぐなうこと" }}},
		{ "たいしょう", {
			{ "対象", "行為の目標となるもの" },
			{ "対称", "2つの図形や物事が互いにつり合っていること" },
			{ "対照", "見比べること、違いが際立つこと" }}},
		{ "あやまる", {
			{ "謝る", "失敗について許しを求める"},
			{ "誤る", "間違った判断をする" }}},
		{ "おさめる", {
			{ "納める", "金や物えお渡すべきところに渡す" },
			{ "治める", "乱れている物事を落ち着いて穏やかな状態にする" },
			{ "修める", "行いや人格を正しくする、学問や技芸などを学んで身につける" }}},
		{ "しょうかい", {
			{ "紹介", "未知の人や集団を引き合わせること"},
			{ "照会", "問い合わせて確かめること" }}},
		{ "いじょう", {
			{ "異常", "普段と異なるようす"},
			{ "異状", "姿や形が異なるようす" }}},
		{ "きょうこう", {
			{ "強行", "困難があると分かっていて無理に物事を行うこと"},
			{ "強硬", "自分の立場や主張を強い態度で押し通そうとすること" }}},
		{ "じったい", {
			{ "実体", "物事の本当の姿や形"},
			{ "実態", "物事の本当の状態" }}},
		{ "きょうい", {
			{ "脅威", "強い力や勢いによって恐れさせること"},
			{ "驚異", "驚くほど素晴らしいものごと" }}},
		{ "かいしん", {
			{ "会心", "期待どおりに物事が運んで満足すること"},
			{ "改心", "悪い考えや行いを反省し、良い心に改めること" }}},
		{ "しめる", {
			{ "占める", "場所、位置、地位などを自分のものにする" },
			{ "締める", "強く引っ張ったりひねったりして、緩みのないようにする" },
			{ "閉める", "物を動かしてすき間をふさぐ" }}},
		{ "つつしむ", {
			{ "謹む", "相手を敬い尊重する"},
			{ "慎む", "あやまちえお起こさないよう控えめに行動する" }}},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		const auto& e = data[indices[i]];

		//要素数を計算
		int count = 0;
		for (; count < size(e.words); count++) {
			if (!e.words[count].kanji) {
				break;
			}
		}

		//正しい番号を選択
		const int correctNo = uniform_int_distribution<>(1, count)(rd);

		//問題文を作成
		const vector<int> answer = CreateRandomIndices(count);
		string s = "「" + string(e.words[answer[correctNo - 1]].kanji) +
			"」の意味として正しい番号を選べ";
		for (int j = 0; j < count; j++) {
			s += "\n　" + to_string(j + 1) + ":" + e.words[answer[j]].meaning;
		}
		questions.push_back({ s, to_string(correctNo) });
	}
	return questions;
}

/*
* 対義語の問題を作成する
*/
QuestionList CreateAntonymExam()
{
	const struct {
		const char* kanji[2];
	} data[] = {
		{ "意図(いと)", "恣意(しい)" },
		{ "需要(じゅよう)", "供給(きょうきゅう)" },
		{ "故意(こい)", "過失(かしつ)" },
		{ "曖昧(あいまい)", "明瞭(めいりょう)" },
		{ "緊張(きんちょう)", "弛緩(しかん)" },
		{ "過疎(かそ)", "過密(かみつ)" },
		{ "栄転(えいてん)", "左遷(させん)" },
		{ "消費(しょうひ)", "生産(せいさん)" },
		{ "異端(いたん)", "正統(せいとう)" },
		{ "尊敬(そんけい)", "軽蔑(けいべつ)" },
		{ "警戒(けいかい)", "油断(ゆだん)" },
		{ "帰納(きのう)", "演繹(えんえき)" },
		{ "枯渇(こかつ)", "潤沢(じゅんたく)" },
		{ "乾燥(かんそう)", "湿潤(しつじゅん)" },
		{ "賞賛(しょうさん)", "罵倒(ばとう)" },
		{ "中枢(ちゅうすう)", "末端(まったん)" },
		{ "絶賛(ぜっさん)", "酷評(こくひょう)" },
		{ "創造(そうぞう)", "模倣(もほう)" },
		{ "過激(かげき)", "穏健(おんけん)" },
		{ "質素(しっそ)", "華美(かび)" },

	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++) {
		//間違った番号をランダムに選ぶ
		const int correcrIndex = indices[i];
		vector<int> answers = CreateWrongIndices(size(data), correcrIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 4)(rd);

		//問題文を作成
		const int object = uniform_int_distribution<>(0, 1)(rd);
		const int other = (object + 1) % 2;
		string s = "「" + string(data[correcrIndex].kanji[object]) +
			"」の対義語として正しい番号を選べ";
		for (int j = 0; j < 4; j++) {
			s += "\n　" + to_string(j + 1) + ":" + data[answers[j]].kanji[other];
		}
		questions.push_back({ s, to_string(correcrIndex) });
	}
	return questions;
}