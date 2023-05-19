#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/
string saved_E_word;
void getEword();
void gen(string);

bool word(string s) {

  int state = 0;
  int charpos = 0;
  // q0 = state 0
  // q0q1 = state 1
  // qoqy = state 2
  // qsa = state 3
  // qy = state 4
  // qt = state 5
  // qs = state 6
  // qc = state 7

  // consonant = b d g h j k m n p r s t w y z
  // consonant pars = by gy hy ky my ny py ry ch sh ts
  // vowels = a i u e o
  // replace the following todo the word dfa  **
  while (s[charpos] != '\0') {
    char c = s[charpos];
    if (state == 0) { // q0
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // if vowel then go to state 1
        state = 1;
      else if (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j')
        state = 3; // if dwzyj go to state 3
      else if (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' ||
               c == 'n' || c == 'p' || c == 'r')
        state = 4;       // if bghkmnpr go to state 4
      else if (c == 'c') // if c go to state 7
        state = 7;
      else if (c == 's')
        state = 6; // if s go to state 6
      else if (c == 't')
        state = 5; // if c go to state t
      else
        return false; // otherwise return false, token is not valid
      charpos++;      // increment charpos
      continue;
    }                 // end if
    if (state == 1) { // q0q1
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // vowel
        state = 1;
      else if (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j')
        state = 3;
      else if (c == 'n')
        state = 2;
      else if (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' ||
               c == 'p' || c == 'r')
        state = 4;
      else if (c == 't')
        state = 5;
      else if (c == 's')
        state = 6;
      else if (c == 'c')
        state = 7;
      else
        return false;
      charpos++;
      continue;
    }                 // end if
    if (state == 2) { // q0qy
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // vowel
        state = 1;
      else if (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' ||
               c == 'n' || c == 'p' || c == 'r')
        state = 4;
      else if (c == 't')
        state = 5;
      else if (c == 's')
        state = 6;
      else if (c == 'c')
        state = 7;
      else if (c == 'y')
        state = 3;
      else if (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j') // c
        state = 3;                                                       // c
      else
        return false;
      charpos++;
      continue;
    }                 // end if
    if (state == 3) { // qsa
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // vowel
        state = 1;
      else
        return false;
      charpos++;
      continue;
    }                 // end if
    if (state == 4) { // qy
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // vowel
        state = 1;
      else if (c == 'y')
        state = 3;
      else
        return false;
      charpos++;
      continue;
    }                 // end if
    if (state == 5) { // qt
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // vowel
        state = 1;
      else if (c == 's')
        state = 3;
      else
        return false;
      charpos++;
      continue;
    }                 // end if
    if (state == 6) { // qs
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' ||
          c == 'I' || c == 'E') // vowel
        state = 1;
      else if (c == 'h')
        state = 3;
      else
        return false;
      charpos++;
      continue;
    }                 // end if
    if (state == 7) { // qc
      if (c == 'h')
        state = 3;
      else
        return false;
      charpos++;
      continue;
    } // end if
    charpos++;
  } // end of while

  // where did I end up????
  if (state == 0 || state == 1 ||
      state == 2) // if final state is q0, q0q1 or q0qy then return true
    return true;  // end in a final state
  else
    return false;
}

// PERIOD DFA
// Done by: William Cassel
// RE: .
bool period(string s) { // complete this **
  int state = 0;
  int charpos = 0;
  // replace the following todo the word dfa  **
  while (s[charpos] != '\0') {
    if (state == 0 && s[charpos] == '.')
      state = 1;
    else
      return (false);
    charpos++;
  } // end of while

  // where did I end up????
  if (state == 1)
    return (true); // end in a final state
  else
    return (false);
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Justin Yum

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
// Done by Justin Yum
unordered_map<string, tokentype> reservedWords = {{"masu", VERB},
                                                  {"masen", VERBNEG},
                                                  {"mashita", VERBPAST},
                                                  {"masendeshita", VERBPASTNEG},
                                                  {"desu", IS},
                                                  {"deshita", WAS},
                                                  {"o", OBJECT},
                                                  {"wa", SUBJECT},
                                                  {"ni", DESTINATION},
                                                  {"watashi", PRONOUN},
                                                  {"anata", PRONOUN},
                                                  {"kare", PRONOUN},
                                                  {"kanojo", PRONOUN},
                                                  {"sore", PRONOUN},
                                                  {"mata", CONNECTOR},
                                                  {"soshite", CONNECTOR},
                                                  {"shikashi", CONNECTOR},
                                                  {"dakara", CONNECTOR},
                                                  {"eofm", EOFM}};

// ------------ Scanner and Driver -----------------------

ifstream fin; // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Casey Mcguan
int scanner(tokentype &tt, string &w) {
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.
  if (fin.is_open() == false) {
    return false;
  }
  fin >> w; // grab word from input file
  cout << "Scanner called using word: " << w << endl;
  if (w == "eofm") { // if the string is eofm then return
    tt = EOFM;
    cout << "\n\nSuccessfully parsed <story>.";
    return tt;
  }
  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.  */
  // cout << w << "test";
  if (period(w) == true) {
    tt = PERIOD; // if the word is a period then set tt to period and return
    return tt;
  }
  if (word(w) != true) {
    tt = ERROR; // if w is not a word or period then set tt to ERROR and return
    cout << "\nLexical error: " << w
         << " is not a valid token\n"; // output lexical error
    return tt;
  }
  /*
    3. If it was a word,
       check against the reservedwords list.
       If not reserved, tokentype is WORD1 or WORD2
       decided based on the last character.
  */
  tt = reservedWords[w]; // using unordered map to set tt according to w

  if (tt == 0) { // if tt is 0 then that means the word was not found in the
                 // reservedWords table
    if (w[w.size() - 1] == 'E' || w[w.size() - 1] == 'I') {
      tt = WORD2; // if last letter is capital E or I then set tt to word 2
    } else {      // if last letter is not E or I then set to word 1
      tt = WORD1;
    }
  }

  /*
    4. Return the token type & string  (pass by reference)
    */
  return tt; // return token type
} // the end of scanner

// enum tokentype { };
bool token_available = false;
tokentype saved_token;
string saved_lexme;
// ----- Four Utility Functions and Globals -----------------------------------
// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// to display syntax error messages as specified by me.
// Type of error: match fails
// Done by: Justin Yum
void syntaxerror1(string s, tokentype t) {
  if (tokenName[t] == "ERROR") {
    return;
  }
  cout << "SYNTAX ERROR: expected " << tokenName[t] << " but found " << s
       << endl;
  exit(1);
}
// Type of error: switch default in a parser function
// Done by: Justin Yum
void syntaxerror2(string s, string t) { // NOT WORKING
  cout << "SYNTAX ERROR: unexpected " << s << " found in " << t << endl;
  exit(1);
}
// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
// Purpose: Checks to see if there's another token avialable and if so returns
// it Done by: William

tokentype next_token() {

  if (!token_available) {
    scanner(saved_token, saved_lexme);

    token_available = true;
    if (saved_token == ERROR) {
      // cout <<"TEST";
      // string ans;
      syntaxerror1(saved_lexme, saved_token);
      // cout << "Skip or replace the token(s or r): ";

      //}//
    }
  }
  return saved_token;
}

// Purpose: Checks to see if token is as expected and if not then outputs a
// syntax error Done by: William
bool match(tokentype expected) {
  if (next_token() != expected) {
    // cout <<"TEST";
    // cout << "Skip or replace the token(s or r):
    syntaxerror1(saved_lexme, expected);
    // cout << "TEST" <<next_token();
    // char ans;
    //  cout << "Skip or replace the token? (s or r)";
    // cin  >> ans;
    // if(ans == 's'){
    //  scanner(saved_token, saved_lexme);
    //  return true;
    // }
    // else{
    // get token from user
    // saved_token = expected;
    //    return false;

    // }
    // syntaxerror2(saved_lexme, next_token());
    //   return false;
  } else {
    token_available = false;
    cout << "Matched: " << tokenName[expected] << endl;
    return true;
  }
}
// ----- RDP functions - one per non-term -------------------
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: noun
// Done by: William
void noun() { //<noun> ::= WORD1 | PRONOUN
  cout << "Processing <noun>\n";
  switch (next_token()) {
  case WORD1:
    match(WORD1);
    break;
  case PRONOUN:
    match(PRONOUN);
    break;
  default:
    syntaxerror2(saved_lexme, "noun");
    break;
  }
}

//<verb> ::= WORD2
// Done by: William
void verb() { match(WORD2); }

//<be> ::= IS | WAS
// Done by: William

void be() {
  cout << "Processing <be>\n";
  switch (next_token()) {
  case IS:
    match(IS);
    break;
  case WAS:
    match(WAS);
    break;
  default:
    syntaxerror2(saved_lexme, "be");
    break;
  }
}

//<tense> := VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Casey McGuan
void tense() {
  cout << "Processing <tense>\n";
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
    syntaxerror2(saved_lexme, "tense");
    break;
  }
}
//<after object> ::= <verb><tense>PERIOD | <noun> DESTINATION <verb> <tense>
//PERIOD Done by: Justin Yum
void afterObject() {
  cout << "Processing <afterObject>\n";
  switch (next_token()) {
  case WORD2:
    verb();
    getEword();
    gen("ACTION");
    tense();
    gen("TENSE");
    match(PERIOD);
    cout << endl;
    break;      // c
  case PRONOUN: // Case Noun
  case WORD1:
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
    cout << endl;
    break; // c
  default:
    syntaxerror2(saved_lexme, "AFTEROBJECT");
    return; // c
  }
}
//<after noun> ::= <be> PERIOD | DESTINATION <verb><tense> PERIOD | OBJECT<after
//object> Done by: Justin Yum
void afterNoun() {
  cout << "Processing <afterNoun>\n";
  switch (next_token()) {
  case IS:  // if next token is IS or WAS then call be
  case WAS: // case be
    gen("DESCRIPTION");
    be();
    gen("TENSE");
    match(PERIOD);
    cout << "\n";
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
    cout << "\n";
    break; // c
  case OBJECT:
    match(OBJECT);
    gen("OBJECT");
    afterObject();
    break; // c
  default:
    syntaxerror2(saved_lexme, "AFTERNOUN");
    return; // c
  }
}

//<after subject> ::=<verb> <tense> PERIOD | <noun> <after noun>
// Done by: Casey McGuan
void afterSubject() {
  cout << "Processing <afterSubject>\n";
  switch (next_token()) {
  case WORD1:
    noun();
    getEword();
    afterNoun();
    break;
  case WORD2:
    verb();
    getEword();
    gen("ACTION");
    tense();
    gen("TENSE");
    match(PERIOD);
    cout << "\n";
    break;
  default:
    syntaxerror2(saved_lexme, "afterSubject");
    break;
  }
}
// <s> ::= [CONNECTOR] <noun> SUBJECT <after subject>
// Done by: Casey McGuan
void s() {
  cout << "Processing <s>\n";
  // if(next_token() == CONNECTOR)	//c
  //	match(CONNECTOR);           //c
  switch (next_token()) {
  case CONNECTOR:
    match(CONNECTOR);
    getEword();
    gen("CONNECTOR");
  default:
    noun();
    getEword();
    match(SUBJECT);
    gen("ACTOR");
    afterSubject();
  }
}
//<story> ::= <s>
// Done by: Casey McGuan
void story() {
  cout << "Processing <story>\n";
  s();
  while (true) {
    if (next_token() == EOFM) {
      break;
    }
    s();
  }
}

//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

//=================================================
// File translator.cpp written by Group Number: 9
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of
// lexicon.txt Make sure it is easy and fast to look up the translation. Do not
// change the format or content of lexicon.txt

//  Done by: Justin
unordered_map<string, string> Lexicon;


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result
//                 in saved_E_word
//  Done by: William

void getEword() {
  if (Lexicon.find(saved_lexme) !=
      Lexicon.end()) { // if the english word doesn't exist in Lexicon then
                       // .find returns an iterator that is one past the end of
                       // the dictionary which is the same as .end so this if
                       // statement checks if there was a matching english word
                       // in the lexicon or not
    saved_E_word = Lexicon[saved_lexme];
  } else {
    saved_E_word = saved_lexme;
  }
}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Casey
 ofstream out("translation.txt");
void gen(string line_type) {
  if (line_type != "TENSE") {
    out << line_type << ": " << saved_E_word << endl;
  } else {
    out << line_type << ": " << tokenName[saved_token] << endl;
  }
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar
//    rule with semantic routine calls
//    above each non-terminal function

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Justin
int main() {


  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  if (!fin.is_open()) {
    cout << "Fail";
    return 1;
  }
  
  //** opens the lexicon.txt file and reads it into Lexicon
  
  ifstream fin2("lexicon.txt");
  string englishWord, japaneseWord;
  while (!fin2.eof()) { 
    fin2 >> japaneseWord >> englishWord;
    Lexicon[japaneseWord] = englishWord;
  }
  
  //** calls the <story> to start parsing
  story();

  //** closes the input file
  fin.close();
  //** closes traslated.txt
  out.close();

  return 0;
} // end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions