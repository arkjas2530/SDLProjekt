#include"Huffman.h"

HUFFMAN::HUFFMAN()
	:freeSpace(7),pack(0),canISave(false),min(0),saved(0),depack(0)
{
	freq.resize(253);
}

void HUFFMAN::createCodes(std::shared_ptr<Leaf> korzen, std::string kod)
{
	if (korzen)
	{
		if (!korzen->getLeftChild())
		{

			huffmanCode[korzen->getValue()] = kod;
			if (kod.size() > 16)
			{
				//
			}
		}
		else
		{
			createCodes(korzen->getLeftChild(), kod + "0");
			createCodes(korzen->getRightChild(), kod + "1");
		}
	}
}

void HUFFMAN::zwolnijPamiec(std::shared_ptr<Leaf> korzen)// zwalnia pamiec (drzewo)
{
	if (korzen->getLeftChild())
		zwolnijPamiec(korzen->getLeftChild());
	if (korzen->getRightChild())
		zwolnijPamiec(korzen->getRightChild());
	korzen.reset();
}

void HUFFMAN::zliczaniePowtorzen(const std::vector<SDL_Color>& buffor)
{
	size_t buff_size=buffor.size();
	for (unsigned int i = 0; i < buff_size; ++i)
	{
		++freq[buffor[i].r];
		++freq[buffor[i].g];
		++freq[buffor[i].b];
	}
}

std::shared_ptr<Leaf> HUFFMAN::getElement()
{
	std::shared_ptr<Leaf> element = prioriQueue.top();
	prioriQueue.pop();

	return element;
}

void HUFFMAN::writeCodes(OurFormat& out)
{
	unsigned int i = 0;
	unsigned int size = 0;
	std::string temp;
	uint16_t pack = 0;
	while (i < 253)
	{
		if (huffmanCode[i] == "")
		{
			pack = 0;
			out.writeBin(RCAST<char*>(&pack), sizeof(pack));
		}
		else
		{
			temp = "1";
			temp += huffmanCode[i];
			pack = std::stoi(temp, nullptr, 2);
			out.writeBin(RCAST<char*>(&pack), sizeof(pack));
		}
		++i;
	}
}

void HUFFMAN::packing(Uint8 color)
{
	size_t size = huffmanCode[color].size();
	bool tmp = false;
	for (size_t j = 0;j < size;++j)
	{
		if (huffmanCode[color][j] == '1')
			tmp = true;
		else
			tmp = false;
		pack +=  tmp << freeSpace;
		--freeSpace;
		if (freeSpace < 0)
		{
			result.push_back(pack);
			pack = 0;
			freeSpace = 7;
		}
	}
}

void HUFFMAN::depacking(uint8_t coded)
{
	//Pamiêtaj o sztucznej jedynce musisz ja dodaæ na koñcu !
	bool tmp = false;

	for (int j = 0;j < 8;++j) 
	{
		if (saved >= min)
		{
			// dodawanie jedynki 
			depack >>= 16 - saved;
			depack += 1 << saved;

			auto it = codeMap.find(depack);
			if (it != codeMap.end())
			{
				result.push_back(it->second);
				depack = 0;
				saved = 0;
			}
			else
			{
				depack <<= 16 - saved;
 
			}
		}

			if (((coded >> freeSpace)&1) == 1)
				tmp = true;
			else
				tmp = false;
			depack += (tmp << (15 - saved));
			saved++;
			freeSpace--;
	}
	freeSpace = 7;
}

void HUFFMAN::InsertIntoQueue(std::shared_ptr<Leaf> x)
{
	prioriQueue.push(x);
}

void HUFFMAN::huffmanCompress( std::vector<SDL_Color>& buffor,char colorchoice)
{
	size_t sizeBuff = buffor.size();
	int j = 0;

	if (colorchoice == '2')
	{
		int BW;
		while (j < sizeBuff)
		{
			BW = (buffor[j].r + buffor[j].g + buffor[j].b) / 3;
			buffor[j].r = BW;
			buffor[j].g = BW;
			buffor[j].b = BW;
			++j;
		}
	}

	zliczaniePowtorzen(buffor);
	makePile();
	std::shared_ptr<Leaf> korzen = TreeGenerating();
	createCodes(korzen, "");

	result.reserve(sizeBuff * 3);
	size_t i = 0;

	while (i < sizeBuff)
	{
		packing(buffor[i].r);
		packing(buffor[i].g);
		packing(buffor[i].b);
		++i;
	}
	if (freeSpace != 7)
	{
		result.push_back(pack);
	}
	canISave = true; //czy mo¿na wywo³aæ funkcje makeCompressedFile
}

bool HUFFMAN::makeCompressedFile(OurFormat & out,SDL_Surface *headerInfo,int size)
{
	if (!canISave)
	{
		std::cout << "No compressed image, first use huffmanCompress" << std::endl;
		return false;
	}
	outHeader header = out.generateHeader(headerInfo, size, 2);   //stworzenie naglowka
	out.writeBin(RCAST<char*>(&header), sizeof(header)); //wpisanie go do pliku
	min = huffmanCode[0].size();
	for (int i = 1;i < 253;++i)
	{
		if (huffmanCode[i].size() < min)
			min = huffmanCode[i].size();
	}
	uint8_t saveMin = static_cast<uint8_t>(min);
	out.writeBin(RCAST<char*>(&saveMin), sizeof(uint8_t));
	writeCodes(out);
	out.writeBin(RCAST<char*>(&result[0]), static_cast<int>(result.size() * sizeof(char)));
	
	return true;
}

std::vector<uint8_t> HUFFMAN::huffmanDecompress(const unsigned int size, std::ifstream &in)
{
	getCodeMap(in);
	std::vector<uint8_t> buffor;
	buffor.resize(size);

	result.reserve(size);

	in.read(RCAST<char*>(&buffor[0]), buffor.size());

	unsigned int i = 0;

	size_t buffSize = buffor.size();
	while (i < buffSize)
	{
		depacking(buffor[i]);
		++i;
	}
	return std::move(result);
}

void HUFFMAN::getCodeMap(std::ifstream & in)
{
	std::vector<uint16_t> map;
	map.resize(253);
	uint8_t tmpMin = 0;
	in.read(RCAST<char*>(&tmpMin), sizeof(uint8_t));
	min = tmpMin;
	in.read(RCAST<char*>(&map[0]), map.size() * sizeof(uint16_t));

	for (int i = 0;i < 253;++i)
	{
		codeMap[map[i]] = i;
	}
}

void HUFFMAN::makePile()
{
	for (int i = 0; i < 253; i++)
	{
		if (freq[i] != 0)
		{
			std::shared_ptr<Leaf> leaf = std::make_shared<Leaf>(i, freq[i]);
			prioriQueue.push(leaf);
		}
		
	}
}

std::shared_ptr<Leaf> HUFFMAN::TreeGenerating()
{
	if (prioriQueue.size()>1)
	{
			while (prioriQueue.size() > 1)
			{
				std::shared_ptr<Leaf> nRoot = std::make_shared<Leaf>(getElement(),getElement());
				InsertIntoQueue(nRoot);
			}
			return getElement();
	}
	else if (prioriQueue.size() == 1)
	{
		std::shared_ptr<Leaf> Root = std::make_shared<Leaf>(getElement());
		return Root;
	}
	else
	{
		std::cerr << "Queue is empty!!" << std::endl;
		getchar(); getchar();
		exit(-1);
	}
		

}
HUFFMAN::~HUFFMAN()
{
}
