#include<iostream>
#include<fstream>
#include<string>
#include<format>
#include<vector>
#include<random>
#include<algorithm>
#include<Windows.h>
#include<cstdlib>
void draw(int iteration,std::string word) {
	switch (iteration) {
	case 1:
		std::cout << "\t\t\t\t\t\t O" << std::endl;
		break;
	case 2:
		std::cout << "\t\t\t\t\t\t O" << std::endl;
		std::cout << "\t\t\t\t\t\t/" << std::endl;
		break;
	case 3:
		std::cout << "\t\t\t\t\t\t O" << std::endl;
		std::cout << "\t\t\t\t\t\t/";
		std::cout << " \\" << std::endl;
		break;
	case 4:
		std::cout << "\t\t\t\t\t\t O" << std::endl;
		std::cout << "\t\t\t\t\t\t/";
		std::cout << " \\" << std::endl;
		std::cout << "\t\t\t\t\t\t |" << std::endl;
		break;
	case 5:
		std::cout << "\t\t\t\t\t\t O" << std::endl;
		std::cout << "\t\t\t\t\t\t/";
		std::cout << " \\" << std::endl;
		std::cout << "\t\t\t\t\t\t |" << std::endl;
		std::cout << "\t\t\t\t\t\t/" << std::endl;
		break;
	case 6:
		std::cout << "\t\t\t\t\t\t O" << std::endl;
		std::cout << "\t\t\t\t\t\t/";
		std::cout << " \\" << std::endl;
		std::cout << "\t\t\t\t\t\t |" << std::endl;
		std::cout << "\t\t\t\t\t\t/";
		std::cout << " \\" << std::endl;
		std::cout << std::endl;
		std::cout << "ВЫ ПРОИГРАЛИ\n\n\n\n\n";
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
	std::string topic_str;
	switch (topic_number) {
	case 1:
		topic_str = "1. Животные ";
		break;
	case 2:
		topic_str = "2. Фрукты и овощи ";
		break;
	case 3:
		topic_str = "3. Города ";
		break;
	case 4:
		topic_str = "4. Профессии ";
		break;
	default:
		break;

	}
	try {
		if (topic_number < 1 || topic_number > 4 || std::cin.fail()) {
			throw std::logic_error("Такая тема отсутствует");
		}
	}
	catch (std::logic_error& err) {
		std::cout << err.what() << std::endl;
		return EXIT_FAILURE;
	}
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
	system("cls");
	word = all_word[index];
	std::string check_word(word.size(), '_');
	std::string bukva;
	int iteration{ 0 };
	std::cout << std::format("Тема: {} ", topic_str) << std::endl;
	std::cout << std::format("Слово состоит из {} букв ", check_word.size());
	for (size_t i = 0; i < check_word.size(); i++) {
		std::cout << std::format("{} ", check_word[i]);
	}
	std::cout << std::endl;
	while (iteration < 6) {
		std::cin >> bukva;
		bool fl{ false };
		if (bukva.size() == 1) {
			for (size_t i = 0; i < word.size(); i++) {
				if (word[i] == bukva[0]) {
					fl = true;
					check_word[i] = word[i];
				}
			}
		}
		else {
			try{
				if (bukva.size() != word.size()) {
					throw std::logic_error("неверная длинна слова");
				}
				for (size_t i = 0; i < word.size(); i++) {
					if (word[i] == bukva[i]) {
						fl = true;
						check_word[i] = word[i];
					}
				}
			}
			catch (std::logic_error& err) {
				std::cout << err.what() << std::endl;
			}
		}

		if (!fl) {
			iteration += 1;
		}
		system("cls");
		std::cout << std::format("Тема: {} ", topic_str) << std::endl;
		std::cout << std::format("Слово состоит из {} букв ", check_word.size());
		std::cout << std::format("угадано {}/{}", check_word.size() -
			std::count(check_word.begin(), check_word.end(), '_'), check_word.size()) << std::endl;
		if (check_word.find("_")==std::string::npos) {
			for (size_t i = 0; i < check_word.size(); i++) {
				std::cout << std::format("{} ", check_word[i]);
			}
			std::cout << std::endl;
			std::cout << "ВЫ ВЫИГРАЛИ!!!!!\n\n\n\n\n";
			break;
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