#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BUF_SIZE 100000
#define MAX_ROWS 1000
#define MAX_COLS 1000

char buffer[BUF_SIZE];
int buf_len = 0;
char filename[256] = "output.txt";

int cursor_x = 0;
int cursor_y = 0;

int row_starts[MAX_ROWS];
int total_rows = 0;

void recalculate_rows() {
  total_rows = 0;
  row_starts[total_rows++] = 0;
  for (int i = 0; i < buf_len; i++) {
    if (buffer[i] == '\n' && total_rows < MAX_ROWS)
      row_starts[total_rows++] = i + 1;
  }
}

void drawBuffer() {
  system("cls");
  printf("[CTRL+S] Save   [CTRL+Q] Quit\n\n");

  for (int i = 0; i < buf_len; i++) {
    putchar(buffer[i]);
  }

  int abs_pos = 0;
  if (cursor_y < total_rows) abs_pos = row_starts[cursor_y] + cursor_x;

  COORD pos;
  pos.X = cursor_x;
  pos.Y = cursor_y + 2;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void saveToFile() {
  FILE *f = fopen(filename, "w");
  if (!f) return;
  fwrite(buffer, 1, buf_len, f);
  fclose(f);
}

void loadFile(const char *fname) {
  FILE *f = fopen(fname, "r");
  if (!f) return;
  buf_len = fread(buffer, 1, BUF_SIZE - 1, f);
  buffer[buf_len] = '\0';
  fclose(f);
}

int get_line_length(int row) {
  if (row >= total_rows) return 0;
  int start = row_starts[row];
  int end = (row + 1 < total_rows) ? row_starts[row + 1] - 1 : buf_len;
  return end - start;
}

void insert_char(char c) {
  if (buf_len >= BUF_SIZE - 1) return;
  int insert_pos =
      (cursor_y < total_rows) ? row_starts[cursor_y] + cursor_x : buf_len;
  memmove(buffer + insert_pos + 1, buffer + insert_pos, buf_len - insert_pos);
  buffer[insert_pos] = c;
  buf_len++;
  recalculate_rows();
  if (c == '\n') {
    cursor_y++;
    cursor_x = 0;
  } else {
    cursor_x++;
  }
}

void delete_char() {
  if (cursor_y == 0 && cursor_x == 0) return;
  int delete_pos = row_starts[cursor_y] + cursor_x - 1;
  if (delete_pos < 0 || delete_pos >= buf_len) return;
  memmove(buffer + delete_pos, buffer + delete_pos + 1,
          buf_len - delete_pos - 1);
  buf_len--;
  cursor_x--;
  if (cursor_x < 0 && cursor_y > 0) {
    cursor_y--;
    cursor_x = get_line_length(cursor_y);
  }
  recalculate_rows();
}

int main(int argc, char *argv[]) {
  if (argc >= 2) {
    strncpy(filename, argv[1], sizeof(filename) - 1);
    loadFile(filename);
  }

  recalculate_rows();

  while (1) {
    drawBuffer();
    int c = getch();

    if (c == 17)
      break;  // Ctrl+Q
    else if (c == 19)
      saveToFile();  // Ctrl+S
    else if (c == 224) {
      int dir = getch();
      if (dir == 72 && cursor_y > 0)
        cursor_y--;  // Up
      else if (dir == 80 && cursor_y + 1 < total_rows)
        cursor_y++;  // Down
      else if (dir == 75 && cursor_x > 0)
        cursor_x--;  // Left
      else if (dir == 77) {
        int len = get_line_length(cursor_y);
        if (cursor_x < len) cursor_x++;  // Right
      }
      int len = get_line_length(cursor_y);
      if (cursor_x > len) cursor_x = len;
    } else if (c == 8)
      delete_char();  // Backspace
    else if (c == '\r')
      insert_char('\n');
    else if (isprint(c))
      insert_char((char)c);
  }

  system("cls");
  return 0;
}
