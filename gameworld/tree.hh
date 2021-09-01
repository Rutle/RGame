#ifndef TREE_HH
#define TREE_HH
#include <queue>
#include <memory>

// BSP Tree
namespace GameWorld {
struct AreaData {
    int x_;
    int y_;
    int width_;
    int height_;
    int centerX_;
    int centerY_;
    AreaData() {}
    AreaData(int x, int y, int width, int height) : x_{x}, y_{y}, width_{width},
        height_{height}, centerX_{x + width/2}, centerY_{y+height/2}{}
};


class Tree {
    public:
        Tree(std::shared_ptr<AreaData> data);
        void getLevel(int level, std::deque<Tree *> &dataQueue);
        void setLeftChild(std::shared_ptr<Tree> leftChild);
        void setRightChild(std::shared_ptr<Tree> rightChild);
        std::shared_ptr<AreaData>& getData();
        bool isLeaf();
        void getLeafs(std::deque<Tree *> &leafQueue);
        std::shared_ptr<Tree> getLeftChild();
        std::shared_ptr<Tree> getRightChild();

    private:
        std::shared_ptr<AreaData> data_;
        std::shared_ptr<Tree> leftChild_;
        std::shared_ptr<Tree> rightChild_;
};
} // GameWorld
#endif // TREE_HH
