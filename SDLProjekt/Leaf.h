#ifndef LEAF_H_
#define LEAF_H_
#include <memory>
class Leaf
{
protected:
	std::shared_ptr<Leaf> leftChild;
	std::shared_ptr<Leaf> rightChild;
	unsigned char value;
	unsigned int freq;

public:
	Leaf(unsigned char _value = '\0',unsigned int _freq = 0);
	Leaf(std::shared_ptr<Leaf> left, std::shared_ptr<Leaf> right);
	Leaf(std::shared_ptr<Leaf> left);
	void setLeftChild(std::shared_ptr<Leaf> l);
	void setRightChild(std::shared_ptr<Leaf> l);
	void setFreq(unsigned int I);
	void setValue(unsigned char w);
	unsigned int getFreq();
	unsigned char getValue();
	std::shared_ptr<Leaf> getLeftChild();
	std::shared_ptr<Leaf> getRightChild();
	bool operator>(Leaf & l);
	bool operator<(Leaf & l);
	bool operator>=(Leaf & l);
	bool operator<=(Leaf & l);
};

struct OperatorQueue
{
	bool operator ()(std::shared_ptr<Leaf> leaf1, std::shared_ptr<Leaf> leaf2)
	{

		if (leaf1->getFreq() > leaf2->getFreq()) return true;

		else  return false;

	}
};

#endif LEAF_H_