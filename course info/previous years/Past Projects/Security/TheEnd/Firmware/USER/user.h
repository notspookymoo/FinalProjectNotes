//DO NOT MODIFY THIS/////////////
typedef struct user {          //
  String Name;                 //
  bool Active;                 //
  int PIN;                     //
  uint8_t Tag[7];              //
} User;                        //
/////////////////////////////////

User USERLIST[10] = {
  {"Anubis",  true, 1235, { 81,  21,  11,  11,   0,   0,   0}},
  {"Apophis", true, 2468, { 66,  68,  66, 242,   0,   0,   0}},
  {"Ba'al",   true, 3692, { 33, 112,  51,  15,   0,   0,   0}},
  {"Ra",      true, 4826, {188, 202, 170, 190,   0,   0,   0}},
  {"Vandal",  true,  420, { 15, 178, 147, 195,   0,   0,   0}},
  {"User6",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
  {"User7",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
  {"User8",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
  {"User9",  false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
  {"User10", false, 1234, {  0,   0,   0,   0,   0,   0,   0}},
};