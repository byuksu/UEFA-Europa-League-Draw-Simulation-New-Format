# UEFA-Europa-League-Draw-Simulation-New-Format

This project simulates the draw process for the UEFA Europa League's new format, where teams from different pots are matched up to play home and away games according to specific rules and restrictions.

> **Note**: This project is currently under development. Some features may not be fully implemented or may be subject to change.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Details of Matching Rules](#details-of-matching-rules)
- [Output Example](#output-example)

## Introduction

This project is designed to automate the team matching process for the UEFA Europa League by adhering to the league's specific rules. The program randomly selects teams from each of the four pots, ensuring that each team has a set number of home and away games against unique opponents. Teams from the same country cannot be matched together, and no team should play the same opponent both at home and away.

The project is implemented in C++ and includes advanced memory management to prevent memory leaks.

## Features

- **Random Team Selection**: Teams are randomly chosen from each pot, ensuring an unbiased draw.
- **Home and Away Game Management**: Each team plays four home and four away games with different opponents.
- **Country Restrictions**: Teams from the same country are restricted from playing against each other.
- **Unique Matches**: A team cannot play against the same opponent in both home and away games.
- **Memory Management**: Proper handling of pointers and memory allocations to avoid memory leaks.

## Usage

The program will automatically generate the matchups based on the rules. It provides a list of matches for each team, specifying whether the game is home or away.

### Command Line Interface

After running the executable, follow the prompts to set up the initial parameters, such as teams and pots. The program will output the matches to the console in a readable format.

## Details of Matching Rules

1. **Pot-Based Selection**:
   - The program begins by selecting a team from the first pot. This process continues sequentially for each pot.
   
2. **Home and Away Constraints**:
   - Each team must play a total of eight matches: four at home and four away.
   - For each selected team, the program verifies that the team’s home and away match counts adhere to these requirements.
   
3. **Country Restrictions**:
   - Teams from the same country are restricted from facing each other in any match.

4. **Unique Opponents**:
   - A team cannot play the same opponent both at home and away. The program validates match history to enforce this rule.
   
5. **Memory Management**:
   - Dynamic memory management is handled using smart pointers to prevent memory leaks, with careful validation for uninitialized or null pointers.

### Key Function: `isValidMatch`

The `isValidMatch` function verifies the validity of each match before it's added to the schedule. It performs the following checks:
   - Confirms that the match does not involve teams from the same country.
   - Checks if the teams have not already played each other in both home and away matches.
   - Validates pointers to prevent segmentation faults.

### Error Handling and Debugging

The program includes robust error handling to catch and manage exceptions during runtime:
- **Segmentation Fault Prevention**: Checks for null pointers in the `isValidMatch` function.
- **Duplicate Matches Prevention**: Ensures no team plays the same opponent in both home and away games.
- **Memory Leak Avoidance**: Utilizes smart pointers to manage dynamic memory allocations, reducing the risk of memory leaks.

For debugging, run the program with a debugger like `gdb` to identify any segmentation faults or memory issues.

## Output Example

```plaintext
Creating the teams in the pot 1........................
_______________________________________________________
Pot 1 Teams:
AS Roma from Italy
Manchester United from England
Porto from Portugal
Ajax from Netherlands
Rangers from Scotland
Eintracht Frankfurt from Germany
Lazio from Italy
Tottenham from England
Slavia Praha from Czechia
_______________________________________________________
Creating the teams in the Pot 2........................
_______________________________________________________
Pot 2 Teams:
Real Sociedad from Spain
AZ Alkmaar from Netherlands
Braga from Portugal
Olympiacos from Greece
Lyon from France
Crvena Zvezda from Serbia
PAOK from Greece
Fenerbahçe from Turkey
LASK from Austria
_______________________________________________________
Creating the teams in the Pot 3........................
_______________________________________________________
Pot 3 Teams:
Maccabi Tel Aviv from Israel
Ferencváros from Hungary
Qarabağ from Azerbaijan
Galatasaray from Turkey
Slovan Bratislava from Slovakia
Viktoria Plzeň from Czech Republic
Union SG from Belgium
Dynamo Kyiv from Ukraine
Ludogorets from Bulgaria
_______________________________________________________
Creating the teams in the Pot 4........................
_______________________________________________________
Pot 4 Teams:
Malmö from Sweden
Athletic Club from Spain
Hoffenheim from Germany
Nice from France
APOEL Nicosia from Cyprus
Anderlecht from Belgium
Twente from Netherlands
Beşiktaş from Turkey
Elfsborg from Sweden
_______________________________________________________
Start to choose a team from pot 1 by pressing 1
1
_______________________________________________________
Opponents for Eintracht Frankfurt are drawing....
_______________________________________________________
1. Slavia Praha - Eintracht Frankfurt    (away)
2. Eintracht Frankfurt - AS Roma    (home)
3. Eintracht Frankfurt - Lyon    (home)
4. Crvena Zvezda - Eintracht Frankfurt    (away)
5. Maccabi Tel Aviv - Eintracht Frankfurt    (away)
6. Eintracht Frankfurt - Ludogorets    (home)
7. Twente - Eintracht Frankfurt    (away)
8. Eintracht Frankfurt - Athletic Club    (home)
_______________________________________________________
Start to choose a team from pot 1 by pressing 1
