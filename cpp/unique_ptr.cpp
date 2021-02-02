#include <iostream>
#include <string>
#include <memory>

class Node {
 public:
  friend std::unique_ptr<Node> CreateNode(const std::string& node_name);
  virtual ~Node();

 private:
  explicit Node(const std::string& node_name);

  std::string node_name_;
};

Node::Node(const std::string& node_name) : node_name_(node_name) {
  std::cout << "Node ctor\n";
}

Node::~Node() {
  std::cout << "Node dtor\n";
}

std::unique_ptr<Node> CreateNode(const std::string& node_name) {
  std::unique_ptr<Node> node(new Node(node_name));

  return std::move(node);
}

int main(int argc, char **argv) {
  auto node = CreateNode("test_node");
  auto node2 = CreateNode("test_node");

  std::cout << node.get() << std::endl;
  std::cout << node2.get() << std::endl;

  return 0;
}
