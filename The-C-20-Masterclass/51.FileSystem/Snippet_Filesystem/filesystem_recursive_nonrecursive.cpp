#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

namespace fs = std::filesystem;

int main() {
	fs::create_directories("data/a/b.txt");
	std::vector<fs::path> paths = {
		"data/a/b.txt/1.txt",
		"data/a/b.txt/2.txt",
		"data/a/3.dat",
		"data/4.dat"
	};
	for (const auto& filepath : paths)
	{
		// � C++17 ����������� fstream ��������� ��� string, ��� � wstring,
		//  ��� �������� ������������������ ��������������� ��� �� path
		std::ofstream(filepath.native()) << "test";
	}
	
	{	fs::recursive_directory_iterator begin("data");
		fs::recursive_directory_iterator end;
		// �������� ������ ������������ � ������� ��������� copy_if
		std::vector<fs::path> subdirs;
		std::copy_if(begin, end, std::back_inserter(subdirs), [](const fs::path& path) {
			return fs::is_directory(path);
					 });
					 // ������� ������ ������������ � cout.
		std::cout << "-- subdirs --" << std::endl;
		std::copy(subdirs.begin(), subdirs.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));
	}

	{
		fs::recursive_directory_iterator begin("data");
		fs::recursive_directory_iterator end;

		// �������� ������ ������ .txt � ������� ��������� copy_if
		std::vector<fs::path> txtFiles;
		std::copy_if(begin, end, std::back_inserter(txtFiles), [](const fs::path& path) {
			return fs::is_regular_file(path) && (path.extension() == ".txt");
					 });
					 // ������� ������ ������ � cout.
		std::cout << "-- txt files --" << std::endl;
		std::copy(txtFiles.begin(), txtFiles.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));
	}
}
