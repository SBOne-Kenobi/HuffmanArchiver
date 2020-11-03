#include "huffman.h"
#include <queue>

using HuffmanArchiver::binary;

namespace HuffmanArchiver {

    HuffmanTree::Node::Node(uint32_t weight, unsigned char val) : _weight(weight), _val(val),
                                                                  _left(nullptr), _right(nullptr) {}

    HuffmanTree::Node::Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r) :
            _weight(l->_weight + r->_weight), _val(l->_val), _left(std::move(l)),
            _right(std::move(r)) {}

    HuffmanTree::Node::Node(const Node &other) : Node(other._weight, other._val) {
        _left = std::move(other._left);
        _right = std::move(other._right);
    }

    HuffmanTree::Node &HuffmanTree::Node::operator=(const HuffmanTree::Node &other) {
        if (&other == this)
            return *this;
        _weight = other._weight;
        _val = other._val;
        _left = std::move(other._left);
        _right = std::move(other._right);
        return *this;
    }

    bool HuffmanTree::Node::isLeaf() const {
        return !_left;
    }

    uint32_t HuffmanTree::Node::getWeight() const {
        return _weight;
    }

    unsigned char HuffmanTree::Node::getVal() const {
        return _val;
    }

    const std::unique_ptr<HuffmanTree::Node> &HuffmanTree::Node::getLeft() const {
        return _left;
    }

    const std::unique_ptr<HuffmanTree::Node> &HuffmanTree::Node::getRight() const {
        return _right;
    }

    void HuffmanTree::getCodes(const std::unique_ptr<Node> &v) {
        static std::vector<bool> curCode;
        if (v->isLeaf()) {
            _code[v->getVal()] = curCode;
        } else {
            curCode.push_back(false);
            getCodes(v->getLeft());
            curCode.pop_back();
            curCode.push_back(true);
            getCodes(v->getRight());
            curCode.pop_back();
        }
    }

    HuffmanTree::HuffmanTree(const std::vector<uint32_t> &cnt) : cnt(cnt) {
        _root = nullptr;
        initSize = 0;

        auto cmp = [](Node &a, Node &b) -> bool {
            return a.getWeight() > b.getWeight() || (a.getWeight() == b.getWeight() && a.getVal() > b.getVal());
        };
        std::priority_queue<Node, std::vector<Node>, decltype(cmp)> queue(cmp);
        for (std::size_t i = 0; i < cnt.size(); i++) {
            if (cnt[i] == 0)
                continue;
            queue.push(Node(cnt[i], i));
            initSize += cnt[i] * CHAR_BIT;
        }
        while (queue.size() > 1) {
            auto a = queue.top();
            queue.pop();
            auto b = queue.top();
            queue.pop();
            queue.push(Node(std::make_unique<Node>(a), std::make_unique<Node>(b)));
        }
        if (!queue.empty()) {
            _root = std::make_unique<Node>(queue.top());
            getCodes(_root);
        }
        newSize = 0;
        for (size_t i = 0; i < cnt.size(); i++) {
            if (cnt[i] == 0)
                continue;
            newSize += cnt[i] * _code[i].size();
        }
    }

    void HuffmanTree::encode(std::istream &in, std::ostream &out) const {
        bool outClean = true;
        unsigned char c = 0;
        while (in >> binary<unsigned char>(c)) {
            for (auto it : _code.at(c))
                outClean = writeBool(out, it);
        }
        while (!outClean) {
            bool zero = false;
            outClean = writeBool(out, zero);
        }
    }

    void HuffmanTree::decode(std::istream &in, std::ostream &out) {
        bool inClean = true;
        const Node *cur = _root.get();
        if (!cur || cur->isLeaf()) {
            unsigned char c = 0;
            for (std::size_t i = 0; i < cnt.size(); i++)
                if (cnt[i])
                    c = i;
            for (uint32_t i = 0; i < cnt[c]; i++)
                out << binary<unsigned char>(c);
        } else {
            for (std::size_t i = 0; i < newSize; i++) {
                bool nextBit = false;
                inClean = readBool(in, nextBit);
                if (!in)
                    throw HuffmanException("ERROR: invalid text format.");
                cur = nextBit ? cur->getRight().get() : cur->getLeft().get();
                if (cur->isLeaf()) {
                    out << binary<unsigned char>(cur->getVal());
                    cur = _root.get();
                }
            }
            while (!inClean) {
                bool tmp;
                inClean = readBool(in, tmp);
            }
            if (cur != _root.get())
                throw HuffmanException("ERROR: invalid text format.");
        }
    }

    std::size_t getBytes(std::size_t bits) {
        return (bits + CHAR_BIT - 1) / CHAR_BIT;
    }

    std::size_t HuffmanTree::getInitSize() const {
        return getBytes(initSize);
    }

    std::size_t HuffmanTree::getNewSize() const {
        return getBytes(newSize);
    }

    std::size_t HuffmanTree::getAddSize() const {
        return getBytes(addSize);
    }

    HuffmanException::HuffmanException(const std::string &msg) : logic_error(msg) {}

}