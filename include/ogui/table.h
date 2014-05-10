/***************************************************************************
Copyright (c) 2013-2014, Amir Geva
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/
#ifndef H_OGUI_TABLE
#define H_OGUI_TABLE

#include <vector>
#include <ogui/text.h>

namespace OGUI {

/** Widget for multi-column table, with headers and a scrollbar
    each cell in the table can be practically any widget, though a default
    set_cell method exists to create TextWidgets
*/
class TableWidget : public StaticWidget
{
  typedef StaticWidget super;
  int m_Columns;
  typedef std::vector<widget_ptr>           table_row;
  typedef std::vector<table_row>            table;
  typedef std::vector<text_widget_ptr>      header_row;

  table                    m_Table;
  scroll_area_ptr          m_ContentArea;
  static_widget_ptr        m_Body;
  scroll_area_ptr          m_Header;
  scrollbar_widget_ptr     m_Scrollbar;
  unsigned                 m_HeaderColor;
  unsigned                 m_HeaderBGColor;
  bool                     m_UpdateContents;
  int                      m_SelectedRow;
  xstring                  m_ColumnWeights;
    
protected:
  TableWidget() 
  : m_Columns(1)
  , m_HeaderBGColor(get_skin_color(SKIN_COLOR_TABLE_HEADER_BG))
  , m_HeaderColor(get_skin_color(SKIN_COLOR_TABLE_HEADER_TEXT))
  , m_Header(ScrollAreaWidget::create())
  , m_Body(StaticWidget::create())
  , m_ContentArea(ScrollAreaWidget::create())
  , m_Scrollbar(ScrollbarWidget::create())
  , m_UpdateContents(true)
  , m_SelectedRow(-1)
  {
    m_ColumnWeights = "1";
    for (int i = 1; i < m_Columns; ++i) m_ColumnWeights += ",1";
    m_Header->set_layout(layout_ptr(new HorizontalLayout));
    m_Header->set_layout_preference(Point(LAYOUT_EXPAND,LAYOUT_TIGHT));
    m_Scrollbar->set_layout_preference(Point(LAYOUT_TIGHT,LAYOUT_EXPAND));
    m_Body->set_layout(layout_ptr(new HorizontalLayout));
    m_Body->add_child(m_ContentArea);
    m_Body->add_child(m_Scrollbar);
    m_ContentArea->set_vertical_scrollbar(m_Scrollbar);
    set_layout(layout_ptr(new VerticalLayout));
    add_child(m_Header);
    add_child(m_Body);
  }

  int get_widget_row_index(widget_ptr w) const
  {
    int i = 0;
    for (auto& row : m_Table)
    {
      for (auto cell : row)
      {
        if (cell == w) return i;
      }
      ++i;
    }
    return -1;
  }

  void set_invert_state(int row_index, bool state)
  {
    if (row_index >= 0 && row_index < int(m_Table.size()))
    {
      auto& row = m_Table[row_index];
      for (auto cell : row)
        StaticWidget::cast(cell)->set_inverted(state);
    }
  }
public:
  OGUI_DECLARE_WIDGET(TableWidget);

  virtual void redraw() override
  {
    if (m_UpdateContents) update_contents();
    super::redraw();
  }

  virtual bool draw(Image& target, const Rect& region) override
  {
    return super::draw(target,region);
  }

  /** Sets the number of columns */
  virtual void set_column_count(const int& cols) 
  { 
    m_Columns=cols; 
    for(auto& r : m_Table)
      r.resize(cols);
  }

  /** Sets the color of the text background in the header */
  virtual void set_header_bg_color(const unsigned& color)
  {
    m_HeaderBGColor=color;
    for(auto& h : *m_Header)
      TextWidget::cast(h)->set_bg_color(color);
  }

  /** Sets the color of the text in the header */
  virtual void set_header_color(const unsigned& color)
  {
    m_HeaderColor=color;
    for(auto& h : *m_Header)
      TextWidget::cast(h)->set_color(color);
  }

  /** Set the column names, by passing a comma delimited string with the names */
  virtual void set_column_names(const xstring& comma_delimited_names)
  {
    xstring_tokenizer st(comma_delimited_names,",");
    set_column_count(st.size());
    m_Header->clear_children();
    while (st.has_more_tokens())
    {
      text_widget_ptr tw=TextWidget::create(st.get_next_token());
      tw->set_bg_color(m_HeaderBGColor);
      tw->set_color(m_HeaderColor);
      m_Header->add_child(tw);
    }
  }

  /** Set the weight of each column, to calculate its relative width */
  virtual void  set_column_weights(const xstring& comma_delimited_weights)
  {
    m_ColumnWeights = comma_delimited_weights;
    xstring_tokenizer st(m_ColumnWeights, ",");
    for (auto it = m_Header->begin(); st.has_more_tokens() && it != m_Header->end(); ++it)
    {
      widget_ptr w = *it;
      float weight = float(st.get_next_token().as_double());
      w->set_layout_weight(weight);
    }
  }

  /** Insert a row to the table.  Default at the end, but can be before any existing row 
      Returns the index of the inserted row
  */
  virtual int insert_row(int before = -1)
  {
    if (before<0) before=m_Table.size();
    m_Table.insert(m_Table.begin()+before,table_row(m_Columns));
    m_UpdateContents=true;
    invalidate();
    return before;
  }

  /** Remove a row using its index */
  virtual void remove_row(int which)
  {
    if (which >= 0 && which < int(m_Table.size()))
    {
      m_Table.erase(m_Table.begin() + which);
      m_UpdateContents = true;
      invalidate();
    }
  }

  /** Overrides to avoid clearing internal structure.
      Instead, clears table data
  */
  virtual void clear_children() override
  {
    clear();
  }

  /** Clear all rows and cells */
  virtual void clear()
  {
    if (!m_Table.empty())
    {
      m_Table.clear();
      m_UpdateContents = true;
      m_SelectedRow = -1;
      invalidate();
    }
  }

  /** Return the widget in a specific cell */
  virtual widget_ptr get_cell(int row, int col)
  {
    if (row < 0 || row >= int(m_Table.size())) return widget_ptr();
    table_row& r = m_Table[row];
    if (col < 0 || col >= int(r.size())) return widget_ptr();
    return r[col];
  }

  /** Return the widget in a specific cell */
  virtual const widget_ptr get_cell(int row, int col) const
  {
    if (row < 0 || row >= int(m_Table.size())) return widget_ptr();
    const table_row& r = m_Table[row];
    if (col < 0 || col >= int(r.size())) return widget_ptr();
    return r[col];
  }

  /** Returns the text in a specific cell, assuming there's a TextWidget there */
  virtual const xstring& get_cell_text(int row, int col) const
  {
    const text_widget_ptr tw = TextWidget::cast(get_cell(row, col));
    return tw->get_text();
  }

  /** Set the widget in a specific cell to be a TextWidget this the given text*/
  virtual void set_cell(int row, int col, const xstring& text)
  {
    text_widget_ptr tw = TextWidget::create(text);
    tw->set_color(get_skin_color(SKIN_COLOR_TEXT));
    tw->set_bg_color(get_skin_color(SKIN_COLOR_DEFAULT_FILL));
    set_cell(row, col, tw);
  }

  /** Set the widget in a specific cell */
  virtual void set_cell(int row, int col, widget_ptr content)
  {
    if (row<0 || row>=int(m_Table.size())) return;
    table_row& r=m_Table[row];
    if (col<0 || col>=int(r.size())) return;
    r[col]=content;
    m_UpdateContents=true;
    invalidate();
  }

  /** Set the index of the currently selected row 
      Row cells will be inverted to indicate this, and a "select" event is raised
  */
  virtual void set_selected_row(int new_sel)
  {
    if (new_sel != m_SelectedRow)
    {
      set_invert_state(m_SelectedRow, false);
      set_invert_state(new_sel, true);
      m_SelectedRow = new_sel;
      raise_event("select", S(new_sel));
    }
  }

protected:
  virtual void contents_clicked(widget_ptr cell)
  {
    int new_sel = get_widget_row_index(cell);
    set_selected_row(new_sel);
  }

  virtual void update_contents()
  {
    m_UpdateContents = false;
    grid_layout_ptr layout(new GridLayout(m_Columns));
    layout->set_columns_weights(m_ColumnWeights);
    m_ContentArea->set_layout(layout);
    m_ContentArea->clear_children();
    for (auto& row : m_Table)
    {
      for (auto cell : row)
      {
        if (cell)
        {
          m_ContentArea->add_child(cell);
          cell->add_listener(get_name(), "clicked", [this, cell](const xstring& name, const xstring& event_type, const xstring& param)
          {
            contents_clicked(cell);
          });
        }
      }
    }
  }

};

typedef std::shared_ptr<TableWidget> table_widget_ptr;

} // namespace OGUI

#endif // H_OGUI_TABLE

