#ifndef  IR_H
#define IR_H


#include <iostream>
#include <memory>
#include <vector>


class NoInheritSentence;
class InheritSentence;
class NoInheritReturner;

class AstNode
{
public:
    AstNode() {};
    void add_son_node(std::shared_ptr<AstNode> a_son);
    bool if_has_son();
    std::vector<std::string> m_sons_return;
    virtual std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence) {};
protected:
    std::vector<std::shared_ptr<AstNode> > m_sons;
};

class NoInheritRoot : public AstNode
{
public:
    NoInheritRoot() {};
    NoInheritRoot(std::shared_ptr<NoInheritSentence> a_inner_sentence):m_inner_sentence(a_inner_sentence) {};
    std::shared_ptr<NoInheritSentence> m_inner_sentence;
    std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
};

class InheritRoot : public AstNode
{
public:
    InheritRoot() {};
    InheritRoot(std::shared_ptr<InheritSentence> a_inner_sentence):m_inner_sentence(a_inner_sentence) {};
    std::shared_ptr<InheritSentence> m_inner_sentence;
    std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
};

class NoInheritLeaf : public AstNode
{
public:
    NoInheritLeaf() {};
    NoInheritLeaf(std::shared_ptr<NoInheritReturner> a_inner_sentence):m_inner_sentence(a_inner_sentence) {};
    std::shared_ptr<NoInheritReturner> m_inner_sentence;
    std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
};


class AbstractSyntaxTree
{
public:
    AbstractSyntaxTree() {};
    std::shared_ptr<AstNode> m_root;
    std::string begin_scene, sizedef;
    std::string postorder_output();
};


#endif