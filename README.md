## Table of contents
* [General info](#general-info)
* [Creating new map file](#creating-new-map-file)
* [Setup](#setup)
* [How it works](#how-it-works)

## General info 
This project is an implementation of the a* algorithm. 
The program, after loading a map from the `grid.txt` file, finds the shortest route avoiding obstacles.
	
## Creating new map file 
* To create new map file simply just run `map_generator.exe`
* To test it, swap grid.txt file in the `aStar` folder
	
## Setup
Open aStar.sln in Visual Studio and hit run, program automaticaly takes map from the `grid.txt` file in `aStar` folder

## How it works?
If u open map file `grid.txt` u will see numbers `5` and `0`:
* `5` are the obstacles
* `0` represents fields to cross

Program takes map file with obstacles and outputs the shortest route represented by numbers `3`
