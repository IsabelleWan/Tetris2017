#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "textdisplay.h"
#include "cell.h"
#include "subject.h"
#include "observer.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include <sstream>
#include "block.h"
#include "board.h"
#include "graphicsdisplay.h"
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
  bool textOnly = false;// it is false if use graphical
bool seedSet = false; //it is false if seed is default
  int seed = 0;
  bool scriptFound = false; // it is false if use sequence.txt
  string scriptName = "sequence.txt";
bool levelSet = false; //it is false if start level is default
  int startLevel = 0;
  bool gameover = false;
//command-line interface
  for (int i = 1; i < argc; ++i) {
    string in;
    stringstream sinput(argv[i]);
    sinput >> in;
    cout << in;
    if (in == "-text") {
      textOnly = true;
    } else if (in == "-seed") {
if (i == argc - 1) {
         cerr << "Usage: -seed xxx" << endl;
         return 1;
      }
      ++i;
      int temp;
  istringstream ss(argv[i]);
  if (!(ss >> temp)) {
    cerr << "Usage: -seed n; your n is not an integer" << endl;
    return 1;
      }
  if (seedSet) {
    if (temp != seed) {
      cerr << "Warning: ambiguous seed" << endl;
      return 1;
    }
  }
  else {
    seedSet = true;
    seed = temp;
  }
} else if (in == "-scriptfile") {
      if (i == argc - 1) {
         cerr << "Usage: -scriptfile xxx" << endl;
         return 1;
      }
      ++i;
      if (scriptFound) {
         if (argv[i] != scriptName) {
            cerr << "Warning: ambiguous script name" << endl;
            return 1;
         }
      } else {
        scriptName = argv[i];
        scriptFound = true;
      }
    } else if (in == "-startlevel") {
      if (i == argc - 1) {
          cerr << "Usage: -startlevel n" << endl;
          return 1;
      }
  int temp;
      ++i;
      istringstream iss{argv[i]};
        if (!(iss >> temp)) {
           cerr << "Usage: -startlevel n, with n being an integer" << endl;
           return 1;
        }
        if (levelSet){
      if (temp != startLevel) {
        cerr << "Warning: ambiguous startlevel" << endl;
        return 1;
      }
        }
    else {
      levelSet = true;
      startLevel = temp;
    }
    } else {
      cerr << "Command line arguments should be : -text, -seed xxx, scriptfile xxx or -startlevel n" << endl;
      return 1;
    }
  }//end of command-line interface
//out << "seed: " << seed<<endl;
    srand(seed);
    std::map<string, string> m;
    m["left"] = "left";
    m["right"] = "right";
    m["down"] = "down";
    m["clockwise"] = "clockwise";
    m["counterclockwise"] = "counterclockwise";
    m["drop"] = "drop";
    m["levelup"] = "levelup";
    m["leveldown"] = "leveldown";
    m["norandom"] = "norandom";
    m["random"] = "random";
    m["sequence file"] = "sequence file";
    m["I"] = "I";
    m["J"] = "J";
    m["L"] = "L";
    m["O"] = "O";
    m["S"] = "S";
    m["Z"] = "Z";
    m["T"] = "T";
    m["restart"] = "restart";
    m["hint"] = "hint";

    std::map<string, std::vector<string>> macro;
    auto b = make_shared<Board>();

   if (textOnly) b->removegraphics();
      b->init(startLevel, scriptName);
        cout << *b << endl;
    string s;
    while (getline(cin,s)) {
	if (s[0] >= '0' && s[0] <= '9') {
	    stringstream ss(s);
	    int multipliers;
	    ss >> multipliers;
	    string commands;
	    ss >> commands;
	    for (int i = 0; i < multipliers; ++i) {
		if (m.find("left")->second == commands) {
		   b->left();
       if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
		   cout << *b << endl;
		} else if (m.find("right")->second == commands) {
		   b->right();
       if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
		   cout << *b << endl;
		} else if (m.find("down")->second == commands) {
		   b->down();
       if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
		   cout << *b << endl;
		} else if (m.find("clockwise")->second == commands) {
      b->Rotate(1);
      if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
  		cout << *b << endl;
    } else if (m.find("counterclockwise")->second == commands) {
      b->Rotate(0);
      if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
      cout << *b << endl;
    } else if (m.find("drop")->second == commands) {
      try{
      b->drop();}catch(int &e) {
        cout << "Game is over. Do you want to start again?" << endl;}
      cout << *b << endl;
    } else if (m.find("levelup")->second == commands) {
      b->levelup();
      cout << *b << endl;
    } else if (m.find("leveldown")->second == commands) {
      b->leveldown();
      cout << *b << endl;
    }
	    }
	} else if (s[0] == 'n' && s[1] == 'o' && s[2] == 'r' && s[3] == 'a' && s[4] == 'n' && s[5] == 'd' && s[6] == 'o' && s[7] == 'm' && s[8] == ' ') {
		string norandom;
		string filename;
		stringstream ss(s);
		ss >> norandom;
		ss >> filename;
		b->norandom(filename);
		cout << *b << endl;
} else if (s[0] == 's' && s[1] == 'e' && s[2] == 'q' && s[3] == 'u' && s[4] == 'e' && s[5] == 'n' && s[6] == 'c' && s[7] == 'e' && s[8] == ' ') {
		string sequence;
		string filename;
		stringstream ss(s);
		ss >> sequence;
		ss >> filename;
		ifstream f{filename};
		while (true) {
		string fcommands;
		if (!(f >> fcommands)) break;
	if (fcommands[0] >= '0' && fcommands[0] <= '9') {
	    stringstream ss(fcommands);
	    int multipliers;
	    ss >> multipliers;
	    string commands;
	    ss >> commands;
	    for (int i = 0; i < multipliers; ++i) {
		if (m.find("left")->second == commands) {
		   b->left();
       if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
		   cout << *b << endl;
		} else if (m.find("right")->second == commands) {
		   b->right();
       if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
		   cout << *b << endl;
		} else if (m.find("down")->second == commands) {
		   b->down();
       if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
		   cout << *b << endl;
		} else if (m.find("clockwise")->second == commands) {
      b->Rotate(1);
      if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
  		cout << *b << endl;
    } else if (m.find("counterclockwise")->second == commands) {
      b->Rotate(0);
      if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
      cout << *b << endl;
    } else if (m.find("drop")->second == commands) {
      try{b->drop();}catch(int &e) {cout << "Game is over. Do you want to start again?" << endl;}
      cout << *b << endl;
    } else if (m.find("levelup")->second == commands) {
      b->levelup();
      cout << *b << endl;
    } else if (m.find("leveldown")->second == commands) {
      b->leveldown();
      cout << *b << endl;
    }
	    }
}

			if (m.find("left")->second == fcommands) {
	       b->left();
         if(b->curlevel() > 2) b->down();
	       cout << *b << endl;
	   }
	   if (m.find("right")->second == fcommands) {
	       b->right();
         if(b->curlevel() > 2) b->down();
         cout << *b << endl;
	   }
    	   if (m.find("down")->second == fcommands) {
	       b->down();
         if(b->curlevel() > 2) b->down();
	       cout << *b << endl;
	   }
	   if (m.find("drop")->second == fcommands) {
	       try{b->drop();}catch(int &e) {cout << "Game is over. Do you want to start again?" << endl;}
	       cout << *b << endl;
	   }
	   if (m.find("clockwise")->second == fcommands) {
		     b->Rotate(1);
         if(b->curlevel() > 2) b->down();
		     cout << *b << endl;
	   }
     if (m.find("counterclockwise")->second == fcommands) {
         b->Rotate(0);
         if(b->curlevel() > 2) b->down();
         cout << *b << endl;
     }
     if (m.find("levelup")->second == fcommands) {
       b->levelup();
       cout << *b << endl;
         //levelup
     }
     if (m.find("leveldown")->second == fcommands) {
       b->leveldown();
       cout << *b << endl;
         //leveldown
     }
     if (m.find("norandom")->second == fcommands) {
       string name;
       cin >> name;
       b->norandom(name);
       cout << *b << endl;
     }
     if (m.find("random")->second == fcommands) {
       b->random();
       cout << *b << endl;
     }
     if (m.find("sequence")->second == fcommands) {
      /*string fileName;
 			if (!cin >> fileName) throw "file for sequence not found. (format: file.txt)";
 			ifstream iss{ fileName };
 			string command;
 			while (iss >> command) {
         *///sequence file
     }
     if (m.find("I")->second == fcommands) {
          b->replace("I");//I
     }
     if (m.find("J")->second == fcommands) {
          b->replace("J");//J
     }
     if (m.find("L")->second == fcommands) {
          b->replace("L");//L
     }
     if (m.find("O")->second == fcommands) {
          b->replace("O");//O
     }
     if (m.find("S")->second == fcommands) {
          b->replace("S");//O
     }
     if (m.find("Z")->second == fcommands) {
          b->replace("Z");//O
     }
     if (m.find("T")->second == fcommands) {
          b->replace("T");//O
     }
     if (m.find("restart")->second == fcommands) {
       int hs = b->getHigh();
       b = make_shared<Board>();
   if (textOnly) b->removegraphics();
 			 b->init(startLevel, scriptName);
 			 b->init(startLevel, scriptName);
			 b->setHigh(hs);
  if (!textOnly) b->printHigh();
 			 cout << *b << endl;
         //restart
     }
     if (m.find("hint")->second == fcommands) {
       b->hint();
            cout << *b << endl;
     }

		}
}

else {
    for (const auto &w : macro) {
      if (w.first == s) {
      for (unsigned int i = 0; i < w.second.size(); ++i) {
        if (w.second[i][0] >= '0' && w.second[i][0] <= '9') {
          stringstream ss(w.second[i]);
          int multipliers;
          ss >> multipliers;
          string commands;
          ss >> commands;
          for (int i = 0; i < multipliers; ++i) {
              if (m.find("left")->second == commands) {
                  b->left();
                  if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
                  cout << *b << endl;
              } else if (m.find("right")->second == commands) {
                  b->right();
                  if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
                  cout << *b << endl;
              } else if (m.find("down")->second == commands) {
                  b->down();
                  if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
                  cout << *b << endl;
              } else if (m.find("clockwise")->second == commands) {
                  b->Rotate(1);
                  if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
                  cout << *b << endl;
              } else if (m.find("counterclockwise")->second == commands) {
                  b->Rotate(0);
                  if(b->curlevel() > 2 && i + 1 == multipliers) b->down();
                  cout << *b << endl;
              } else if (m.find("drop")->second == commands) {
                  try{b->drop();}catch(int &e) {cout << "Game is over. Do you want to start again?" << endl;}
                  cout << *b << endl;
              } else if (m.find("levelup")->second == commands) {
                  b->levelup();
                  cout << *b << endl;
              } else if (m.find("leveldown")->second == commands) {
                  b->leveldown();
                  cout << *b << endl;
              }
            }
          }
           if (m.find("left")->second == w.second[i]) {
              b->left();
              if(b->curlevel() > 2) b->down();
              cout << *b << endl;
           }
           if (m.find("right")->second == w.second[i]) {
              b->right();
              if(b->curlevel() > 2) b->down();
              cout << *b << endl;
           }
              if (m.find("down")->second == w.second[i]) {
              b->down();
              if(b->curlevel() > 2) b->down();
              cout << *b << endl;
           }
           if (m.find("drop")->second == w.second[i]) {
              try{b->drop();}catch(int &e) {cout << "Game is over. Do you want to start again?" << endl;}
              cout << *b << endl;
          }
          if (m.find("clockwise")->second == w.second[i]) {
              b->Rotate(1);
              if(b->curlevel() > 2) b->down();
              cout << *b << endl;
          }
          if (m.find("counterclockwise")->second == w.second[i]) {
              b->Rotate(0);
              if(b->curlevel() > 2) b->down();
              cout << *b << endl;
          }
          if (m.find("levelup")->second == w.second[i]) {
            b->levelup();
            cout << *b << endl;
              //levelup
          }
          if (m.find("leveldown")->second == w.second[i]) {
            b->leveldown();
            cout << *b << endl;
          }
          if (m.find("norandom")->second == w.second[i]) {
            string name;
		          cin >> name;
		            b->norandom(name);
		              cout << *b << endl;
          }
          if (m.find("random")->second == w.second[i]) {
            b->random();
            cout << *b << endl;
          }
          if (m.find("sequence")->second == w.second[i]) {
            /*string fileName;
           if (!cin >> fileName) throw "file for sequence not found. (format: file.txt)";
           ifstream iss{ fileName };
           string command;
           while (iss >> command) {//sequence file*/
          }
          if (m.find("I")->second == w.second[i]) {
			  b->replace("I");
          }
          if (m.find("J")->second == w.second[i]) {
			  b->replace("J");
          }
          if (m.find("L")->second == w.second[i]) {
			  b->replace("L");
          }
          if (m.find("O")->second == w.second[i]) {
			  b->replace("O");
          }
          if (m.find("S")->second == w.second[i]) {
			  b->replace("S");
          }
          if (m.find("Z")->second == w.second[i]) {
			  b->replace("Z");
          }
          if (m.find("T")->second == w.second[i]) {
			  b->replace("T");
          }

          if (m.find("restart")->second == w.second[i]) {
	    int hs = b->getHigh();
            b = make_shared<Board>();
   if (textOnly) b->removegraphics();
      			b->init(startLevel, scriptName);
			b->setHigh(hs);
if (!textOnly)b->printHigh();
      			cout << *b << endl;
              //restart
          }
          if (m.find("hint")->second == w.second[i]) {
            b->hint();
            cout << *b << endl;
          }

        }
      }
    }
	   if (m.find("left")->second == s) {
	       b->left();
         if(b->curlevel() > 2) b->down();
	       cout << *b << endl;
	   }
	   if (m.find("right")->second == s) {
	       b->right();
         if(b->curlevel() > 2) b->down();
         cout << *b << endl;
	   }
    	   if (m.find("down")->second == s) {
	       b->down();
         if(b->curlevel() > 2) b->down();
	       cout << *b << endl;
	   }
	   if (m.find("drop")->second == s) {
	       try{b->drop();}catch(int &e) {cout << "Game is over. Do you want to start again?" << endl;}
	       cout << *b << endl;
	   }
	   if (m.find("clockwise")->second == s) {
		     b->Rotate(1);
         if(b->curlevel() > 2) b->down();
		     cout << *b << endl;
	   }
     if (m.find("counterclockwise")->second == s) {
         b->Rotate(0);
         if(b->curlevel() > 2) b->down();
         cout << *b << endl;
     }
     if (m.find("levelup")->second == s) {
       b->levelup();
       cout << *b << endl;
         //levelup
     }
     if (m.find("leveldown")->second == s) {
       b->leveldown();
       cout << *b << endl;
         //leveldown
     }
     if (m.find("norandom")->second == s) {
       string name;
       cin >> name;
       b->norandom(name);
       cout << *b << endl;
     }
     if (m.find("random")->second == s) {
       b->random();
       cout << *b << endl;
     }
     if (m.find("I")->second == s) {
          b->replace("I");//I
          cout << *b << endl;
     }
     if (m.find("J")->second == s) {
          b->replace("J");//J
          cout << *b << endl;
     }
     if (m.find("L")->second == s) {
		 b->replace("L");//L
          cout << *b << endl;
     }
     if (m.find("O")->second == s) {
		 b->replace("O");//O
                 cout << *b << endl;
     }
     if (m.find("S")->second == s) {
          b->replace("S");//S
          cout << *b << endl;
     }
     if (m.find("Z")->second == s) {
          b->replace("Z");//Z
          cout << *b << endl;
     }
     if (m.find("T")->second == s) {
          b->replace("T");//T
          cout << *b << endl;
     }
     if (m.find("restart")->second == s) {
       int hs = b->getHigh();
       b = make_shared<Board>();
   if (textOnly) b->removegraphics();
	 b->init(startLevel, scriptName);
	 b->setHigh(hs);
   if (!textOnly)  b->printHigh();
 	 cout << *b << endl;
         //restart
     }
     if (m.find("hint")->second == s) {
       b->hint();
            cout << *b << endl;
     }

     stringstream stream(s);
     int com = 0; // 1 if change, 2 if macro, 0 for nothing
     while(true) {
      string segment;
      if (stream >> segment) {
        if (com == 1) {
          string newname;
          stream >> newname;
          m.at(segment) = newname;
        } else if (com == 2) {
          vector<string> commands;
          while (true) {
            string macroadd;
            if (stream >> macroadd) {
              commands.emplace_back(macroadd);
            } else {
              break;
            }
          }
          macro[segment] = commands;
        }
        if (segment == "set") {
          com = 1;
        } else if (segment == "macro") {
          com = 2;
        }
      } else {
        com = 0;
        break;
      }
     }

       }
   }
   m.clear();
   macro.clear();
   b->removegraphics();
}


