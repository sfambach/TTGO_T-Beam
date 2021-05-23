/*********************************************************
   Table for oled Displays



   Currently tested with
   TTGO Lora32 Oled

   Created by SteFam http://www.fambach.net
   GPL2 V3

*/
#ifndef OLED_TABLE_H
#define OLED_TABLE_H


/*  SSD1306 */
#include <SSD1306.h>

#define OK 0
#define ERROR_WRONG_COL -1
#define ERROR_WRONG_ROW -2
#define ERROR_TEXT_TO_LONG -3 // currently not used

class OledTable {
  private:
    uint8_t _rows;
    uint8_t _cols;
    int _colWidth;
    int _rowHeight;
    bool _drawFrame;
    SSD1306* _display;
    OLEDDISPLAY_COLOR  _bgColor = WHITE;
    OLEDDISPLAY_COLOR  _fgColor = BLACK;

  public:

    /**
       Constructor
    */
    OledTable(SSD1306* display, uint8_t rows, uint8_t cols, bool drawFrame = true)
      : _display(display), _rows(rows), _cols(cols), _drawFrame(drawFrame) {


    }

    /**
        init the table, call this function during the setup
    */
    void init() {

      int w = _display->getWidth();
      int h = _display->getHeight();

      _colWidth  = w / _cols;
      _rowHeight = h / _rows;

    }

    /**
       draw the table, call this in the loop or each time when the content has changed.
    */
    void drawLines() {

      _display->clear();

      // draw the frame
      if (_drawFrame) {
        _display->drawRect(0, 0, _display->getWidth(), _display->getHeight());
      }

      // draw lines
      for (int i = 1; i < _rows; i++) {
        _display->drawHorizontalLine(0, i * _rowHeight , _display->getWidth());
      }

      for (int i = 1; i < _cols; i++) {
        _display->drawVerticalLine(_colWidth * i, 0, _display->getHeight());
      }
    }

    int setText(uint8_t row, uint8_t col, double value , bool fitToFrame = true) {
      return setText(row, col, String(value) , fitToFrame);
    }

    int setText(uint8_t row, uint8_t col, String text , bool fitToFrame = true) {

      if (row < 0 || row > _rows) {
        return ERROR_WRONG_ROW;
      }

      if (col < 0 || col > _cols) {
        return ERROR_WRONG_COL;
      }

      // clear field
      //_display->setColor(_bgColor );
      //_display->drawRect(_colWidth *(col)+1, _rowHeight*(row)+1,_colWidth *(col+1)-1, _rowHeight*(row+1)-1);

      if (fitToFrame) {
        _display->drawStringMaxWidth((_colWidth * (col)) + 3, (_rowHeight * (row)), (_colWidth) - 5 , text);
      } else {
        _display->drawString((_colWidth * (col)) + 3, (_rowHeight * (row)) , text);
      }

      return OK;
    }


    void refresh() {
      _display->display();
    }

    void clear() {
      _display->clear();
      drawLines();
    }



};

#endif // OLED_TABLE_H
