%{
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include "Sentence.h"
extern std::string tab2space(std::string a_string);


extern "C" {
	int yylex();
	int yyparse();
	void yyerror(char const* s);
};
extern FILE *yyin, *yyout;
AbstractSyntaxTree ast;

struct No_Inherit_Root
{
	std::shared_ptr<NoInheritRoot> no_inherit_root;
	No_Inherit_Root() {no_inherit_root.reset(new NoInheritRoot());}
};

struct Inherit_Root
{
	std::shared_ptr<InheritRoot> inherit_root;
	Inherit_Root() {inherit_root.reset(new InheritRoot());}
};

struct No_Inherit_Leaf
{
	std::shared_ptr<NoInheritLeaf> no_inherit_leaf;
	No_Inherit_Leaf() {no_inherit_leaf.reset(new NoInheritLeaf());}
};
%}

%union
{
	struct No_Inherit_Root *NO_INHERIT_ROOT;
	struct Inherit_Root *INHERIT_ROOT;
	struct No_Inherit_Leaf *NO_INHERIT_LEAF;
	char *ter;
}

%type <NO_INHERIT_ROOT> charadef scenedef eventdef e
%type <INHERIT_ROOT> sceneblock charablock eventblock shapedef displayvar eventrefer zindexdef vardef
%type <NO_INHERIT_LEAF> sizedef varrefer eventif listener position closer schedular x operator expression rightvalue condition logicsta cmpoperator returntruth judge leftvalue exits
%token <ter> SCENE CHARA EVENT RETURN START INVISIBLE CLOSE DISPLAY IN SCHEDULE SIZE EXIT SHAPE ANCHOR ZINDEX LISTEN IF ELSE TYPEINT TYPEFLOAT TYPESTR INT FLOAT STRING VAR AND OR NOT TRUE FALSE ONCE

%%

e: e scenedef
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<UpperE>();
		$$->no_inherit_root->add_son_node($1->no_inherit_root);
		$$->no_inherit_root->add_son_node($2->no_inherit_root);
		ast.m_root = $$->no_inherit_root;
	}
 | e eventdef
 	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<UpperE>();
		$$->no_inherit_root->add_son_node($1->no_inherit_root);
		$$->no_inherit_root->add_son_node($2->no_inherit_root);
		ast.m_root = $$->no_inherit_root;
	}
 | e charadef
 	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<UpperE>();
		$$->no_inherit_root->add_son_node($1->no_inherit_root);
		$$->no_inherit_root->add_son_node($2->no_inherit_root);
		ast.m_root = $$->no_inherit_root;
	}
 | sizedef ';'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<UpperE>();
		ast.m_root = $$->no_inherit_root;
	}
 | /* NULL */
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<UpperE>();
		ast.m_root = $$->no_inherit_root;
	}
 ;
sizedef: SIZE '=' '(' INT ',' INT ')'
	{
		std::string x = $4;
		std::string y = $6;
		ast.sizedef = "(" + x + ", " + y + ")";
	}
	   ;
scenedef: SCENE VAR '{' sceneblock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<SceneDef>($2);
		$$->no_inherit_root->add_son_node($4->inherit_root);
	}
		| START SCENE VAR '{' sceneblock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<SceneDef>($3);
		$$->no_inherit_root->add_son_node($5->inherit_root);
		ast.begin_scene = $3;
	}
		;
eventdef: EVENT VAR '(' varrefer ';' eventif ')' '{' eventblock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<EventDef>($2, 11);
		$$->no_inherit_root->add_son_node($4->no_inherit_leaf);
		$$->no_inherit_root->add_son_node($6->no_inherit_leaf);
		$$->no_inherit_root->add_son_node($9->inherit_root);
	}
		| EVENT VAR '(' ';' eventif ')' '{' eventblock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<EventDef>($2, 1);
		$$->no_inherit_root->add_son_node($5->no_inherit_leaf);
		$$->no_inherit_root->add_son_node($8->inherit_root);
	}
		| EVENT VAR '(' varrefer ')' '{' eventblock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<EventDef>($2, 10);
		$$->no_inherit_root->add_son_node($4->no_inherit_leaf);
		$$->no_inherit_root->add_son_node($7->inherit_root);
	}
		| EVENT VAR '(' ')' '{' eventblock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<EventDef>($2, 0);
		$$->no_inherit_root->add_son_node($6->inherit_root);
	}
		;
charadef: CHARA VAR '{' charablock '}'
	{
		$$ = new No_Inherit_Root();
		$$->no_inherit_root->m_inner_sentence = std::make_shared<CharaDef>($2);
		$$->no_inherit_root->add_son_node($4->inherit_root);
	}
		;
sceneblock: sceneblock shapedef ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<SceneBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | sceneblock displayvar ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<SceneBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | sceneblock eventrefer ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<SceneBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | sceneblock zindexdef ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<SceneBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | /* NULL */
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<SceneBlock>();
	}
		  ;
eventblock: eventblock expression ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | eventblock displayvar ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | eventblock closer ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | eventblock schedular ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | eventblock judge
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | eventblock returntruth ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | eventblock exits ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | /* NULL */
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventBlock>();
	}
		  ;
charablock: charablock vardef ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<CharaBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | charablock shapedef ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<CharaBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | charablock zindexdef ';'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<CharaBlock>();
		$$->inherit_root->add_son_node($1->inherit_root);
		$$->inherit_root->add_son_node($2->inherit_root);
	}
		  | /* NULL */
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<CharaBlock>();
	}
		  ;
vardef: VAR '=' x
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<VarDef>($1);
		$$->inherit_root->add_son_node($3->no_inherit_leaf);
	}
	  ;
varrefer: varrefer ',' VAR
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<VarRefer>($3);
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
	}
		| VAR
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<VarRefer>($1);
	}
		;
eventif: IF '(' condition ')'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<EventIf>();
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
	   ;
listener: LISTEN '(' STRING ')'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Listener>($3);
	}
		;
shapedef: SHAPE '=' STRING
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<ShapeDef>($3);
	}
		;
position: '(' INT ',' INT ')'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Position>($2, $4);
	}
		;
displayvar: DISPLAY leftvalue IN position
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<DisplayVar>("other_type");
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
		$$->inherit_root->add_son_node($4->no_inherit_leaf);
	}
		  | DISPLAY leftvalue INVISIBLE
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<DisplayVar>("other_type");
		$$->inherit_root->add_son_node($2->no_inherit_leaf);
	}
		  | DISPLAY CHARA VAR IN position
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<DisplayVar>("chara", $3);
		$$->inherit_root->add_son_node($5->no_inherit_leaf);
	}
		  | DISPLAY CHARA VAR INVISIBLE
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<DisplayVar>("chara", $3);
	}
		  | DISPLAY SCENE VAR
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<DisplayVar>("scene", $3);
	}
		  ;
eventrefer: VAR '(' varrefer ')'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventRefer>($1);
		$$->inherit_root->add_son_node($3->no_inherit_leaf);
	}
		  | VAR '(' ')'
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<EventRefer>($1);
	}
		  ;
closer: CLOSE VAR
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Closer>($2);
	}
	  ;
zindexdef: ZINDEX '=' INT
	{
		$$ = new Inherit_Root();
		$$->inherit_root->m_inner_sentence = std::make_shared<ZIndexDef>($3);
	}
		 ;
schedular: SCHEDULE INT eventrefer
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Schedular>("absolute", $2);
		$$->no_inherit_leaf->add_son_node($3->inherit_root);
	}
		 | SCHEDULE '+' INT eventrefer
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Schedular>("relative", $3);
		$$->no_inherit_leaf->add_son_node($4->inherit_root);
	}
		 ;
x: INT
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LowerX>($1);
	}
 | FLOAT
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LowerX>($1);
	}
 | STRING
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LowerX>($1);
	}
 | position
 	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LowerX>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
	}
 ;
operator: '+'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Operator>('+');
	}
		| '-'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Operator>('-');
	}
		| '*'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Operator>('*');
	}
		| '/'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Operator>('/');
	}
		| '%'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Operator>('%');
	}
		;
leftvalue: VAR
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Leftvalue>($1);
	}
		 | VAR '.' VAR
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Leftvalue>($1, $3);
	}
		 ;
expression: leftvalue '=' rightvalue
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Expression>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
		  ;
rightvalue: rightvalue operator x
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Rightvalue>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($2->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
		  | rightvalue operator leftvalue
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Rightvalue>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($2->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
		  | x
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Rightvalue>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
	}
		  | leftvalue
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Rightvalue>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
	}
		  ;
judge: IF '(' condition ')' '{' eventblock '}'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<If>();
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($6->inherit_root);
	}
	 | IF '(' condition ')' '{' eventblock '}' ELSE '{' eventblock '}'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<If>();
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($6->inherit_root);
		$$->no_inherit_leaf->add_son_node($10->inherit_root);
	}
	 ;
condition: condition AND logicsta
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Condition>("and");
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
		 | condition OR logicsta
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Condition>("or");
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
		 | logicsta
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<Condition>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
	}
		 ;
logicsta: rightvalue cmpoperator rightvalue
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LogicSta>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($2->no_inherit_leaf);
		$$->no_inherit_leaf->add_son_node($3->no_inherit_leaf);
	}
		| eventrefer
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LogicSta>();
		$$->no_inherit_leaf->add_son_node($1->inherit_root);
	}
		| listener
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LogicSta>();
		$$->no_inherit_leaf->add_son_node($1->no_inherit_leaf);
	}
		| TRUE
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LogicSta>("True");
	}
		| FALSE
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LogicSta>("False");
	}
		| NOT logicsta
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<LogicSta>("not");
		$$->no_inherit_leaf->add_son_node($2->no_inherit_leaf);
	}
		;
cmpoperator: '>'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<CmpOperator>(">");
	}
		   | '<'
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<CmpOperator>("<");
	}
		   | '>' '='
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<CmpOperator>(">=");
	}
		   | '<' '='
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<CmpOperator>("<=");
	}
		   | '=' '='
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<CmpOperator>("==");
	}
		   | '!' '='
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<CmpOperator>("!=");
	}
		   ;
returntruth: RETURN condition
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<ReturnTruth>();
		$$->no_inherit_leaf->add_son_node($2->no_inherit_leaf);
	}
		   ;
exits: EXIT
	{
		$$ = new No_Inherit_Leaf();
		$$->no_inherit_leaf->m_inner_sentence = std::make_shared<ExitGame>();
	}
	 ;

%%

int main() {
	std::string path, outfile;
	std::cout << "Input your code file: ";
	std::cin >> path;
	outfile = "./engine/" + path + ".py";
	FILE *o = fopen(path.c_str(), "r");
	yyout = fopen(outfile.c_str(), "w");
	if(o == NULL)
	{
		std::cout << "\nFile does not exists.\n";
		fclose(o);
	}
	else
	{
		yyin = o;
		yyparse();
		fclose(yyin);
		fprintf(yyout, tab2space(ast.postorder_output()).c_str());
	}
	fclose(yyout);
	std::cout << "Code generation finished.\n";
	return 0;
}

void yyerror(char const* s) {
	std::cout << s << std::endl;
}
