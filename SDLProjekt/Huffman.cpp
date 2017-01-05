#include"Huffman.h"

HUFFMAN::HUFFMAN()
{
	freq.resize(256);
}

/*
void HUFFMAN::wypiszWynik(std::shared_ptr<Leaf> korzen, std::vector<bool> kod)
{
	if (!korzen->getLeftChild())
	{
		huffmanCode[korzen->getValue()] = kod;
		std::cout << (int)korzen->getValue() << " ";
		for (auto &x : kod)
		{
			std::cout << x;
		}
		std::cout << std::endl;
	}
	else
	{
		kod.push_back(0);
		wypiszWynik(korzen->getLeftChild(), kod);
		kod.pop_back();

		kod.push_back(1);
		wypiszWynik(korzen->getRightChild(), kod);
		kod.pop_back();
	}
}
*/

void HUFFMAN::wypiszWynik(std::shared_ptr<Leaf> korzen, std::string kod)
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

Leaf HUFFMAN::getElement()
{
	Leaf element = prioriQueue.top();
	prioriQueue.pop();

	return element;
}

void HUFFMAN::writeMap(OurFormat& out)
{
	unsigned int i = 0;
	uint16_t pack = 0;
	while (i < 256)
	{
		pack = std::stoi(huffmanCode[i],nullptr,2);
		out.writeBin(reinterpret_cast<char*>(&pack), sizeof(pack));
		++i;
	}
}

void HUFFMAN::InsertIntoQueue(const Leaf &x)
{
	prioriQueue.push(x);
}

void HUFFMAN::huffmanCompress(const std::vector<SDL_Color>& buffor,OurFormat &out)
{
	size_t sizeBuff = buffor.size();
	size_t i = 0;
	while (i < sizeBuff)
	{
		;
	}
	std::cout << "Pause";
}

void HUFFMAN::wypelnijSterte()
{
	unsigned char liczba;	// kolor
	unsigned int ilosc;		// powtorzenie koloru

	for (int i = 0; i < 256; i++)
	{
		liczba = i;
		ilosc = freq[i];
		if (ilosc != 0)
		{
			Leaf leaf(liczba, ilosc);
			prioriQueue.push(leaf);
		}
		
	}
}

std::shared_ptr<Leaf> HUFFMAN::TreeGenerating()
{
	std::shared_ptr<Leaf> lastLeft = nullptr; // addr of last left child
	std::shared_ptr<Leaf> lastRight = nullptr; // addr of last right child

	while (!prioriQueue.empty())
	{
		std::shared_ptr<Leaf> rightChild = std::make_shared<Leaf>();
		std::shared_ptr<Leaf> leftChild = std::make_shared<Leaf>();
		std::shared_ptr<Leaf> nRoot = std::make_shared<Leaf>();

		if (prioriQueue.size() == 1) // getting last element from prioriQueue, this if end algorithm
		{
			*nRoot = getElement();
			nRoot->setLeftChild(lastLeft);
			nRoot->setRightChild(lastRight);
			if (lastLeft == nullptr && lastRight == nullptr)
			{
				nRoot->setFreq(nRoot->getFreq()); // HERE IS A PROBLEM !!
			}
			else if (lastRight == nullptr)
			{
				nRoot->setFreq(lastLeft->getFreq()); // HERE IS A PROBLEM !!
			}
			else if (lastLeft == nullptr && lastRight == nullptr)
			{
				nRoot->setFreq(lastRight->getFreq()); // HERE IS A PROBLEM !!
			}
			else
			{
				nRoot->setFreq(lastLeft->getFreq() + lastRight->getFreq()); // HERE IS A PROBLEM !!
			}

			nRoot->setValue(0);
			return nRoot;
		}
		else 
		{
			*leftChild = getElement();
			*rightChild = getElement();

			nRoot->setLeftChild(leftChild);
			nRoot->setRightChild(rightChild);
			nRoot->setFreq(leftChild->getFreq() + rightChild->getFreq());
			nRoot->setValue(0);

			lastLeft = leftChild;
			lastRight = rightChild;

			InsertIntoQueue(*nRoot);
		}
	}

}
HUFFMAN::~HUFFMAN()
{
}
