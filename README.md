# AMCS
Advanced Military Communication System
מתקדם צבאי תקשורת מערכת

## Goals
* ALERT: BUY HEADPHONES
* SELF DESTRUCTION SYSTEM.
* For the IAF unit!
* Data en/de-cryption.
* Physical safety, protection from stealing, passwords, etc.
* Sockets, both Server and Client.
* CLI, Command-line interface for the central server.

## Encryption
* Stage 1 
  * Generate a key.
  * Make a "Periodic table" of 255 elements.
    * Using the key.
    * Each element can be 1, 2, or 3 characters long, like Afx, Sa, A, :).
  * Ascosiate each element of the periodic table to a character, just ASCII[0]=PERIODIC[0], etc.
* Stage 2
  * Generate a key 2.0.
  * Independent of stage 1, just move each byte according to the key.
    * Move each charater according to it's number on the key, and replace it with the other. Example: XYZ, if X gets 2, replace X and Z: ZYX, keep going for Y and so on.
