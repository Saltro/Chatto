#include <vector>
#include <string>
#include "Sentence.h"
#include "indent.cpp"
extern std::string add_indent(std::string a_string);


/* NoInheritSentence */
// class UpperE : public NoInheritSentence
// {
// public:
//     UpperE();
//     std::string get_type() {return "UpperE";}
//     std::string feedback(NoInheritRoot *a_shell);
// };

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


// class SceneDef : public NoInheritSentence
// {
// public:
//     SceneDef(std::string a_scene_name):m_scene_name(a_scene_name) {};
//     std::string get_type() {return "SceneDef";};
//     std::string get_name();
//     std::string feedback(NoInheritRoot *a_shell);
// protected:
//     std::string m_scene_name;
// };

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


// class CharaDef : public NoInheritSentence
// {
// public:
//     CharaDef(std::string a_chara_name):m_chara_name(a_chara_name) {};
//     std::string get_type() {return "CharaDef";};
//     std::string get_name();
//     std::string feedback(NoInheritRoot *a_shell);
// protected:
//     std::string m_chara_name;
// };

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


// class EventDef : public NoInheritSentence
// {
// public:
//     EventDef(std::string a_event_name, int a_type):m_event_name(a_event_name), m_type(a_type) {};
//     std::string get_type() {return "EventDef";};
//     std::string get_name();
//     std::string feedback(NoInheritRoot *a_shell);
// protected:
//     std::string m_event_name;
//     int m_type;
// };

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


// class ShapeDef : public InheritSentence
// {
// public:
//     ShapeDef(std::string a_shape):m_shape(a_shape) {};
//     std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
// protected:
//     std::string m_shape;
// };

std::string ShapeDef::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    return a_front_sentence->get_name() + ".shape = " + m_shape;
}


// class DisplayVar : public InheritSentence
// {
// public:
//     DisplayVar(std::string a_var_type):m_var_type(a_var_type) {};
//     DisplayVar(std::string a_var_type, std::string a_var_name):m_var_type(a_var_type), m_var_name(a_var_name) {}
//     std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence = nullptr);
// protected:
//     std::string m_var_type;
//     std::string m_var_name = "";
// };

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


// class EventRefer : public InheritSentence
// {
// public:
//     EventRefer(std::string a_event_name):m_event_name(a_event_name) {};
//     std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
// protected:
//     std::string m_event_name;
// };

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


// class ZIndexDef : public InheritSentence
// {
// public:
//     ZIndexDef(std::string a_zindex):m_zindex(a_zindex) {};
//     std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
// protected:
//     std::string m_zindex;
// };

std::string ZIndexDef::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    return a_front_sentence->get_name() + ".zindex = " + m_zindex;
}


// class VarDef : public InheritSentence
// {
// public:
//     VarDef(std::string a_var_name):m_var_name(a_var_name) {};
//     std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
// protected:
//     std::string m_var_name;
// };

std::string VarDef::feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence)
{
    return a_front_sentence->get_name() + ".add_var('" + m_var_name + "', '" + a_shell->m_sons_return[0] + "')";
}




/* NoInheritReturner */
// class VarRefer : public NoInheritReturner
// {
// public:
//     VarRefer(std::string a_var_name):m_var_name(a_var_name) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_var_name;
// };

std::string VarRefer::feedback(NoInheritLeaf *a_shell)
{
    if(!a_shell->if_has_son())
    {
        return m_var_name;
    }
    return a_shell->m_sons_return[0] + ", " + m_var_name;
}


// class EventIf : public NoInheritReturner
// {
// public:
//     EventIf();
//     std::string feedback(NoInheritLeaf *a_shell);
// };

std::string EventIf::feedback(NoInheritLeaf *a_shell)
{
    return "if " + a_shell->m_sons_return[0] + ":";
}


// class Listener : public NoInheritReturner
// {
// public:
//     Listener(std::string a_key):m_key(a_key) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_key;
// };

std::string Listener::feedback(NoInheritLeaf *a_shell)
{
    return "main.listen(" + m_key + ")";
}


// class Position : public NoInheritReturner
// {
// public:
//     Position(std::string a_x, std::string a_y):m_x(a_x), m_y(a_y) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_x, m_y;
// };

std::string Position::feedback(NoInheritLeaf *a_shell)
{
    return "Position(" + m_x + ", " + m_y + ")";
}


// class Closer : public NoInheritReturner
// {
// public:
//     Closer(std::string a_name):m_name(a_name) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_name;
// };

std::string Closer::feedback(NoInheritLeaf *a_shell)
{
    return "main.close(\"" + m_name + "\")";
}


// class Schedular : public NoInheritReturner
// {
// public:
//     Schedular(std::string a_time, std::string a_frame):m_time(a_time), m_frame(a_frame) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_time, m_frame;
// };

std::string Schedular::feedback(NoInheritLeaf *a_shell)
{
    return "main.schedule(" + m_frame + ", " + a_shell->m_sons_return[0] + ", time='" + m_time + "')";
}


// class LowerX : public NoInheritReturner
// {
// public:
//     LowerX(std::string a_x):m_x(a_x) {};
//     LowerX() {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_x = "__PositionDefault__";
// };

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


// class Operator : public NoInheritReturner
// {
// public:
//     Operator(std::string a_op):m_op(a_op) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_op;
// };

std::string Operator::feedback(NoInheritLeaf *a_shell)
{
    return m_op;
}


// class Expression : public NoInheritReturner
// {
// public:
//     Expression();
//     std::string feedback(NoInheritLeaf *a_shell);
// };

std::string Expression::feedback(NoInheritLeaf *a_shell)
{
    return a_shell->m_sons_return[0] + " = " + a_shell->m_sons_return[1];
}


// class Rightvalue : public NoInheritReturner
// {
// public:
//     Rightvalue();
//     std::string feedback(NoInheritLeaf *a_shell);
// };

std::string Rightvalue::feedback(NoInheritLeaf *a_shell)
{
    std::string t = "";
    for(auto x = a_shell->m_sons_return.begin(); x != a_shell->m_sons_return.end(); x++)
    {
        t += *x;
    }
    return t;
}


// class Condition : public NoInheritReturner
// {
// public:
//     Condition(std::string a_logical_operator):m_logical_operator(a_logical_operator) {};
//     Condition() = default;
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_logical_operator = "";
// };

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


// class LogicSta : public NoInheritReturner
// {
// public:
//     LogicSta(std::string a_truth_value):m_truth_value(a_truth_value) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_truth_value;
// };

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


// class CmpOperator : public NoInheritReturner
// {
// public:
//     CmpOperator(std::string a_op):m_op(a_op) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_op;
// };

std::string CmpOperator::feedback(NoInheritLeaf *a_shell)
{
    return m_op;
}


// class ReturnTruth : public NoInheritReturner
// {
// public:
//     ReturnTruth();
//     std::string feedback(NoInheritLeaf *a_shell);
// };

std::string ReturnTruth::feedback(NoInheritLeaf *a_shell)
{
    return "return " + a_shell->m_sons_return[0];
}


// class If : public NoInheritReturner
// {
// public:
//     If();
//     std::string feedback(NoInheritLeaf *a_shell);
// };

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


// class Leftvalue : public NoInheritReturner
// {
// public:
//     Leftvalue(std::string a_var_name):m_var_name(a_var_name) {};
//     Leftvalue(std::string a_obj_name, std::string a_var_name):m_obj_name(a_obj_name), m_var_name(a_var_name) {};
//     std::string feedback(NoInheritLeaf *a_shell);
// protected:
//     std::string m_var_name, m_obj_name = "";
// };

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