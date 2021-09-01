#include "tree.hh"

namespace GameWorld {
Tree::Tree(std::shared_ptr<AreaData> data) : data_{nullptr},
    leftChild_{nullptr}, rightChild_{nullptr} {
    data_ = data;
}

void Tree::getLevel(int level, std::deque<Tree *> &dataQueue) {
    if ( level == 1 ) {
        dataQueue.push_back(this);
    } else {
        if ( this->leftChild_ != nullptr ) {
            this->leftChild_->getLevel(level - 1, dataQueue);
        }
        if ( this->rightChild_ != nullptr ) {
            this->rightChild_->getLevel(level - 1, dataQueue);
        }
    }

}

void Tree::setLeftChild(std::shared_ptr<Tree> leftChild) {
    leftChild_ = leftChild;
}

void Tree::setRightChild(std::shared_ptr<Tree> rightChild) {
    rightChild_ = rightChild;
}

std::shared_ptr<AreaData> &Tree::getData() {
    return data_;
}

bool Tree::isLeaf() {
    if ( leftChild_ == nullptr && rightChild_ == nullptr ) {
        return true;
    }
    return false;
}

void Tree::getLeafs(std::deque<Tree *> &leafQueue) {
    if ( leftChild_ == nullptr &&rightChild_ == nullptr ) {
        leafQueue.push_back(this);
    }
    if ( leftChild_ != nullptr ) {
        leftChild_->getLeafs(leafQueue);
    }
    if ( rightChild_ != nullptr ) {
        rightChild_->getLeafs(leafQueue);
    }
}

std::shared_ptr<Tree> Tree::getLeftChild() {
    return leftChild_;
}

std::shared_ptr<Tree> Tree::getRightChild() {
    return rightChild_;
}

} // GameWorld
