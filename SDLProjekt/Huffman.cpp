#include"Huffman.h"

HUFFMAN::HUFFMAN()
{
	freq.resize(256);
}

void HUFFMAN::wypiszWynik(std::shared_ptr<Leaf> korzen, std::string kod)
{
	if (korzen)
	{
		if (!korzen->getLeftChild())
		{
			huffmanCode[korzen->getValue()] = kod;
			std::cout << (int)korzen->getValue() << " " << kod << std::endl;
		}
		else
		{
			wypiszWynik(korzen->getLeftChild(), kod + "0");
			wypiszWynik(korzen->getRightChild(), kod + "1");
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

void HUFFMAN::zliczaniePowtorzen(std::vector<SDL_Color>& buffor)
{
	size_t buff_size=buffor.size();
	for (unsigned int i = 0; i < buff_size; ++i)
	{
		++freq[buffor[i].r];
		++freq[buffor[i].g];
		++freq[buffor[i].b];
	}

	for (int i = 0; i < 256; i++)
	{
		std::cout << "Ilosc wystapien " << i << " :" << freq[i] << std::endl;
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
	uint16_t pack = 0;
	while (i < 256)
	{
		if (huffmanCode[i] == "")
		{
			pack = 0;
			out.writeBin(reinterpret_cast<char*>(&pack), sizeof(pack));
		}
		else
		{
			huffmanCode[i] += "1";
			pack = std::stoi(huffmanCode[i], nullptr, 2);
			out.writeBin(reinterpret_cast<char*>(&pack), sizeof(pack));
		}
		
		++i;
	}
}

void HUFFMAN::InsertIntoQueue(std::shared_ptr<Leaf> x)
{
	prioriQueue.push(x);
}

void HUFFMAN::huffmanCompress(const std::vector<SDL_Color>& buffor,OurFormat &out)
{
	size_t sizeBuff = buffor.size();
	size_t i = 0;
	int freeSpace = 8;
	uint8_t pack = 0;
	while (i < sizeBuff)
	{
		huffmanCode[buffor[i].r] = ;
		++i;
	}
	std::cout << "Pause";
}

void HUFFMAN::wypelnijSterte()
{
	for (int i = 0; i < 256; i++)
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

}
HUFFMAN::~HUFFMAN()
{
}
