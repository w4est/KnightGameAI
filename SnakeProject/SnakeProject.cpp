// SnakeProject.cpp : main project file.

#include "stdafx.h"
#include "MyForm.h"

using namespace SnakeProject;

int main(array<System::String ^> ^args)
{
	MyForm^ Form = gcnew MyForm();
	Form->ShowDialog();
    
    return 0;
}
