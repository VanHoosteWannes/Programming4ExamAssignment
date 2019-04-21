#include "MiniginPCH.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(const std::string& readfile)
	:m_Exists(false)
	,m_Reader{std::ifstream(readfile.c_str(), std::ios::in | std::ios::binary)}
{
	if (m_Reader.is_open()) m_Exists = true;
	else
	{

		std::cout << "[READ] Failed to open file: " << readfile << std::endl;
	}
}

std::string BinaryReader::ReadString()
{
	std::stringstream ss;

	if (m_Exists)
	{
		int stringLength = (int)Read<char>();

		for (int i{ 0 }; i < stringLength; ++i)
		{
			ss << Read<char>();
		}
	}
	return ss.str();
	//std::string s;
	//if (m_Exists)
	//{
	//	int length = (int)Read<char>();
	//	s.resize(length);
	//	for (int i{0}; i < length; ++i)
	//	{
	//		s[i] = Read<char>();
	//	}
	//	
	//}
	//return s;
	/*std::string s;
	std::getline(m_Reader, s, '\0');
	return s;*/

}

void BinaryReader::CloseFile()
{
	m_Reader.close();
}

void BinaryReader::ReadHex(std::vector<std::string>& hexVector)
{
	int hex;
	if (m_Exists)
	{
		int stringLength = (int)Read<unsigned char>();
		int number3, number4;
		std::string HexSize;
		number3 = stringLength / 16;
		number4 = stringLength % 16;
		if (number3 < 10)
			HexSize += std::to_string(number4);
		else if (number3 == 10) HexSize += "A";
		else if (number3 == 11) HexSize += "B";
		else if (number3 == 12) HexSize += "C";
		else if (number3 == 13) HexSize += "D";
		else if (number3 == 14) HexSize += "E";
		else if (number3 == 15) HexSize += "F";
		if (number4 < 10)
			HexSize += std::to_string(number4);
		else if (number4 == 10) HexSize += "A";
		else if (number4 == 11) HexSize += "B";
		else if (number4 == 12) HexSize += "C";
		else if (number4 == 13) HexSize += "D";
		else if (number4 == 14) HexSize += "E";
		else if (number4 == 15) HexSize += "F";
		hexVector.push_back(HexSize);

		for (int i{ 0 }; i < stringLength; ++i)
		{
			std::string sHex;
			int number1, number2;
			hex = Read<char>();
			number1 = hex / 16;
			number2 = hex % 16;
			if (number1 < 10)
				sHex += std::to_string(number1);
			else if (number1 == 10) sHex += "A";
			else if (number1 == 11) sHex += "B";
			else if (number1 == 12) sHex += "C";
			else if (number1 == 13) sHex += "D";
			else if (number1 == 14) sHex += "E";
			else if (number1 == 15) sHex += "F";
			if (number2 < 10)
				sHex += std::to_string(number2);
			else if (number2 == 10) sHex += "A";
			else if (number2 == 11) sHex += "B";
			else if (number2 == 12) sHex += "C";
			else if (number2 == 13) sHex += "D";
			else if (number2 == 14) sHex += "E";
			else if (number2 == 15) sHex += "F";
			hexVector.push_back(sHex);
		}
	}
}



