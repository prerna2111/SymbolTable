#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_Size 101
#define SIZE 100

typedef struct Symbol
{
	char *name;
	int value;
	struct Symbol *next;
} Symbol;

typedef struct SymbolTable
{
	Symbol *symbols[HASH_Size];
	struct SymbolTable *parent;
} SymbolTable;

SymbolTable *curr_scope = NULL;

int getHashIndex(char *val)
{
	char s[SIZE];
	strcpy(s, val);
	int i = 0;
	int l = 0;
	while (s[i] != '\0')
	{
		l = l + s[i] * 2;
		i = i + 1;
	}
	int k = l % HASH_Size;

	int done = 0;
	i = 1;
	int index = k;
	while (!done)
	{
		if (curr_scope->symbols[index] == NULL)
		{
			done = 1;
		}
		else
		{
			index = (k + i * i) % HASH_Size;
			i++;
		}
	}
	return index;
}

void insert(char *name, int value)
{
	Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
	strcpy(sym->name, name);
	sym->value = value;
	int hash_val = getHashIndex(name);
	sym->next = curr_scope->symbols[hash_val];
	curr_scope->symbols[hash_val] = sym;
}

int lookForSymbol(char *name)
{
	int hash_value = getHashIndex(name), ret_val = -1;
	Symbol *sym = curr_scope->symbols[hash_value];
	while (sym != NULL)
	{
		if (strcmp(sym->name, name) == 0)
		{
			return sym->value;
		}
		sym = sym->next;
	}
	SymbolTable *par = curr_scope->parent;
	while (par != NULL)
	{
		sym = par->symbols[hash_value];
		while (sym != NULL)
		{
			if (strcmp(sym->name, name) == 0)
			{
				return sym->value;
			}
			sym = sym->next;
		}
		par = par->parent;
	}
	return ret_val;
}

void new_scope()
{
	SymbolTable *newscope = (SymbolTable *)malloc(sizeof(SymbolTable));
	newscope->parent = curr_scope;
	for (int i = 0; i < HASH_Size; i++)
	{
		newscope->symbols[i] = NULL;
		curr_scope = newscope;
	}
}

void end_scope()
{
	SymbolTable* temp=curr_scope;
	curr_scope=curr_scope->parent;
	free(temp);
}

int main()
{
	FILE * fp=fopen("assign3.txt","r");
	char filestat[SIZE];
	if(fp==NULL)
	{
		printf("Couldn't open file");
	}
	else
	{
		char buffer[100];

		while (fscanf(fp, " %99[^\n]", buffer) == 1)
		{
			if (strcmp(buffer, "begin") == 0)
			{
				new_scope();
			}
			else if (strcmp(buffer, "end") == 0)
			{
				end_scope();
			}
			else if (strncmp(buffer, "assign", 6) == 0)
			{
				char name[100];
				int value;
				sscanf(buffer, "assign %s %d", name, &value);
				insert(name, value);
			}
			else if (strncmp(buffer, "print", 5) == 0)
			{
				char name[100];
				sscanf(buffer, "print %s", name);
				printf("print %s => %d\n", name, lookForSymbol(name));
			}
			fgetc(fp); // Consume newline
		}
	}
	fclose(fp);
	return 0;
}
