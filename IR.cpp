#include <iostream>
#include <memory>
#include <vector>
#include "Sentence.h"


/* AstNode Assign */
// class NoInheritRoot;
// class InheritRoot;
// class NoInheritLeaf;


/* InnerSentence */
// class NoInheritSentence
// {
// public:
//     virtual std::string get_type();
//     virtual std::string get_name();
//     virtual std::string feedback(std::shared_ptr<NoInheritRoot> a_shell);
// };


// class InheritSentence
// {
// public:
//     virtual std::string feedback(std::shared_ptr<InheritRoot> a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
// };


// class NoInheritReturner
// {
// public:
//     virtual std::string feedback(std::shared_ptr<NoInheritLeaf> a_shell);
// };


/* AbstractSyntaxTree Node */

/* Base Class */
// class AstNode
// {
// public:
//     AstNode();
//     void add_son_node(std::shared_ptr<AstNode> a_son);
//     bool if_has_son();
//     std::vector<std::string> m_sons_return;
//     virtual std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
// protected:
//     std::vector<std::shared_ptr<AstNode> > m_sons;
// };

void AstNode::add_son_node(std::shared_ptr<AstNode> a_son)
{
    m_sons.push_back(a_son);
}

bool AstNode::if_has_son()
{
    return !m_sons.empty();
}


/* Implement */
// class NoInheritRoot : public AstNode
// {
// public:
//     std::shared_ptr<NoInheritSentence> m_inner_sentence;
//     std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
// };

std::string NoInheritRoot::output(std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    for(auto x = m_sons.begin(); x != m_sons.end(); x++)
    {
        m_sons_return.push_back((*x)->output(m_inner_sentence));
    }
    std::string r = m_inner_sentence->feedback(this);
    return r;
}


// class InheritRoot : public AstNode
// {
// public:
//     std::shared_ptr<InheritSentence> m_inner_sentence;
//     std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
// };

std::string InheritRoot::output(std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    for(auto x = m_sons.begin(); x != m_sons.end(); x++)
    {
        m_sons_return.push_back((*x)->output(a_front_sentence));
    }
    std::string r = m_inner_sentence->feedback(this, a_front_sentence);
    return r;
}


// class NoInheritLeaf : public AstNode
// {
// public:
//     std::shared_ptr<NoInheritReturner> m_inner_sentence;
//     std::string output(std::shared_ptr<NoInheritSentence> a_front_sentence);
// };

std::string NoInheritLeaf::output(std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    for(auto x = m_sons.begin(); x != m_sons.end(); x++)
    {
        m_sons_return.push_back((*x)->output(a_front_sentence));
    }
    std::string r = m_inner_sentence->feedback(this);
    return r;
}





/* AbstractSyntaxTree */
// class AbstractSyntaxTree
// {
// public:
//     AbstractSyntaxTree();
//     std::shared_ptr<AstNode> m_root;
//     std::string begin_scene, sizedef;
//     std::string postorder_output();
// };

std::string AbstractSyntaxTree::postorder_output()
{
    std::string t = "from scene import Scene\nfrom chara import Chara\nfrom playmain import Play\nfrom position import Position\n";
    t += m_root->output(std::make_shared<NoInheritSentence>());
    t += "\nif __name__ == '__main__':\n\tmain = Play" + sizedef + "\n\tSCENE_" + begin_scene + "(main)\n\tmain.play()";
    return t;
}