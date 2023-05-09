#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 20
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Gabe
// RE:   (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair
// vowel | consonant-pair vowel n)^+

// FIX THIS
bool word(string s) {

  string VOWELS = "aeiouIE";

  int state = 0;
  int charpos = 0;
  /* replace the following todo the word dfa  */
  while (s[charpos] != '\0') {
    char t;
    if (VOWELS.find(s[charpos]) != -1)
      t = 'V';
    else
      t = s[charpos];

    // q0
    if (state == 0) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 'd':
      case 'w':
      case 'z':
      case 'y':
      case 'j':
        state = 2;
        break;
      case 'b':
      case 'g':
      case 'h':
      case 'k':
      case 'm':
      case 'p':
      case 'r':
      case 'n':
        state = 3;
        break;
      case 't':
        state = 4;
        break;
      case 's':
        state = 5;
        break;
      case 'c':
        state = 6;
        break;
      default:
        return (false);
      }
    } // end of q0

        // q0q1
    else if (state == 1) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 'd':
      case 'w':
      case 'z':
      case 'y':
      case 'j':
        state = 2;
        break;
      case 'b':
      case 'g':
      case 'h':
      case 'k':
      case 'm':
      case 'p':
      case 'r':
        state = 3;
        break;
      case 't':
        state = 4;
        break;
      case 's':
        state = 5;
        break;
      case 'c':
        state = 6;
        break;
      case 'n':
        state = 7;
        break;
      default:
        return (false);
      }
    } // end of q0q1

        // qsa
    else if (state == 2) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      default:
        return (false);
      }
    } //end of qsa

        // qy
    else if (state == 3) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 'y':
        state = 2;
        break;
      default:
        return (false);
      }
    } //end of qsa

        // qt
    else if (state == 4) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 's':
        state = 2;
        break;
      default:
        return (false);
      }
    } //end of qt

        // qs
    else if (state == 5) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 'h':
        state = 2;
        break;
      default:
        return (false);
      }
    } //end of qt

        // qc
    else if (state == 6) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 'h':
        state = 2;
        break;
      default:
        return (false);
      }
    } //end of qt

        // q0qy
    else if (state == 7) {
      switch (t) {
      case 'V':
        state = 1;
        break;
      case 'd':
      case 'w':
      case 'z':
      case 'y':
      case 'j':
        state = 2;
        break;
      case 'b':
      case 'g':
      case 'h':
      case 'k':
      case 'm':
      case 'p':
      case 'r':
      case 'n':
        state = 3;
        break;
      case 't':
        state = 4;
        break;
      case 's':
        state = 5;
        break;
      case 'c':
        state = 6;
        break;
      default:
        return (false);
      }
    } //end of q0qy

        //error case
    else {
      cout << "I am stuck in state " << state << endl;
      return (false);
    } //end of error case

    charpos++; //next char

  } //end of while

// where did I end up????
  if (state == 0 || state == 1 || state == 7)
    return (true); // end in a final state
  else
    return (false);
}

// bool word(string s) {
//   int state = 0;
//   int charpos = 0;
//   char c;
//   char vowels[] = "aiueoIE";

//   while (s[charpos] != '\0') {
//     // c = s[charpos];
//     switch (state) {
//       case 0:
//         if (strchr(vowels, c))
//           state = 1;
//         else if (strchr("dwzyj", c))
//           state = 7;
//         else if (c == 't')
//           state = 3;
//         else if (c == 's')
//           state = 4;
//         else if (c == 'c')
//           state = 5;
//         else
//           return false;
//         break;
//       case 1:
//         if (c == 'n')
//           state = 6;
//         else if (strchr(vowels, c))
//           state = 1;
//         else if (strchr("dwzyj", c))
//           state = 7;
//         else if (strchr("bghkmpr", c))
//           state = 2;
//         else if (c == 't')
//           state = 3;
//         else if (c == 's')
//           state = 4;
//         else if (c == 'c')
//           state = 5;
//         else
//           return false;
//         break;
//       case 2:
//         if (strchr(vowels, c))
//           state = 1;
//         else if (c == 'y')
//           state = 7;
//         else
//           return false;
//         break;
//       case 3:
//         if (strchr(vowels, c))
//           state = 1;
//         else if (c == 's')
//           state = 7;
//         else
//           return false;
//         break;
//       case 4:
//         if (strchr(vowels, c))
//           state = 1;
//         else if (c == 'h')
//           state = 7;
//         else
//           return false;
//         break;
//       case 5:
//         if (c == 'h')
//           state = 7;
//         else
//           return false;
//         break;
//       case 6:
//         if (strchr(vowels, c))
//           state = 1;
//         else if (strchr("dwzyj", c))
//           state = 7;
//         else if (strchr("bghkmpr", c))
//           state = 2;
//         else if (c == 't')
//           state = 3;
//         else if (c == 's')
//           state = 4;
//         else if (c == 'c')
//           state = 5;
//         else
//           return false;
//         break;
//       case 7:
//         if (strchr(vowels, c))
//           state = 1;
//         else
//           return false;
//     }
//     charpos++;
//   }

//   if (state == 0 || state == 1 || state == 6)
//     return true;
//   else
//     return false;
// }

// PERIOD DFA
// Done by: Jared Ryan
bool period(string s) {  // complete this **
  int state = 0;         // init state to 0
  int charpos = 0;       // init char position to 0

  while (s[charpos] != '\0') {  // loop through string of characters while not 0
    if (state == 0 &&
      s[charpos] ==
      '.') {  // if state is 0 AND char position of string is a PERIOD
      state = 1;    // update state to 1
    }
    else {
      return false;  // else, char is not a PERIOD
    }
    charpos++;  // incement char position
  }             // end of while

  // where did I end up????
  if (state == 1) {  // if state is 1, char is a PERIOD
    return true;
  }
  else {
    return false;  // else, char is not a PERIOD
  }
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Jared Ryan

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {
  ERROR,
  WORD1,
  WORD2,
  PERIOD,
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  OBJECT,
  SUBJECT,
  DESTINATION,
  PRONOUN,
  CONNECTOR,
  EOFM
};

// ** For the display names of tokens - must be in the same order as the
// tokentype.
string tokenName[30] = { "ERROR",       "WORD1",   "WORD2",     "PERIOD",
                        "VERB",        "VERBNEG", "VERBPAST",  "VERBPASTNEG",
                        "IS",          "WAS",     "OBJECT",    "SUBJECT",
                        "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" };

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
// string reservewords[20][2] = {
//     "masu",      "VERB",         "masu",        "VERBNEG",   "mashita",
//     "VERBPAST",  "masendeshita", "VERBPASTNEG", "desu",      "IS",
//     "deshita",   "WAS",          "o",           "OBJECT",    "wa",
//     "SUBJECT",   "ni",           "DESTINATION", "watashi",   "PRONOUN",
//     "anata",     "PRONOUN",      "kare",        "PRONOUN",   "kanojo",
//     "PRONOUN",   "sore",         "PRONOUN",     "mata",      "CONNECTOR",
//     "soshite",   "CONNECTOR",    "shikashi",    "CONNECTOR", "dakara",
//     "CONNECTOR", "eofm",         "EOFM" };

// ------------ Scanner and Driver -----------------------

map<string, tokentype> reservedWords;

// set up table function. //Copy from the reservedWords.txt
void buildTable() {
  reservedWords["masu"] = VERB;
  reservedWords["masen"] = VERBNEG;
  reservedWords["mashita"] = VERBPAST;
  reservedWords["masendeshita"] = VERBPASTNEG;

  reservedWords["desu"] = IS;
  reservedWords["deshita"] = WAS;

  reservedWords["o"] = OBJECT;
  reservedWords["wa"] = SUBJECT;

  reservedWords["ni"] = DESTINATION;

  reservedWords["watashi"] = PRONOUN;
  reservedWords["anata"] = PRONOUN;
  reservedWords["kare"] = PRONOUN;
  reservedWords["kanojo"] = PRONOUN;
  reservedWords["sore"] = PRONOUN;

  reservedWords["mata"] = CONNECTOR;
  reservedWords["soshite"] = CONNECTOR;
  reservedWords["shikashi"] = CONNECTOR;
  reservedWords["dakara"] = CONNECTOR;

  reservedWords["eofm"] = EOFM;
}

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Nathan Cimino
int scanner(tokentype& tt, string& w) {
  // ** Grab the next word from the file via fin
  fin >> w;
  cout << "Scanner called using word: " << w << endl;
  // 1. If it is eofm, return right now.

  // int rc = sizeof(reservewords) / sizeof(reservewords[0]);

  if (w == "eofm") {
    tt = EOFM;
    return tt;
  }

  if (period(w)) {
    tt = PERIOD;
  }
  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.
  */
  else if (word(w)) {
    char last = w[w.length() - 1];
    if (reservedWords.find(w) != reservedWords.end()) {
      tt = reservedWords.find(w)->second;
    }

    else if (last == 'I' || last == 'E') {
      tt = WORD2;
    }
    else {
      tt = WORD1;
    }

  }
  /* **
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.
  */
  else {
    cout << "LEXICAL ERROR: " << w << " is not a valid token" << endl;
    tt = ERROR;
  }
  /* **
  4. Return the token type & string  (pass by reference)
  */
  return 0;
}  // the end of scanner

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 20
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------
tokentype saved_token;
string saved_lexeme;
bool token_available;

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: Syntax error, unexpected word
// Done by: Jared
void syntaxerror1(tokentype expected, string saved_lexeme) {
  cout << "SYNTAX ERROR: expected " << tokenName[expected] << " but found "
    << saved_lexeme << endl;
  exit(1);
}
// Type of error: Syntax error, token does not matach/invalid token
// Done by: Jared
void syntaxerror2(string word, tokentype token) {
  cout << "SYNTAX ERROR: unexpected " << word << " found in "
    << tokenName[token] << "." << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks ahead to see what token comes next from the scanner
// HOW: checks first to see if the token_available flag is false.
// If so, saved_token gets scanner() result.
// and the flag is set true.
// A token is grabbed but is not eaten up.
// Returns the saved_token
//
// Done by: Jared
tokentype next_token() {
  if (!token_available) {                // if there is no saved token yet
    scanner(saved_token, saved_lexeme);  // call scanner func to get new token
    token_available = true;              // marks saved token
    if (saved_token == ERROR) {          // if token is ERROR
      syntaxerror2(
        saved_lexeme,
        saved_token);  // call syntax error func to generate error message
    }
  }
  return saved_token;  // return saved token
}

// Purpose: Checks and eats up the expected token.
// HOW: checks to see if expected is different from next_token()
// and if so, generates a syntax error and handles the error
// else token_available becomes false (eat up) and returns true
// Done by: Jared
bool match(tokentype expected) {
  if (next_token() != expected) {  // next token does not match
    syntaxerror1(
      expected,
      saved_lexeme);  // calls syntax error func to generate error message
    return false;       // returns error
  }
  else {              // match found
    token_available = false;  // eat token
    cout << "Matched " << tokenName[expected] << endl;
    return true;  // returns match
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

void story();
void s();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();

// Grammar: <story> ::= <s> {<s>}
// Done by: Jared
void story() {
  cout << "Processing <Story>" << endl;
  s();
  while (true) {
    if (next_token() == EOFM) {
      break;
    }
    s();
  }
  return;
}

// Grammar: 2 <s>::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Nathan Cimino
void s() {
  cout << "Processing <s>" << endl;

  switch (next_token()) {
  case CONNECTOR:
    match(CONNECTOR);
    noun();
    match(SUBJECT);
    after_subject();
    break;
  case WORD1:
  case PRONOUN:
    noun();
    match(SUBJECT);
    after_subject();
    break;
  default:
    syntaxerror2("<s>", next_token());
    return;
  }
}

// Grammar: <after subject>::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: Nathan Cimino
void after_subject() {
  cout << "Processing <after_subject>" << endl;

  switch (next_token()) {
  case WORD2:
    verb();
    tense();
    match(PERIOD);
    break;
  case WORD1:
  case PRONOUN:
    noun();
    after_noun();
    break;
  default:
    syntaxerror2("<after_subject>", next_token());
    return;
  }
}

// Grammar: <after noun>::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD |
// OBJECT <after object> Done by: Nathan Cimino
void after_noun() {
  cout << "Processing <after_noun>" << endl;

  switch (next_token()) {
  case IS:
  case WAS:
    be();
    match(PERIOD);
    break;
  case DESTINATION:
    match(DESTINATION);
    verb();
    tense();
    match(PERIOD);
    break;
  case OBJECT:
    match(OBJECT);
    after_object();
    break;
  default:
    syntaxerror2("<after_noun>", next_token());
    return;
  }
}

// Grammar: <after object>::= <noun> DESTINATION <verb> <tense> PERIOD | <verb>
// <tense> PERIOD Done by: Nathan Cimino
void after_object() {
  cout << "Processing <after_object>" << endl;

  switch (next_token()) {
  case WORD2:
    verb();
    tense();
    match(PERIOD);
    break;
  case WORD1:
  case PRONOUN:
    noun();
    match(DESTINATION);
    verb();
    tense();
    match(PERIOD);
    break;
  default:
    syntaxerror2("<after_object>", next_token());
    return;
  }
}

// Grammar: <noun>::= WORD1 | PRONOUN
// Done by: Nathan Cimino
void noun() {
  cout << "Processing <noun>" << endl;

  switch (next_token()) {
  case WORD1:
    match(WORD1);
    break;
  case PRONOUN:
    match(PRONOUN);
    break;
  default:
    syntaxerror2("<noun>", next_token());
    return;
  }
}

// Grammar: <verb>::= WORD2
// Done by: Nathan Cimino
void verb() {
  cout << "Processing <verb>" << endl;

  switch (next_token()) {
  case WORD2:
    match(WORD2);
    break;
  default:
    syntaxerror2("<verb>", next_token());
    return;
  }
}

// Grammar: <be>::= IS | WAS
// Done by: Nathan Cimino
void be() {
  cout << "Processing <be>" << endl;

  switch (next_token()) {
  case IS:
    match(IS);
    break;
  case WAS:
    match(WAS);
    break;
  default:
    syntaxerror2("<be>", next_token());
  }
}

// Grammar: <tense>::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Nathan Cimino
void tense() {
  cout << "Processing <tense>" << endl;

  switch (next_token()) {
  case VERBPAST:
    match(VERBPAST);
    break;
  case VERBPASTNEG:
    match(VERBPASTNEG);
    break;
  case VERB:
    match(VERB);
    break;
  case VERBNEG:
    match(VERBNEG);
    break;
  default:
    syntaxerror2("<tense>", next_token());
  }
}



/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: **
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Jared 
map<string, string> lexicon;
string saved_E_word;

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** 
string getEword() {
  if (lexicon.find(saved_lexeme) != lexicon.end()) {
    saved_E_word = lexicon.at(saved_lexeme);
    return saved_E_word;
  }
  else {
    saved_E_word = saved_lexeme;
    return saved_E_word;
  }
}


//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Jared
ofstream fout;
void gen(string line_type) {
  if (line_type == "VERBPAST" || line_type == "VERBPASTNEG" || line_type == "VERB" || line_type == "VERBNEG" || line_type == "IS" || line_type == "WAS") {
    fout << "TEST: " << line_type << endl;
  }
  else {
    fout << line_type << ": " << saved_E_word << endl;
  }
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------
string filename;
// The final test driver to start the translator
// Done by:  **
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  ifstream lex_in;
  string jword;
  string eword;

  lex_in.open("lexicon.txt");

  while (lex_in) {
    lex_in >> jword;
    lex_in >> eword;

    lexicon.insert({jword, eword});
  }
  //** closes lexicon.txt 
  lex_in.close();


  //** opens the output file translated.txt

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  fout.open("translated.txt");

  //** calls the <story> to start parsing
  story();
  //** closes the input file
  fin.close();
  //** closes traslated.txt
  fout.close();
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

