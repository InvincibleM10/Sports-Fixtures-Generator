Sports Fixture Management System

Introduction
The Sports Fixture Management System is a software solution designed to automate the scheduling of sports matches across multiple venues. It helps sports organizers efficiently manage tournaments by generating fixtures, assigning venues, and organizing match schedules.

Features
Automated Fixture Generation: Dynamically schedules matches using a round-robin algorithm.
Venue Management: Assigns venues sequentially to avoid conflicts.
Time Slot Allocation: Includes customizable match durations and lunch breaks.
Organized Output: Displays fixtures sorted by venue for better clarity.
User-Friendly Interface: Menu-driven system for easy navigation.

Technologies Used
Programming Language: C
Development Tools: GCC Compiler, Text Editor (e.g., VS Code)
Libraries: Standard C Libraries (`stdio.h`, `stdlib.h`, `string.h`)

Usage
How to Use:
1. Add venues and teams via the menu-driven interface.
2. Generate fixtures based on team and venue inputs.
3. View organized schedules sorted by stadiums.

Example Commands:
Enter number of teams: 4
Team 1: TeamA
Team 2: TeamB
Team 3: TeamC
Team 4: TeamD

Enter number of venues: 2
Venue 1: StadiumA
Venue 2: StadiumB

Generate Fixtures:
TeamA vs TeamD at StadiumA at 09:00
TeamB vs TeamC at StadiumB at 09:00

Display Fixtures by Venue:
 StadiumA 
TeamA vs TeamD at 09:00

 StadiumB 
TeamB vs TeamC at 09:00
File Structure

├── fixture_management.c        # Main program file
├── README.md                   # Documentation file
└── assets                      # Additional resources (if any)
