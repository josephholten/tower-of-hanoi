#include <vector>
#include <array>
#include <cstdint>
#include <cstddef>
#include <print>
#include <exception>
#include <iostream>

class Towers {
public:
  Towers(size_t n) {
    for (size_t i = n; i > 0; i--) {
      stacks[0].push_back(i);
    }
  }

  void print() {
    for (size_t s = 0; s < 3; s++) {
      std::print("{}: ",s);
      for (size_t i = 0; i < stacks[s].size(); i++)
        std::print("{} ", stacks[s][i]);
      std::print("\n");
    }
    for (size_t i = 0; i < 10; i++)
      std::print("-");
    std::print("\n");
  }

  size_t move(size_t src, size_t dst, size_t num) {
    if (num == 0)
      return 0;

    if (num == 1) {
      size_t top = stacks[src].back();
      if (!stacks[dst].empty() && stacks[dst].back() < top)
        throw std::runtime_error(std::format("invalid move {} < {}", stacks[dst].back(), top));
      stacks[src].pop_back();
      stacks[dst].push_back(top);
      print();
      return 1;
    }

    size_t tmp = other(src,dst);
    size_t moves = 0;
    moves += move(src,tmp,num-1);
    moves += move(src,dst,1);
    moves += move(tmp,dst,num-1);
    return moves;
  }

private:
  static size_t other(size_t src, size_t dst) {
    int idx[3] = {1,1,1};
    idx[src] = 0;
    idx[dst] = 0;
    for (size_t i = 0; i<3; i++)
      if (idx[i])
        return i;
    throw std::runtime_error("Towers: could not find free stack");
  }

  std::array<std::vector<size_t>,3> stacks;
};

int main() {
  std::print("stack height? =");
  size_t height = 0;
  std::cin >> height;

  Towers t(height);
  t.print();

  std::println("  enter <src> <dst> <num>");
  std::println("----------");

  std::print("> ");

  size_t src, dst, num;
  while (std::cin >> src >> dst >> num) {
    std::println("----------");
    size_t moves = 0;
    Towers backup = t;
    try {
      moves = t.move(src,dst,num);
      std::print("({}) > ", moves);
    } catch (std::runtime_error e) {
      std::println("{}",e.what());
      std::println("----------");
      t = backup;
      t.print();
      std::print("(?) > ", moves);
    }
  }
}
