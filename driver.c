// Batch Number 42
// Saurabh Anand  2013A7PS139P
// Priyank Gupta  2013A7PS060P



#include "lexer.h"
#include "parser.h"
#include "symbolTable.h"
#include "typechecker.h"
#include "semanticAnalyzer.h"
#include "ircode.h"
#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc,char **argv)
//int main()
{

	int ptam=0,ptn=0,atn=0,atam=0;
	if(argc!=3)
	{
		
		printf("Please enter command line argument as $./toycompiler testcase.txt code.asm\n");
		
		return 0;
	}
	

    //printf("\nBoth lexical and syntax analysis modules implemented\n");
    //printf("\nAll lexical error (ERROR 1-4) handled\n");
    //printf("\nParsing error (ERROR 5) handled but program breaks as soon as first parsing error detected\n");

	initStateToToken();

	computeState();

	inittoken_idToTokenName();
	//printf("hello\n");
	initLookUpTable();
	tokenInfo tokenList [5000] ;
	int token_list_len = 0;
	FILE *fp0;
	int i1,i;
	int flag1=0,flag2=0;
	lexer_errors = 0;
	//printf("\nLEXICAL ERRORS ARE : \n");
	


	/*
	for (i=0;(B[i]!='\0');i++)
	{
		printf("%d :%c\n",i,B[i]);
	}*/

	//-----------------------------------------------------------------------------------------------
	// parser initialization code inserted here
	//there are tokens from 0 to dollar (53)
	no_of_tokens = 54;
	no_of_nonterminals = 51;
	int j;
	rule_ptr temp1;
	int type_check_errors=0;
	int semantic_check_errors=0;

	
	

	fp0=fopen("grammarFinal.txt","r+");
	if (!fp0)
	{
		printf("Error in opening Grammar\n");
	}
	FILE* fp1=fopen("finalFirst.txt","r+");
	if (!fp1)
	{
		printf("Error in opening first sets of non-terminals\n");
	}
	FILE* fp2=fopen("finalFollow.txt","r+");
	if (!fp0)
	{
		printf("Error in opening follow set of non-terminals\n");
	}
	
	grammar G;

	G = initGrammar(fp0);
	inittoken_idToTokenName();
	G = initFirstFollow(fp1,fp2,G);
	printf("----------------------------------------------------------------------------------------------------------------\n");
	

	G = firstOfRule (G);
	createParseTable(G);
	

	
	//caution you have changed rule_ptr from temp to temp1
	//-----------------------------------------------------------------------------------------------

	fp=fopen(argv[1],"r+");
	//fp=fopen("testcase1.txt","r+");
	if (!fp)
	{
		printf("error in opening testcase\n");
	}
	k=500;
	// k is buffer size

	buffer_end_index = 0;
	buffer_start_index = 0;
	lnum = 1;
	current_state = 0;


	char* B=(char *)malloc((k+1)*sizeof(char));
	fp=getStream(fp,B,k);

	while (1)
	{
		if(B[buffer_end_index] == '\0')
		{
			buffer_end_index = 0;
			buffer_start_index = 0;
			lexeme_index = 0;
			current_state = 0;
			//initializing tokenInfo temp
			temp.line_no = 0;
			strcpy(temp.value,"");
			temp.token_id = -1;
			fp=getStream(fp,B,k);
		}

		if (strlen(B) == 0)
		{
			break;
		}

		if (B[buffer_end_index] == ' ')
		{
			buffer_end_index++;
			continue;
		}
		//9 as ascii for tab
		if (B[buffer_end_index] == 9)
		{
			buffer_end_index++;
			continue;
		}
		//13 => carriage return
		if (B[buffer_end_index] == 13)
		{
			buffer_end_index++;
			continue;
		}

		if (B[buffer_end_index] == 10)
		{
			lnum++;
			buffer_end_index++;
			continue;
		}



		lexeme_index = 0;
		current_state = 0;
		//initializing tokenInfo temp
		temp.line_no = 0;
		strcpy(temp.value,"");
		temp.token_id = -1;


		tokenInfo temp=getNextToken(B,fp);
		if (temp.token_id >=0)
		{
			//

			if (temp.token_id == TK_FUNID)
			{
				if (flag2 == 0)
				{
					if (flag1 > 0)
					{
						//printf("<TK_END> expected at line number <%d>\n",temp.line_no-1);
						flag1--;
					}
					flag1++;
				}
			}
			else if (temp.token_id == TK_MAIN)
			{
				flag2 = 1;
				if (flag1 > 0)
					{
						//printf("<TK_END> expected at line number <%d>\n",temp.line_no-1);
						flag1--;
					}
			flag1++;
			}
			else if (temp.token_id == TK_END)
			{
					if (flag1 > 0)
						flag1--;
			}
			
			//
			tokenList[token_list_len++] = temp;
		}
		else
		{
			lexer_errors++;
		}



	}
	//
	
	
	//
	temp.token_id = TK_DOLLAR;
	strcpy(temp.value,"$");
	temp.line_no = lnum;
	tokenList[token_list_len++] = temp;

	if (flag1 > 0)
	{
		printf("Input is consumed while it is expected to have token <TK_END> at line number <%d>\n",temp.line_no-1);
	}
	fclose(fp);

	parseTree pt;
	abstractSyntaxTree ast;
	symbol_table_ptr st;
	quadruple_node *quad;
	int quad_size;
	//printf("\n\n\n\n\nNo of lexical errors: %d\n\n\n\n\n",lexer_errors);


	

	int user =1;
	
	printf("Level 4 :  Symbol table/ AST/ Semantic Rules modules work.(Errors 1-16) \n\n");

	while (user != 8)
	{

	printf("--------------------------------------------------------------------------------------------------------------\n");
	//printf("1 :  For removal of comments - print the comment free code on the console \n");
    printf("1 :  For  printing the token list (on the console) generated by the lexer \n");            
    printf("2 :  For parsing to verify the syntactic correctness of the input source code \n");
	printf("3 :  For creating the asbtract syntax tree and printing it appropriatly \n");
	printf("4 :  For displaying the amount of allocated memory and number of nodes to each of parse tree and abstract syntax tree\n");

	printf("5 :  For populating the symbol table and printing it appropriatly \n");
	printf("6 :  For compiling (front end only) to verify the syntactic and semantic correctness of the input source code  \n");
	printf("7 :  For producing assembly code (only when there is no syntactic, semantic or type mismatch errors)\n");
	printf("8 :  Exit\n");
	printf("--------------------------------------------------------------------------------------------------------------\n");

	printf("Enter your choice:\n");
	scanf("%d",&user);
		
	
	if (user == 1)
	{
		int y;
		printf("%15s ","Token Name");
			printf("value is %30s ","Token Value");
			printf ("%6s  ","line");
			for(i1=0; temp.value[i1]!='\0'; ++i1);
    		printf("Length of string\n");
		for (y= 0; (y< token_list_len-1) ; y++)
		{
			temp = tokenList[y];
			printf("%15s ",tokenName[temp.token_id]);
			printf("value is %30s ",temp.value);
			printf ("%6d  ",temp.line_no);
			for(i1=0; temp.value[i1]!='\0'; ++i1);
    		printf("Length of string: %d\n",i1);
		}

	}
	else if (user == 2)
	{
		
		pt = NULL;

		if (lexer_errors > 0)
		{
			
			/*pt = NULL;
			pt = parseInputSourceCode("Test.txt", parse_table, G, tokenList, token_list_len);
			//printParseTree(pt ,"output.txt");
			printParseTree(pt ,argv[2]);
			printf("Partial parse tree generated upto the error occurence\n");*/
			printf(" parse tree creation not possible because there are lexical errors\n");
		}
		else
		{
			pt = NULL;
			pt = parseInputSourceCode("Test.txt", parse_table, G, tokenList, token_list_len);
				//printParseTree(pt ,argv[2]);
				printParseTree(pt ,"output.txt",0,&ptn,&ptam);

			//printf("\nPlease check file with name %s for the depth first traversal result \n\n",argv[2]);
			//	printf("\nPlease check file with name %s for the depth first traversal result \n\n","output.txt");
		}
	}
	else if (user == 3)
	{
		if (pt == NULL)
		{
			printf("Parse tree has not been created \n");

		}
		else
		{
			ast=NULL;
			ast=generateAST(ast,pt);
			if (ast!=NULL)
			{

				printf("AST generated successfully\n");
				printParseTree(ast ,"astout.txt",1,&atn,&atam);

			}
			else
			{
				printf("ast is null\n");
			}
		}		

	}
	else if (user == 4)
	{
		printf("\n\n\n\n");
		if (ast != NULL)
		{
			printf("%30s  Number of Nodes= %8d  Allocated Memory = %8d  bytes\n","Parse Tree",ptn,ptam);
			printf("%30s  Number of Nodes= %8d  Allocated Memory = %8d  bytes\n","AST",atn,atam);
			printf("Compression percentage is : %f\n",(ptam-atam+0.0)/(ptam+0.0)*100);
		}
		else
		{
			printf("create parse tree and ast first \n");
		}

		printf("\n\n\n\n");
		
	}
	else if (user == 5)
	{
		int dummy = get_parse_errors();
		if (dummy == 0){
		printf("\n\n\n\n");
		st = init_symbol_table(ast);
		printf("symbol table populated\n");
		print_symbol_table(st);}
		else
		{
			printf("Symbol table can't be created because there are parsing errors\n");
		}
		printf("\n\n\n\n");
	}
	else if (user == 6)
	{


		int dummy = get_parse_errors();
		if (dummy > 0)
		printf(" Printing parsing Errors");
		print_parse_errors();

		printf("\n\n\n\n");

		if (dummy == 0)
		{
		print_sem_errors();
		//add conditions to check if ast and symbol table has been populated
		
	
		type_check_errors = error_type_checking_ast(st,ast);
		//printf("exited type check block\n");
		//printf(" no of type checking errors are : %d\n",type_check_errors);
		//printf("\n\n\n\n");

		//printf("\n\n\n\n");

		semantic_check_errors = error_semantics(st,ast);
		//printf("no of semantic errors : %d\n",semantic_check_errors);
		//printf("\n\n\n\n");
		if (type_check_errors == 0 && semantic_check_errors == 0)
		{
			printf("----------------------------------------------------------------------------------------------\n");
			printf("--------------------------------CODE COMPILES SUCCESSFULLY------------------------------------\n");
			printf("----------------------------------------------------------------------------------------------\n");
		}
		}
	}

	else if (user == 7)
	{

		quad = code_generation(ast,st);
		quad_size = return_quad_size();
		print_nasm(quad,quad_size,argv[2],st);

	}
	
	

	}//closing while



	return 0;
		
	
}
