__int64 __fastcall main(int a1, char **a2, char **a3)
{
  char *input_buffer; // rbp
  FILE *admissions_db; // rax
  char input_buffer_ptr; // bl
  const unsigned __int16 **v6; // r12
  const unsigned __int16 *table; // rsi
  __int64 input_buffer_index; // rax
  bool fully_processed_flag; // cf
  int occurrences_in_dictionary_ref; // ebx
  __int64 flag_index; // rax
  char input_no_blanks[264]; // [rsp+0h] [rbp-138h] BYREF
  unsigned __int64 v14; // [rsp+108h] [rbp-30h]

  v14 = __readfsqword(0x28u);
  input_buffer = (char *)malloc(65536uLL);
  puts(s);
  puts(
    "-------------------------------------------------------------------ESSAY QUESTION-----------------------------------"
    "-------------------------------------");
  puts("Describe a time you did something that contributed to your community (65535 characters max).");
  __printf_chk(1LL, "(start typing here) ");
  fgets(input_buffer, 0xFFFF, stdin);
  admissions_db = fopen("admissions-database.txt", "r");
  input_buffer_ptr = *input_buffer;
  f_addmission_stream = admissions_db;
  if ( input_buffer_ptr )
  {
    v6 = __ctype_b_loc();
    do
    {
      table = *v6;
      input_buffer_index = 0LL;
      while ( (table[input_buffer_ptr] & 0x400) != 0 )// skip blank characters
      {
        ++input_buffer;
        input_no_blanks[input_buffer_index++] = input_buffer_ptr;
        input_buffer_ptr = *input_buffer;
      }
      fully_processed_flag = input_buffer_ptr == 0;// is the input buffer fully processed?
      occurrences_in_dictionary_ref = occurrences_in_dictionary;
      input_no_blanks[(int)input_buffer_index] = 0;
      input_buffer += -fully_processed_flag + 1;
      if ( !strcmp(input_no_blanks, (&dictionary)[occurrences_in_dictionary_ref % 16]) )// check if word is in dictionary
      {
        occurrences_in_dictionary = occurrences_in_dictionary_ref + 1;
      }
      else if ( (unsigned int)fn_check(input_no_blanks) )
      {
        puts(
          "Thank you for your interest in ångstromCTF. Unfortunately, we are unable to offer you a flag in our competitio"
          "n of 2024. Every year, we receive hundreds of qualified flag submissions, and we cannot accept them all.");
        puts("We wish you the best of luck in all of your future challenge-solving endeavors.");
        return 0LL;
      }
      input_buffer_ptr = *input_buffer;
    }
    while ( *input_buffer );
  }
  puts(
    "On behalf of the ångstromCTF admissions committee, it is my pleasure to offer you a flag in our competition of 2024."
    " Your application stood out as highlighting the unique qualities that make you you, including hard work, perseveranc"
    "e, passion and a commitment to making the world a better place.");
  flag_index = global_flag_index++;
  suc_flag[flag_index] = 0;
  __printf_chk(1LL, "Again, congratulations, and the flag is: %s\n");
  return 0LL;
}

__int64 __fastcall fn_check(char *input_no_blanks)
{
  int index; // r13d
  size_t input_len; // rax
  FILE *f_text_file; // rdi
  int eof_or_new_index; // ebx
  __int64 index2; // rbx
  unsigned int zero; // r13d
  __int64 index3; // rbp
  char admission_char; // al
  int suc_flag_index; // [rsp+Ch] [rbp-6Ch] BYREF
  char number_of_word[56]; // [rsp+10h] [rbp-68h] BYREF
  unsigned __int64 v13; // [rsp+48h] [rbp-30h]

  index = 0;
  v13 = __readfsqword(0x28u);
  rewind(f_addmission_stream);                  // sets the file position to the beginning of the file of the stream
  input_no_blanks[strlen(input_no_blanks) + 1] = 0;
  input_no_blanks[strlen(input_no_blanks)] = ':';
  while ( 1 )
  {
    eof_or_new_index = feof(f_addmission_stream);// returns a non-zero value when End-of-File indicator associated with the stream is set, else zero is returned.
    if ( eof_or_new_index )
      break;
    input_len = strlen(input_no_blanks);
    f_text_file = f_addmission_stream;
    if ( index >= input_len )
      goto parse_number;
    if ( input_no_blanks[index] == (unsigned __int8)fgetc(f_addmission_stream) )
      eof_or_new_index = index + 1;
    index = eof_or_new_index;
  }
  f_text_file = f_addmission_stream;
parse_number:
  index2 = 0LL;
  zero = feof(f_text_file);
  if ( zero )
    return 1;
  do
  {
    index3 = (int)index2;
    admission_char = fgetc(f_addmission_stream);
    number_of_word[index2++] = admission_char;
  }
  while ( admission_char != ' ' );
  number_of_word[index3] = 0;
  __isoc99_sscanf(number_of_word, "%o", &suc_flag_index);// convert to octal number
  suc_flag_index ^= 0x4A72B18Cu;
  if ( (suc_flag_index & 0xFF000000) == 0xBC000000// check for right words in assignment-database.txt
    && (unsigned __int8)suc_flag_index == global_flag_index
    && BYTE1(suc_flag_index) == (unsigned __int8)suc_flag_index + occurrences_in_dictionary )// check that no words in dictionary occured
  {
    global_flag_index = (unsigned __int8)suc_flag_index + 1;
    suc_flag[(unsigned __int8)suc_flag_index] = BYTE2(suc_flag_index);
  }
  else
  {
    return 1;
  }
  return zero;
}