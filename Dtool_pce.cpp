#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

std::fstream f;
std::string rx;
int start = 0;
int end = 0;
std::vector<std::string> vf;

std::vector<std::string> fsplit;

void process(const std::string& filename) {

	f.open(filename, std::ios::binary | std::ios::in);
	if (!f.is_open()) {
		std::cerr << "Error: " << filename << std::endl;
		return;
	}
	std::vector<char> buffer((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
	for (char& c : buffer) {
		c = ~c;
	}
	f.close();

	f.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!f.is_open()) {
		std::cerr << "Error: " << filename << std::endl;
		return;	
	}
	f.write(buffer.data(), buffer.size());
	f.close();
}

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
	std::vector<std::string> result;
	std::regex re(delimiter);
	std::sregex_token_iterator iter(s.begin(), s.end(), re, -1);
	std::sregex_token_iterator end;
	while (iter != end) {
		result.push_back(iter->str());
		iter++;
	}
	return result;
}

int main() {

	f.open("D.config", std::ios::in);

	if (!f.is_open()) {
		f.open("D.config", std::ios::out | std::ios::trunc);
		std::cout << "(用于匹配的文件名，并用字符“&”占位符表示文件编号（必须有且只有一个），如“www&.JPG”\n配合下面的数字会自动搜索文件名为www1.JPG，www10.JPG等等文件)\nrx: " << std::endl;
		std::cin >> rx;
		f << "rx: " << rx << std::endl;
		std::cout << "(表示遍历文件的开始序号（既上文所述的“&”占位符的数字）)\nstart: " << std::endl;
		std::cin >> start;
		f << "start: " << start << std::endl;
		std::cout << "(表示遍历文件的结束序号)\nend: " << std::endl;
		std::cin >> end;
		f << "end: " << end << std::endl;
		f.close();
	}
	while (!f.eof()) {
		std::string ts;
		f >> ts;
		vf.push_back(ts);
	}
	f.close();
	if (vf.empty()) {
		std::cerr << "Error: D.config is empty or incomplete." << std::endl;
		return 1;
	}
	for (int i = 0; i < vf.size(); i++) {
		if (vf[i] == "rx:" && (i + 1 < vf.size()))
			rx = vf[++i];
		if (vf[i] == "start:" && (i + 1 < vf.size()))
			start = std::stoi(vf[++i]);
		if (vf[i] == "end:" && (i + 1 < vf.size()))
			end = std::stoi(vf[++i]);
	}

	fsplit = split(rx, "[&]");
	for (int i = start; i <= end; i++) {
		process(fsplit[0] + std::to_string(i) + fsplit[1]);
	}
	std::cout << "Done." << std::endl;
	system("pause");
}