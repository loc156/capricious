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
		std::cout << "(����ƥ����ļ����������ַ���&��ռλ����ʾ�ļ���ţ���������ֻ��һ�������硰www&.JPG��\n�����������ֻ��Զ������ļ���Ϊwww1.JPG��www10.JPG�ȵ��ļ�)\nrx: " << std::endl;
		std::cin >> rx;
		f << "rx: " << rx << std::endl;
		std::cout << "(��ʾ�����ļ��Ŀ�ʼ��ţ������������ġ�&��ռλ�������֣�)\nstart: " << std::endl;
		std::cin >> start;
		f << "start: " << start << std::endl;
		std::cout << "(��ʾ�����ļ��Ľ������)\nend: " << std::endl;
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