#include<iostream>
#include<fstream>
#include<string>
#include<format>
#include<vector>
#include<random>
#include<Windows.h>
void draw(int iteration,std::string word) {
	switch (iteration) {
	case 1:
		std::cout << "\t O" << std::endl;
		break;
	case 2:
		std::cout << "\t O" << std::endl;
		std::cout << "\t/" << std::endl;
		break;
	case 3:
		std::cout << "\t O" << std::endl;
		std::cout << "\t/";
		std::cout << " \\" << std::endl;
		break;
	case 4:
		std::cout << "\t O" << std::endl;
		std::cout << "\t/";
		std::cout << " \\" << std::endl;
		std::cout << "\t |" << std::endl;
		break;
	case 5:
		std::cout << "\t O" << std::endl;
		std::cout << "\t/";
		std::cout << " \\" << std::endl;
		std::cout << "\t |" << std::endl;
		std::cout << "\t/" << std::endl;
		break;
	case 6:
		std::cout << "\t O" << std::endl;
		std::cout << "\t/";
		std::cout << " \\" << std::endl;
		std::cout << "\t |" << std::endl;
		std::cout << "\t/";
		std::cout << " \\" << std::endl;
		std::cout << std::endl;
		std::cout << "GAME OVER";
		std::cout << std::format("Слово было : {} ", word) << std::endl;
		break;
	default:
		break;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int topic_number;
	std::vector<std::string> all_word;
	std::cout << "Выберите тему: " << std::endl; 
	std::cout << "1. Животные " << std::endl << "2. Фрукты и овощи " << std::endl
		<< "3. Города " << std::endl << "4. Профессии " << std::endl;
	std::cout << "Введите номер темы " << std::endl;
	std::cin >> topic_number;
	std::ifstream file(std::format("word{}.txt",topic_number));
	if (!file.is_open()) {
		std::cout << "Файл не найден" << std::endl;
	}
	else {
		std::string str;
		while (file >> str) {
			all_word.push_back(str);
		}
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(0,all_word.size()-1);
	size_t index = dist(gen);
	std::string word;
	std::cout << "Угадывайте)" << std::endl;
	word = all_word[index];
	std::string check_word(word.size(), '_');
	char bukva;
	int iteration{ 0 }, true_bk{ 0 };
	while (iteration < 6) {
		std::cin >> bukva;
		bool fl{ false };
		for (size_t i = 0; i < word.size(); i++) {
			if (word[i] == bukva) {
				fl = true;
				check_word[i] = word[i];
			}
		}
		if (!fl) {
			iteration += 1;
		}
		else {
			true_bk += 1;
		}
		if (check_word.find("_")==std::string::npos) {
			for (size_t i = 0; i < check_word.size(); i++) {
				std::cout << std::format("{} ", check_word[i]);
			}
			std::cout << std::endl;
			std::cout << "YOU WIN!!!!!";
		}
		else {
			for (size_t i = 0; i < check_word.size(); i++) {
				std::cout << std::format("{} ", check_word[i]);
			}
			std::cout << std::endl;
			draw(iteration,word);
		}
	}



	return EXIT_SUCCESS;
}