// JLibrary
// FileManager.cpp
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-05-15 by Justyn Durnford
// Source file for the FileManager class.

#include "Buffer.hpp"
#include "FileManager.hpp"

#include <cstddef>
using std::size_t;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <ios>
using std::ios_base;

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string;
using std::string_view;
using std::getline;

#include <utility>
using std::move;

#include <vector>
using std::vector;

import Array;
using jlib::Array;

#pragma warning(push)
#pragma warning(disable: 4244) // Disable warning for argument type conversion.

namespace jlib
{
	bool try_getline(ifstream& fin, string& str)
	{
		getline(fin, str);
		return fin.good();
	}

	FileManager::FileManager(const string& path)
	{
		_path = path;
		_fin.open(_path);

		if (!_fin.is_open())
			throw runtime_error(string("FileManager::FileManager(const string& path) threw an exception: Could not find file: ") + _path);
	}

	void FileManager::read(void* buffer, size_t count)
	{
		if (!_fin.is_open())
			throw runtime_error(string("FileManager::read(void* buffer, size_t count) threw an exception: File cannot be read."));

		_fin.read(reinterpret_cast<char*>(buffer), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::read(void* buffer, size_t count) threw an exception: File cannot be read."));
	}

	void FileManager::read(Buffer& buffer, size_t count)
	{
		if (!_fin.is_open())
			throw runtime_error(string("FileManager::read(Buffer& buffer, size_t count) threw an exception: File cannot be read."));

		_fin.read(reinterpret_cast<char*>(buffer.pointer()), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::read(Buffer& buffer, size_t count) threw an exception: File cannot be read."));
	}

	void FileManager::read(string& str, size_t count)
	{
		str.resize(count);

		if (!_fin.is_open())
			throw runtime_error(string("FileManager::read(string& str, size_t count) threw an exception: File cannot be read."));

		_fin.read(str.data(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::read(string& str, size_t count) threw an exception: File cannot be read."));
	}

	void FileManager::read(vector<char>& vec, size_t count)
	{
		vec.resize(count);

		if (!_fin.is_open())
			throw runtime_error(string("FileManager::read(vector<char>& vec, size_t count) threw an exception: File cannot be read."));

		_fin.read(vec.data(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::read(vector<char>& vec, size_t count) threw an exception: File cannot be read."));
	}

	void FileManager::read(Array<char>& arr, size_t count)
	{
		arr.resize(count);

		if (!_fin.is_open())
			throw runtime_error(string("FileManager::read(Array<char>& arr, size_t count) threw an exception: File cannot be read."));

		_fin.read(arr.data(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::read(Array<char>& arr, size_t count) threw an exception: File cannot be read."));
	}

	string FileManager::read()
	{
		string str;

		if (!_fin.is_open())
			throw runtime_error(string("FileManager::read() threw an exception: File cannot be read."));

		_fin >> str;

		if (!_fin.good())
			throw runtime_error(string("FileManager::read() threw an exception: File cannot be read."));

		return str;
	}

	string FileManager::readLine()
	{
		string line;

		if (!_fin.is_open())
			throw runtime_error(string("FileManager::readLine() threw an exception: File cannot be read."));

		if (!try_getline(_fin, line))
			throw runtime_error(string("FileManager::readLine() threw an exception."));

		return line;
	}

	vector<string> FileManager::readLines()
	{
		string line;
		vector<string> lines;

		_fin.seekg(0);

		while (try_getline(_fin, line))
			lines.push_back(line);

		return lines;
	}

	void FileManager::write(const char* buffer, size_t count)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(const char* buffer, size_t count) threw an exception: File cannot be written to."));

		_fout.write(buffer, count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(const char* buffer, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::write(const char* begin, const char* end)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(const char* begin, const char* end) threw an exception: File cannot be written to."));

		_fout.write(begin, end - begin - 1);
		_fout << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(const char* begin, const char* end) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::write(const string& str)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(const string& str) threw an exception: File cannot be written to."));

		_fout << str;

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(const string& str) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::write(const string& str, size_t count)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(const string& str, size_t count) threw an exception: File cannot be written to."));

		_fout.write(str.c_str(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(const string& str, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::write(const vector<char>& vec, size_t count)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(const vector<char>& vec, size_t count) threw an exception: File cannot be written to."));

		_fout.write(vec.data(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(const vector<char>& vec, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::write(const Array<char>& arr, size_t count)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(const Array<char>& arr, size_t count) threw an exception: File cannot be written to."));

		_fout.write(arr.data(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(const Array<char>& arr, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::write(string_view view)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::write(string_view view) threw an exception: File cannot be written to."));

		_fout.write(view.data(), view.size());

		if (!_fin.good())
			throw runtime_error(string("FileManager::write(string_view view) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::writeLine(const char* buffer, size_t count)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::writeLine(const char* buffer, size_t count) threw an exception: File cannot be written to."));

		_fout.write(buffer, count);
		_fout << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::writeLine(const char* buffer, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::writeLine(const string& line)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::writeLine(const string& line) threw an exception: File cannot be written to."));

		_fout << line << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::writeLine(const string& line) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::writeLines(const string* lines, size_t count)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::writeLines(const string* lines, size_t count) threw an exception: File cannot be written to."));

		for (size_t i = 0; i < count; ++i)
			_fout << lines[i] << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::writeLines(const string* lines, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::writeLines(const vector<string>& lines)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::writeLines(const vector<string>& lines) threw an exception: File cannot be written to."));

		for (const string& str : lines)
			_fout << str << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::writeLines(const vector<string>& lines) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::writeLines(const Array<string>& lines)
	{
		_fin.close();
		_fout.open(_path);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::writeLines(const Array<string>& lines) threw an exception: File cannot be written to."));

		for (const string& str : lines)
			_fout << str << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::writeLines(const Array<string>& lines) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::insertLine(const string& line, size_t line_index)
	{
		vector<string> lines = readLines();
		lines.insert(lines.begin() + line_index, line);
		writeLines(lines);
	}

	void FileManager::insertLines(const vector<string>& lines, size_t line_index)
	{
		vector<string> file_lines = readLines();

		for (size_t i = 0; i < lines.size(); ++i)
			file_lines.insert(file_lines.begin() + line_index + i, lines[i]);

		writeLines(file_lines);
	}

	void FileManager::append(const char* buffer, size_t count)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::append(const char* buffer, size_t count) threw an exception: File cannot be written to."));

		_fout.write(buffer, count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::append(const char* buffer, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::append(const string& str)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::append(const string& str) threw an exception: File cannot be written to."));

		_fout << str;

		if (!_fin.good())
			throw runtime_error(string("FileManager::append(const string& str) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::append(const string& str, size_t count)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::append(const string& str, size_t count) threw an exception: File cannot be written to."));

		_fout.write(str.c_str(), count);

		if (!_fin.good())
			throw runtime_error(string("FileManager::append(const string& str, size_t count) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::append(const vector<char>& vec)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::append(const vector<char>& vec) threw an exception: File cannot be written to."));

		_fout.write(vec.data(), vec.size());

		if (!_fin.good())
			throw runtime_error(string("FileManager::append(const vector<char>& vec) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::append(const Array<char>& arr)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::append(const Array<char>& arr) threw an exception: File cannot be written to."));

		_fout.write(arr.data(), arr.size());

		if (!_fin.good())
			throw runtime_error(string("FileManager::append(const Array<char>& arr) threw an exception: File cannot be written to."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::appendLine(const string& line)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::appendLine(const string& line) threw an exception: File cannot be written to."));

		_fout << line << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::appendLine(const string& line) threw an exception: File cannot be read."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::appendLines(const string* lines, size_t count)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::appendLines(const string* lines, size_t count) threw an exception: File cannot be written to."));

		for (size_t i = 0; i < count; ++i)
			_fout << lines[i] << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::appendLines(const string* lines, size_t count) threw an exception: File cannot be read."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::appendLines(const Array<string>& lines)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::appendLines(const Array<string>& lines) threw an exception: File cannot be written to."));

		for (const string& str : lines)
			_fout << str << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::appendLines(const Array<string>& lines) threw an exception: File cannot be read."));

		_fout.close();
		_fin.open(_path);
	}

	void FileManager::appendLines(const vector<string>& lines)
	{
		_fin.close();
		_fout.open(_path, ios_base::app);

		if (!_fout.is_open())
			throw runtime_error(string("FileManager::appendLines(const vector<string>& lines) threw an exception: File cannot be written to."));

		for (const string& str : lines)
			_fout << str << '\n';

		if (!_fin.good())
			throw runtime_error(string("FileManager::appendLines(const vector<string>& lines) threw an exception: File cannot be read."));

		_fout.close();
		_fin.open(_path);
	}

	bool FileManager::eof() const
	{
		return _fin.eof();
	}

	void FileManager::open(const string path)
	{
		_path = path;
		_fin.open(_path);
	}

	void FileManager::close()
	{
		_fin.close();
	}

	bool FileManager::isOpen() const
	{
		return _fin.is_open();
	}

	bool FileManager::isClosed() const
	{
		return !_fin.is_open();
	}
}

#pragma warning(pop)