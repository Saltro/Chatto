#ifndef SENTENCE_H
#define SENTENCE_H


#include <iostream>
#include <memory>
#include <vector>
#include "IR.h"


class NoInheritSentence
{
public:
    NoInheritSentence() {};
    virtual std::string get_type() {};
    virtual std::string get_name() {};
    virtual std::string feedback(NoInheritRoot *a_shell) {};
};


class InheritSentence
{
public:
    InheritSentence() {};
    virtual std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence) {};
};


class NoInheritReturner
{
public:
    NoInheritReturner() {};
    virtual std::string feedback(NoInheritLeaf *a_shell) {};
};




/* NoInheritSentence */
class UpperE : public NoInheritSentence
{
public:
    UpperE() {};
    std::string get_type();
    std::string get_name();
    std::string feedback(NoInheritRoot *a_shell);
};


class SceneDef : public NoInheritSentence
{
public:
    SceneDef(std::string a_scene_name):m_scene_name(a_scene_name) {};
    std::string get_type();
    std::string get_name();
    std::string feedback(NoInheritRoot *a_shell);
protected:
    std::string m_scene_name;
};


class CharaDef : public NoInheritSentence
{
public:
    CharaDef(std::string a_chara_name):m_chara_name(a_chara_name) {};
    std::string get_type();
    std::string get_name();
    std::string feedback(NoInheritRoot *a_shell);
protected:
    std::string m_chara_name;
};


class EventDef : public NoInheritSentence
{
public:
    EventDef(std::string a_event_name, int a_type):m_event_name(a_event_name), m_type(a_type) {};
    std::string get_type();
    std::string get_name();
    std::string feedback(NoInheritRoot *a_shell);
protected:
    std::string m_event_name;
    int m_type;
};




/* InheritSentence */
class SceneBlock : public InheritSentence
{
public:
    SceneBlock() {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
};


class CharaBlock : public InheritSentence
{
public:
    CharaBlock() {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
};


class EventBlock : public InheritSentence
{
public:
    EventBlock() {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
};


class ShapeDef : public InheritSentence
{
public:
    ShapeDef(std::string a_shape):m_shape(a_shape) {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
protected:
    std::string m_shape;
};


class DisplayVar : public InheritSentence
{
public:
    DisplayVar(std::string a_var_type):m_var_type(a_var_type) {};
    DisplayVar(std::string a_var_type, std::string a_var_name):m_var_type(a_var_type), m_var_name(a_var_name) {}
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence = std::shared_ptr<NoInheritSentence>());
protected:
    std::string m_var_type;
    std::string m_var_name = "";
};


class EventRefer : public InheritSentence
{
public:
    EventRefer(std::string a_event_name):m_event_name(a_event_name) {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
protected:
    std::string m_event_name;
};


class ZIndexDef : public InheritSentence
{
public:
    ZIndexDef(std::string a_zindex):m_zindex(a_zindex) {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
protected:
    std::string m_zindex;
};


class VarDef : public InheritSentence
{
public:
    VarDef(std::string a_var_name):m_var_name(a_var_name) {};
    std::string feedback(InheritRoot *a_shell, std::shared_ptr<NoInheritSentence> a_front_sentence);
protected:
    std::string m_var_name;
};




/* NoInheritReturner */
class VarRefer : public NoInheritReturner
{
public:
    VarRefer(std::string a_var_name):m_var_name(a_var_name) {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_var_name;
};


class EventIf : public NoInheritReturner
{
public:
    EventIf() {};
    std::string feedback(NoInheritLeaf *a_shell);
};


class Listener : public NoInheritReturner
{
public:
    Listener(std::string a_key):m_key(a_key) {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_key;
};


class Position : public NoInheritReturner
{
public:
    Position(std::string a_x, std::string a_y):m_x(a_x), m_y(a_y) {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_x, m_y;
};


class Closer : public NoInheritReturner
{
public:
    Closer(std::string a_name):m_name(a_name) {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_name;
};


class Schedular : public NoInheritReturner
{
public:
    Schedular(std::string a_time, std::string a_frame):m_time(a_time), m_frame(a_frame) {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_time, m_frame;
};


class LowerX : public NoInheritReturner
{
public:
    LowerX(std::string a_x):m_x(a_x) {};
    LowerX() {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_x = "__PositionDefault__";
};


class Operator : public NoInheritReturner
{
public:
    Operator(std::string a_op):m_op(a_op) {};
    Operator(char a_op) {m_op = a_op;};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_op;
};


class Expression : public NoInheritReturner
{
public:
    Expression() {};
    std::string feedback(NoInheritLeaf *a_shell);
};


class Rightvalue : public NoInheritReturner
{
public:
    Rightvalue() {};
    std::string feedback(NoInheritLeaf *a_shell);
};


class Condition : public NoInheritReturner
{
public:
    Condition(std::string a_logical_operator):m_logical_operator(a_logical_operator) {};
    Condition() {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_logical_operator = "";
};


class LogicSta : public NoInheritReturner
{
public:
    LogicSta(std::string a_truth_value):m_truth_value(a_truth_value) {};
    LogicSta() {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_truth_value = "";
};


class CmpOperator : public NoInheritReturner
{
public:
    CmpOperator(std::string a_op):m_op(a_op) {};
    CmpOperator(char a_op) {m_op = a_op;};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_op;
};


class ReturnTruth : public NoInheritReturner
{
public:
    ReturnTruth() {};
    std::string feedback(NoInheritLeaf *a_shell);
};


class If : public NoInheritReturner
{
public:
    If() {};
    std::string feedback(NoInheritLeaf *a_shell);
};


class Leftvalue : public NoInheritReturner
{
public:
    Leftvalue(std::string a_var_name):m_var_name(a_var_name) {};
    Leftvalue(std::string a_obj_name, std::string a_var_name):m_obj_name(a_obj_name), m_var_name(a_var_name) {};
    std::string feedback(NoInheritLeaf *a_shell);
protected:
    std::string m_var_name, m_obj_name = "";
};


class ExitGame : public NoInheritReturner
{
public:
    ExitGame() {};
    std::string feedback(NoInheritLeaf *a_shell);
};


#endif