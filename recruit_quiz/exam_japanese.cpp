#include "exam_japanese.h"
#include "utility.h"
#include "random"
using namespace std;

/*
* �����̓ǂݎ������쐬����
*/
QuestionList CreateKanjiExam()
{
	static const struct {
		const char* kanji;		//����
		const char* reading;	//�ǂ�
		const char* meaning;	//�Ӗ�
	} data[] = {
		{ "�s��", "������", "�l�������W�܂��ĕ�炷�Ƃ���A��" },
		{ "���", "�Ȃ���", "(�����Ƌ���)��ӂ���������" },
		{ "���E", "��������", "���������̌��ʁA�����Ȃ��Ȃ邱��" },
		{ "�}��", "�͂�ꂢ", "�{��}�\�̂͂��߂ɁA�g������񑩎����ӏ������ɂ�������" },
		{ "���", "�₭���傤", "�񑩂��Ă��߂邱�ƁA�_��" },
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	//���̎�ނ�I��
	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0) {
		//�����̓ǂ݂𓚂�����
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"�u" + string(e.kanji) + "�v�̓ǂ݂��Ђ炪�Ȃœ�����",
				e.reading });
		}
	}
	else {
		//�������n��𓚂�����
		for (int i = 0; i < quizCount; i++) {
			//�Ԉ�����ԍ��������_���ɑI��
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//��蕶���쐬
			string s = "�u" + string(data[correctIndex].meaning) +
				"�v���Ӗ�����n��̔ԍ���I��";
			for (int j = 0; j < 3; j++) {
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].kanji;
			}

			questions.push_back({ s, to_string(correctNo) });
		}
	}//if type
	return questions;
}