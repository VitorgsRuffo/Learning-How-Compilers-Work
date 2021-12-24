#ifndef PARSER_H
#define PARSER_H

/* Predictive Parser LL(1)
*   Is able to determine if a string is generated by a LL(1) grammar (left-to-right, left-most derivation, 1-symbol lookahead).
*   
*/

/* Recognized grammar:
*
* S → E$
* E → T E 0
* E 0 → +T E 0
* E 0 →
* T → FT 0
* T 0 → ∗F T 0
* T 0 →
* F → (E)
* F → id
*
*/

int parse();

#endif