#include <iostream>
#include <memory>
#include <vector>

// Visitor isn’t a very common pattern because of its complexity and narrow
// applicability.

class Animal;
class Wolf;
class Fish;

class Visitor {
 public:
  virtual void visit(const Animal &animal) const = 0;
  virtual void visit(const Wolf &animal) const = 0;
  virtual void visit(const Fish &animal) const = 0;
};

template <typename AMOUNT>
class AmountVisitor : public Visitor {
 public:
  AmountVisitor(AMOUNT amount) : amount_(amount) {}

  virtual void visit(const Animal &animal) const {
    std::cout << "I eat like a generic Animal\n";
  }

  virtual void visit(const Wolf &animal) const {
    std::cout << "I eat like a wolf\n";
  }

  virtual void visit(const Fish &animal) const {
    std::cout << "I eat like a fish\n";
  }

  AMOUNT amount_;
};

class Animal {
 public:
  virtual void Accept(const Visitor &visitor) const {
    visitor.visit(*this);
  }

  virtual ~Animal() {}
};

class Wolf : public Animal {
 public:
  virtual void Accept(const Visitor &visitor) const {
    visitor.visit(*this);
  }
};

class Fish : public Animal {
 public:
  virtual void Accept(const Visitor &visitor) const {
    visitor.visit(*this);
  }
};

int main() {
  typedef std::shared_ptr<Animal> AnimalPtr;
  std::vector<AnimalPtr> animals;
  animals.push_back(AnimalPtr(new Animal()));
  animals.push_back(AnimalPtr(new Wolf()));
  animals.push_back(AnimalPtr(new Fish()));

  AmountVisitor<int> amount(10);

  for (std::vector<AnimalPtr>::const_iterator it = animals.begin();
       it != animals.end(); ++it) {
    (*it)->Accept(amount);
  }

  return 0;
}
