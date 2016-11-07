# KnightGameAI
A small example AI demo that calculates and demonstrates the movement of a knight chess piece, relative to targets around a board. It was originally created from another project, so some names are from the older project.

========================================================================
    APPLICATION : KnightGame AI example Project Overview
========================================================================

This Project was created from a previous project that used a moving snake as an AI.

This project uses the same board, however, it controls a knight chess piece, as it moves around the board to collect "pawns"

Pawns move side to side, making this task a little more difficult.

This project has a working example of a -BFS search,
										-DFS search,
										-A* search,
										-Another A* with a different variation of the search heuristic
										-An averaged A* of the two heuristics.


The laptop used to demonstrate this project did not have the proper .Net libraries, and so this project compiles with Costura.Fody

Costura.Fody is a NuGet package that includes referenced libraries in the binary. 

This package may be required to run this implementation.
However, a release version of the 64-bit binary can be found precompiled in the "x64/Release" Folder if need be.

SnakeProject.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

SnakeProject.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

SnakeProject.cpp
    This is the main application source file.

AssemblyInfo.cpp
	Contains custom attributes for modifying assembly metadata.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
