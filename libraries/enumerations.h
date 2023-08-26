#ifndef ENUMERATIONS_H_INCLUDED
#define ENUMERATIONS_H_INCLUDED

//Enumeration Of Boolean
enum boolean {
  True = 1, False = 0
};

//Enumeration Of Readed Line From Configuration File
enum line_type {
  Scheduler_Configuration = 1, Process_Configuration = 2, Comment = 3, Empty = 4, Error = 5
};

//Enumeration Of Text Color Of Console
enum text_color {
  Default_Text_Color = 0, Black_Text_Color = 30, Red_Text_Color = 31, Green_Text_Color = 32,
    Yellow_Text_Color = 33, Blue_Text_Color = 34, Purple_Text_Color = 35, Cyan_Text_Color = 36, White_Text_Color = 37
};

#endif // ENUMERATIONS_H_INCLUDED