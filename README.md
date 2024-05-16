# Zappy documentation

## Introduction
The goal of this project is to create a network game where several teams confront on a tiles map containing resources.

The winning team is the first one where at least 6 players who reach the maximum elevation

## Installation
Step 1: Clone the repository

Step 2: make re

## Usage
### Server
`./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb`
args         | description
-------------|-------------
-f           | freq
port         | is the port number
width        | is the width of the world
height       | is the height of the world
nameX        | is the name of the team X
clientsNb    | is the number of authorized clients per team
freq         | is the reciprocal of time unit for execution of actions

### IA
`./zappy_ai -p port -h machine`
args         | description
-------------|-------------
port         | is the port number
machine      | is the name of the machine; localhost by default

### GUI
`./zappy_ai -p port -n name -h machine`
args         | description
-------------|-------------
port         | is the port number
name         | is the name of the team
machine      | is the name of the machine; localhost by default

## Documentation
`Requirements: Doxygen`

Documentation can be obtained by running `make doc` and access `./doc/html/index.html` in a web browser