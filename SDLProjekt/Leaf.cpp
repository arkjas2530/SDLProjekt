#include"Leaf.h"	


Leaf::Leaf(unsigned char _value, unsigned int _freq) 
	: value(_value), freq(_freq), leftChild(nullptr), rightChild(nullptr)
{
}

Leaf::Leaf(std::shared_ptr<Leaf> left, std::shared_ptr<Leaf> right)
	:rightChild(right),leftChild(left),freq(right->freq + left->freq),value('\0')
{
}

Leaf::Leaf(std::shared_ptr<Leaf> left)
	: rightChild(nullptr), leftChild(left), freq(left->freq), value('\0')
{
}

void Leaf::setLeftChild(std::shared_ptr<Leaf> l)
{
	leftChild = l;
}

void Leaf::setRightChild(std::shared_ptr<Leaf> l)
{
	rightChild = l;
}

void Leaf::setFreq(unsigned int I)
{
	freq = I;
}

void Leaf::setValue(unsigned char w)
{
	value = w;
}

unsigned int Leaf::getFreq()
{
	return freq;
}

unsigned char Leaf::getValue()
{
	return value;
}

std::shared_ptr<Leaf> Leaf::getLeftChild()
{
	if (!leftChild)
		return nullptr;
	return leftChild;
}

std::shared_ptr<Leaf> Leaf::getRightChild()
{
	if (!rightChild)
		return nullptr;
	return rightChild;
}

bool Leaf::operator>(Leaf & l)
{
	if (this->getFreq() > l.getFreq())
		return true;
	else
		return false;
}

bool Leaf::operator<(Leaf & l)
{
	return l.operator>(*this);
}

bool Leaf::operator>=(Leaf & l)
{
	if (this->getFreq() <= l.getFreq())
		return true;
	else
		return false;
}

bool Leaf::operator<=(Leaf & l)
{
	return l.operator>=(*this);
}