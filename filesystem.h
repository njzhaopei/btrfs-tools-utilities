#ifndef FILESYSTEM
#define FILESYSTEM
#include <gtk/gtk.h>
#include <stdio.h>
extern GtkWidget *window_main;//主窗口
extern GtkWidget *label_title1,*label_title2,*screen_view,*scwin;//两个标题栏、一个文本显示区域和一个滚动条窗口
extern GtkAccelGroup *accel_group;//快捷键集
extern GtkWidget *box,*itemlist_box,*contents_box;//主容器，左边的列表容器，右边的显示区域容器
extern GtkWidget *menubar;
extern GtkWidget *panel;//分割面板
extern GtkWidget *separator;//分割线
extern GtkItemFactory *item_factory;
extern GtkWidget *view;//容纳列表的视图容器
extern GtkWidget *list;//列表
extern GtkWidget *list_item;//列表项
extern GtkWidget *test_button;//用于测试重绘窗口控件的功能
extern GtkTextBuffer *buffer;//GTK text view buffer 缓冲区
extern GtkTextIter start,end;
extern int cmd_show(int argc, char **argv);
extern void scan_filesystem(GtkMenuItem *item,gpointer data);
#endif
