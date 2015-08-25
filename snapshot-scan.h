#ifndef SNAPSHOT_SCAN_H
#define SNAPSHOT_SCAN_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#define ACTIVE_SIZE 127
/*************************************************************************************/
/*                                                                          全局使用                                                                                                   */
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

/*struct snapshot_list_def{
	char id[6];
	char gen[30];
	char level[5];
	char path[20];
};
extern struct snapshot_list_def list_def[127];*/
extern char list_def_id[ACTIVE_SIZE][6];
extern char list_def_gen[ACTIVE_SIZE][30];
extern char list_def_level[ACTIVE_SIZE][5];
extern char list_def_path[ACTIVE_SIZE][200];
GtkWidget *left_snapshot_box,*right_snapshot_box;
GtkWidget *file_change_pack_box;
GdkColor color;
int file_change_num;
char file_change_info[ACTIVE_SIZE][256];
extern GtkWidget *label_file_change_info[ACTIVE_SIZE];//显示最近修改文件的标签
/*
**子卷的主界面布局
*/
extern GtkWidget *main_box;
GtkWidget *main_box;


GtkWidget *main_box;
GtkWidget *main_snapshot_icon_box;
GtkWidget *snapshot_icon_create;
GtkWidget *snapshot_dialog;
GtkWidget *snapshot_dialog;
GtkWidget *basep_snap_box;
GtkWidget *label_basep_snap;
GtkWidget *combo_basep_snap;
GtkWidget *desp_snap_box;
GtkWidget *label_desp_snap;
GtkWidget *text_desp_snap;
GtkWidget *name_snap_box;
GtkWidget *label_name_snap;
GtkWidget *text_name_snap;
GtkWidget *snapshot_dialog_box;
gint result;

GtkWidget *snapshot_icon_open;
GtkWidget *snapshot_icon_delete;
GtkWidget *snapshot_icon_change;
GtkWidget *button_snapshot_create;
GtkWidget *button_snapshot_open;
GtkWidget *button_snapshot_delete;
GtkWidget *button_snapshot_change;

GtkWidget *main_snapshot_info_box;
GtkWidget *snapshot_info_scroll_window;
GtkWidget *snapshot_info_treeview;
GtkWidget *snapshot_info_list_store;
GtkTreeIter snapshot_iter;
GtkCellRenderer* snapshot_info_render;  
GtkTreeViewColumn * snapshot_info_column;

GtkWidget *main_snapshot_details_box;
GtkWidget *details_title_box;
GtkWidget *label_snapshot_details_pic;
GtkWidget *label_snapshot_details_title;
GtkWidget *details_show_box;
GtkWidget *snapshot_details_scroll;
GtkWidget *text_snapshot_details;

GtkWidget *main_snapshot_log_box;
GtkWidget *label_snapshot_log;


#endif
