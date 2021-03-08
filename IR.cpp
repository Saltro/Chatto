#include <iostream>
#include <memory>
#include <vector>
#include "Sentence.h"

/* AbstractSyntaxTree Node */

/* Base Class */

void AstNode::add_son_node(std::shared_ptr<AstNode> a_son)
{
    m_sons.push_back(a_son);
}

bool AstNode::if_has_son()
{
    return !m_sons.empty();
}


/* Implements */


std::string NoInheritRoot::output(std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    for(auto x = m_sons.begin(); x != m_sons.end(); x++)
    {
        m_sons_return.push_back((*x)->output(m_inner_sentence));
    }
    std::string r = m_inner_sentence->feedback(this);
    return r;
}


std::string InheritRoot::output(std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    for(auto x = m_sons.begin(); x != m_sons.end(); x++)
    {
        m_sons_return.push_back((*x)->output(a_front_sentence));
    }
    std::string r = m_inner_sentence->feedback(this, a_front_sentence);
    return r;
}


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

std::string AbstractSyntaxTree::postorder_output()
{
    std::string t = "from scene import Scene\nfrom chara import Chara\nfrom playmain import Play\nfrom position import Position\n";
    t += m_root->output(std::make_shared<NoInheritSentence>());
    t += "\nif __name__ == '__main__':\n\tmain = Play" + sizedef + "\n\tSCENE_" + begin_scene + "(main)\n\tmain.play()";
    return t;
}