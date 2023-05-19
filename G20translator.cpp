#include <cstdlib>

#include <iostream>

#include <fstream>

#include <string>

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

    }  // end of q0

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

    }  // end of q0q1

    // qsa

    else if (state == 2) {
      switch (t) {
        case 'V':

          state = 1;

          break;

        default:

          return (false);
      }

    }  // end of qsa

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

    }  // end of qsa

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

    }  // end of qt

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

    }  // end of qt

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

    }  // end of qt

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

    }  // end of q0qy

    // error case

    else {
      cout << "I am stuck in state " << state << endl;

      return (false);

    }  // end of error case

    charpos++;  // next char

  }  // end of while

  // where did I end up????

  if (state == 0 || state == 1 || state == 7)

    return (true);  // end in a final state

  else

    return (false);
}

// PERIOD DFA

// Done by: Jared Ryan

bool period(string s) {  // complete this **

  int state = 0;  // init state to 0

  int charpos = 0;  // init char position to 0

  while (s[charpos] != '\0') {  // loop through string of characters while not 0

    if (state == 0 &&

        s[charpos] ==

            '.') {  // if state is 0 AND char position of string is a PERIOD

      state = 1;  // update state to 1

    }

    else {
      return false;  // else, char is not a PERIOD
    }

    charpos++;  // incement char position

  }  // end of while

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

string tokenName[30] = {"ERROR",       "WORD1",   "WORD2",     "PERIOD",

                        "VERB",        "VERBNEG", "VERBPAST",  "VERBPASTNEG",

                        "IS",          "WAS",     "OBJECT",    "SUBJECT",

                        "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};

// ** Need the reservedwords table to be set up here.

// ** Do not require any file input for this. Hard code the table.

// ** a.out should work without any additional files.

// ------------ Scanner and Driver -----------------------

map<string, tokentype> reservedWords;

// set up table function. //Copy from the reservedWords.txt

void buildReservedTable() {
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
    map<string, tokentype>::iterator it = reservedWords.find(w);

    char last = w[w.size() - 1];

    if (it != reservedWords.end()) {
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

void syntaxerror1(string saved_lexeme, tokentype expected) {
  cout << "SYNTAX ERROR: expected " << tokenName[expected] << " but found "

       << saved_lexeme << endl;

  exit(1);
}

// Type of error: Syntax error, token does not matach/invalid token

// Done by: Jared

void syntaxerror2(string saved_lexeme, string tt) {
  cout << "SYNTAX ERROR: unexpected word" << saved_lexeme << " found in "

       << tt << "." << endl;

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
  if (!token_available) {  // if there is no saved token yet

    scanner(saved_token, saved_lexeme);  // call scanner func to get new token

    token_available = true;  // marks saved token
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

        saved_lexeme,

        expected

    );  // calls syntax error func to generate error message

    return false;  // returns error

  }

  else {  // match found

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

void getEword();

void gen(string);

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

// Grammar:<s>::= [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword#
// SUBJECT #gen(ACTOR)# <after subject>

// Done by: Nathan Cimino

void s() {
  cout << "Processing <S>" << endl;

  if (next_token() != EOFM) {
    if (next_token() == CONNECTOR) {
      match(CONNECTOR);

      getEword();

      gen("CONNECTOR");
    }

    noun();

    getEword();

    match(SUBJECT);

    gen("ACTOR");

    after_subject();
  }
}

// Grammar: <after subject>::= <verb> #getEword# #gen(ACTION)# <tense>
// #gen(TENSE)# PERIOD | <noun> #getEword# <after noun>

// Done by: Nathan Cimino

void after_subject() {
  cout << "Processing <after_subject>\n\n";

  switch (next_token()) {
    case WORD2:

      verb();

      getEword();

      gen("ACTION");

      tense();

      gen("TENSE");

      match(PERIOD);

      break;

    case WORD1:

    case PRONOUN:

      noun();

      getEword();

      after_noun();

      break;

    default:

      syntaxerror2(saved_lexeme, "<after_subject>");

      break;
  }
}

// Grammar: <after noun>::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD |
// DESTINATION #gen(TO)# <verb> #genEword# #gen(ACTION)# <tense> #gen(TENSE)#
// PERIOD | OBJECT #gen(OBJECT)# <after object>

// Done by: Nathan Cimino

void after_noun() {
  cout << "Processing <afterNoun>\n\n";

  switch (next_token()) {
    case IS:

    case WAS:

      be();

      gen("DESCRIPTION");

      gen("TENSE");

      match(PERIOD);

      break;

    case DESTINATION:

      match(DESTINATION);

      gen("TO");

      verb();

      getEword();

      gen("ACTION");

      tense();

      gen("TENSE");

      match(PERIOD);

      break;

    case OBJECT:

      match(OBJECT);

      gen("OBJECT");

      after_object();

      break;

    default:

      syntaxerror2(saved_lexeme, "<after_noun>");  // getting called?

      break;
  }
}

// Grammar: <after object>::= <verb> #getEword()# #gen(ACTION)# <tense>
// #gen(TENSE)# PERIOD | <noun> #getEword# DESTINATION #gen(TO)# <verb>
// #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD

// Done by: Nathan Cimino

void after_object() {
  cout << "Processing <afterObject>\n\n";

  switch (next_token()) {
    case WORD2:

      verb();

      getEword();

      gen("ACTION");

      tense();

      gen("TENSE");

      match(PERIOD);

      break;

    case WORD1:

    case PRONOUN:

      noun();

      getEword();

      match(DESTINATION);

      gen("TO");

      verb();

      getEword();

      gen("ACTION");

      tense();

      gen("TENSE");

      match(PERIOD);

      break;

    default:

      syntaxerror2("<after_object>", saved_lexeme);

      break;
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

      syntaxerror2(saved_lexeme, "<noun>");

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

      syntaxerror2(saved_lexeme, "<verb>");

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

      syntaxerror2(saved_lexeme, "<be>");
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

      syntaxerror2(saved_lexeme, "<tense>");
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

// ** Declare Lexicon (i.e. dictionary) that will hold the content of
// lexicon.txt

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

void getEword() {
  saved_E_word = lexicon[saved_lexeme];

  if (saved_E_word == "") {
    saved_E_word = saved_lexeme;
  }
}

//    gen(line_type) - using the line type,

//                     sends a line of an IR to translated.txt

//                     (saved_E_word or saved_token is used)

//  Done by: Jared

ofstream fout;

void gen(string line_type) {
  if (line_type == "TENSE") {
    fout << line_type << ": " << tokenName[saved_token] << "\n\n";

  }

  else {
    fout << line_type << ": " << saved_E_word << "\n";
  }
}

// ---------------- Driver ---------------------------

string filename;

// The final test driver to start the translator

// Done by:  Gabe

int main() {
  //** opens the lexicon.txt file and reads it into Lexicon

  ifstream lex_in;

  string jword;

  string eword;

  lex_in.open("lexicon.txt");

  while (lex_in >> jword) {
    lex_in >> eword;

    lexicon.insert(make_pair(jword, eword));
  }

  //** closes lexicon.txt

  lex_in.close();

  buildReservedTable();

  //** opens the output file translated.txt

  fout.open("translated.txt");

  cout << "Enter the input file name: ";

  cin >> filename;

  fin.open(filename.c_str());

  //** calls the <story> to start parsing

  story();

  //** closes the input file

  fin.close();

  //** closes traslated.txt

  fout.close();

}  // end

//** require no other input files!

//** syntax error EC requires producing errors.txt of error messages

//** tracing On/Off EC requires sending a flag to trace message output functions

