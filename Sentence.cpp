#include <vector>
#include <string>
#include "Sentence.h"
#include "indent.cpp"
extern std::string add_indent(std::string a_string);


/* NoInheritSentence */

std::string UpperE::get_type()
{
    return "UpperE";
}

std::string UpperE::get_name()
{
    return "";
}

std::string UpperE::feedback(NoInheritRoot *a_shell)
{
    if(!a_shell->if_has_son())
    {
        return "";
    }
    else if(a_shell->m_sons_return.size() < 2)
    {
        return a_shell->m_sons_return[0];
    }
    else
    {
        return a_shell->m_sons_return[0] + "\n" + a_shell->m_sons_return[1];
    }
}



std::string SceneDef::get_type()
{
    return "SceneDef";
}

std::string SceneDef::get_name()
{
    return m_scene_name;
}

std::string SceneDef::feedback(NoInheritRoot *a_shell)
{
    std::string tail = m_scene_name + ".ask_screen(main)\nmain.add_scene(" + m_scene_name + ")";
    return m_scene_name + " = Scene()\ndef SCENE_" + m_scene_name + "(main):\n" + add_indent(a_shell->m_sons_return[0]) + "\n" + add_indent(tail);

}



std::string CharaDef::get_type()
{
    return "CharaDef";
}

std::string CharaDef::get_name()
{
    return m_chara_name;
}

std::string CharaDef::feedback(NoInheritRoot *a_shell)
{
    return m_chara_name + " = Chara()\n" + a_shell->m_sons_return[0];
}



std::string EventDef::get_type()
{
    return "EventDef";
}

std::string EventDef::get_name()
{
    return m_event_name;
}

std::string EventDef::feedback(NoInheritRoot *a_shell)
{
    if(m_type == 11)
    {
        return "def " + m_event_name + 
        "(main, args):\n\tif len(args) <= 1:\n\t\targs = args[0]\n\t" +
        a_shell->m_sons_return[0] + " = args\n\t" + 
        a_shell->m_sons_return[1] + "\n" + 
        add_indent(add_indent(a_shell->m_sons_return[2]));
    }
    else if(m_type == 10)
    {
        return "def " + m_event_name + 
        "(main, args):\n\tif len(args) <= 1:\n\t\targs = args[0]\n\t" +
        a_shell->m_sons_return[0] + " = args\n" + 
        add_indent(a_shell->m_sons_return[1]);
    }
    else if(m_type == 1)
    {
        return "def " + m_event_name + 
        "(main, args):\n\t" +
        a_shell->m_sons_return[0] + "\n" + 
        add_indent(add_indent(a_shell->m_sons_return[1]));
    }
    else if(m_type == 0)
    {
        return "def " + m_event_name + 
        "(main, args):\n" +
        add_indent(a_shell->m_sons_return[0]);
    }
}




/* InheritSentence */

std::string SceneBlock::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    if(a_shell->if_has_son())
    {
        return a_shell->m_sons_return[0] + "\n" + a_shell->m_sons_return[1];
    }
    else return "";
}


std::string CharaBlock::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    if(a_shell->if_has_son())
    {
        return a_shell->m_sons_return[0] + "\n" + a_shell->m_sons_return[1];
    }
    else return "";
}


std::string EventBlock::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    if(a_shell->if_has_son())
    {
        return a_shell->m_sons_return[0] + "\n" + a_shell->m_sons_return[1];
    }
    else return "";
}



std::string ShapeDef::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    return a_front_sentence->get_name() + ".shape = " + m_shape;
}



std::string DisplayVar::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    if(m_var_type == "scene")
    {
        return "SCENE_" + m_var_name + "(main)";
    }
    else if(m_var_type == "chara")
    {
        return m_var_name + ".position = " + a_shell->m_sons_return[0] + "; " +
               a_front_sentence->get_name() + ".add_chara(" + m_var_name + ")";
    }
    else if(m_var_type == "other_type")
    {
        return a_front_sentence->get_name() + ".add_display(\"" + a_shell->m_sons_return[0] + "\", " + 
               a_shell->m_sons_return[0] + ", " + a_shell->m_sons_return[1] + ")";
    }
    else
    {
        return "";
    }
}



std::string EventRefer::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    /* 部分语句可能同时需要两种不同类型的返回值，这依据其接受到的根结点判断应执行哪种操作 */
    if(a_front_sentence->get_type() == "EventDef")  // 说明实际为NoInheritReturner下操作
    {
        if(a_shell->if_has_son())
        {
            return m_event_name + ", " + a_shell->m_sons_return[0];
        }
        else
        {
            return m_event_name;
        }
    }
    else if(a_front_sentence->get_type() == "SceneDef")
    {
        if(a_shell->if_has_son())
        {
            return a_front_sentence->get_name() + ".add_func_to_scene(" + m_event_name + ", " + a_shell->m_sons_return[0] + ")";
        }
        else
        {
            return a_front_sentence->get_name() + ".add_func_to_scene(" + m_event_name + ")";
        }
    }
}



std::string ZIndexDef::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    return a_front_sentence->get_name() + ".zindex = " + m_zindex;
}



std::string VarDef::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    return a_front_sentence->get_name() + ".add_var('" + m_var_name + "', '" + a_shell->m_sons_return[0] + "')";
}




/* NoInheritReturner */

std::string VarRefer::feedback(NoInheritLeaf *a_shell)
{
    if(!a_shell->if_has_son())
    {
        return m_var_name;
    }
    return a_shell->m_sons_return[0] + ", " + m_var_name;
}



std::string EventIf::feedback(NoInheritLeaf *a_shell)
{
    return "if " + a_shell->m_sons_return[0] + ":";
}



std::string Listener::feedback(NoInheritLeaf *a_shell)
{
    return "main.listen(" + m_key + ")";
}



std::string Position::feedback(NoInheritLeaf *a_shell)
{
    return "Position(" + m_x + ", " + m_y + ")";
}



std::string Closer::feedback(NoInheritLeaf *a_shell)
{
    return "main.close(\"" + m_name + "\")";
}



std::string Schedular::feedback(NoInheritLeaf *a_shell)
{
    return "main.schedule(" + m_frame + ", " + a_shell->m_sons_return[0] + ", time='" + m_time + "')";
}



std::string LowerX::feedback(NoInheritLeaf *a_shell)
{
    if(m_x == "__PositionDefault__")
    {
        return a_shell->m_sons_return[0];
    }
    else
    {
        return m_x;
    }
}



std::string Operator::feedback(NoInheritLeaf *a_shell)
{
    return m_op;
}



std::string Expression::feedback(NoInheritLeaf *a_shell)
{
    return a_shell->m_sons_return[0] + " = " + a_shell->m_sons_return[1];
}



std::string Rightvalue::feedback(NoInheritLeaf *a_shell)
{
    std::string t = "";
    for(auto x = a_shell->m_sons_return.begin(); x != a_shell->m_sons_return.end(); x++)
    {
        t += *x;
    }
    return t;
}



std::string Condition::feedback(NoInheritLeaf *a_shell)
{
    if(m_logical_operator == "and")
    {
        return a_shell->m_sons_return[0] + " and " + a_shell->m_sons_return[1];
    }
    else if(m_logical_operator == "or")
    {
        return a_shell->m_sons_return[0] + " or " + a_shell->m_sons_return[1];
    }
    else
    {
        return a_shell->m_sons_return[0];
    }
}



std::string LogicSta::feedback(NoInheritLeaf *a_shell)
{
    if(m_truth_value == "True")
    {
        return "True";
    }
    else if(m_truth_value == "False")
    {
        return "False";
    }
    else if(m_truth_value == "not")
    {
        return "not " + a_shell->m_sons_return[0];
    }
    else
    {
        std::string t = "";
        for(auto x = a_shell->m_sons_return.begin(); x != a_shell->m_sons_return.end(); x++)
        {
            t += *x;
        }
        return t;
    }
}



std::string CmpOperator::feedback(NoInheritLeaf *a_shell)
{
    return m_op;
}



std::string ReturnTruth::feedback(NoInheritLeaf *a_shell)
{
    return "return " + a_shell->m_sons_return[0];
}



std::string If::feedback(NoInheritLeaf *a_shell)
{
    if(a_shell->m_sons_return.size() < 3)
    {
        return "if " + a_shell->m_sons_return[0] + ":" + add_indent(a_shell->m_sons_return[1]);
    }
    else
    {
        return "if " + a_shell->m_sons_return[0] + ":" + add_indent(a_shell->m_sons_return[1]) + "\nelse:\n" + add_indent(a_shell->m_sons_return[2]);
    }
}



std::string Leftvalue::feedback(NoInheritLeaf *a_shell)
{
    if(m_obj_name == "")
    {
        return m_var_name;
    }
    else
    {
        if(m_var_name == "position")
        {
            return m_obj_name + ".position";
        }
        return m_obj_name + ".var['" + m_var_name + "']";
    }
}



std::string ExitGame::feedback(NoInheritLeaf *a_shell)
{
    return "main.exit()";
}