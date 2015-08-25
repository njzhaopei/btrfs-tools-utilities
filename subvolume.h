#ifndef SUBVOLUME_H
#define SUBVOLUME_H
#define ACTIVE_SIZE 127
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/*struct subvol_list_def{
	char id[6];
	char gen[30];
	char level[5];
	char path[20];
};
extern struct subvol_list_def list_def[127];*/
GtkWidget *left_subvol_box,*right_subvol_box;
GtkWidget *file_change_pack_box;
GdkColor color;
int file_change_num;
char file_change_info[ACTIVE_SIZE][256];
extern GtkWidget *label_file_change_info[ACTIVE_SIZE];//显示最近修改文件的标签
/*
**子卷的主界面布局
*/
GtkWidget *main_box;
GtkWidget *main_subvol_icon_box;
GtkWidget *subvol_icon_create;
GtkWidget *subvol_icon_open;
GtkWidget *subvol_icon_delete;
GtkWidget *subvol_icon_change;
GtkWidget *button_subvol_create;
GtkWidget *subvol_dialog;
GtkWidget *subvol_dialog_box;
GtkWidget *dest_subvol_box;
GtkWidget *label_dest_subvol;
GtkWidget *text_dest_subvol;
GtkWidget *button_dest_browse;
GtkWidget *name_subvol_box;
GtkWidget *label_name_subvol;
GtkWidget *text_name_subvol;
gint result;

GtkWidget *button_subvol_open;
GtkWidget *button_subvol_delete;
GtkWidget *button_subvol_change;

GtkWidget *main_subvol_info_box;
GtkWidget *subvol_info_scroll;
GtkWidget *subvol_info_treeview;
GtkWidget *selection; 
GtkWidget *subvol_info_list_store;
GtkTreeIter subvol_iter;
GtkCellRenderer* subvol_info_render;  
GtkTreeViewColumn * subvol_info_column;

GtkWidget *main_subvol_details_box;
GtkWidget *details_title_box;
GtkWidget *label_subvol_details_pic;
GtkWidget *label_subvol_details_title;
GtkWidget *details_show_box;
GtkWidget *subvol_details_scroll;
GtkWidget *text_subvol_details;

GtkWidget *main_subvol_log_box;
GtkWidget *label_subvol_log;
/*************************************************************************************/
/*                                                                      创建子卷                                                                                                   */
GtkWidget *label_output;//用于错误输出
GtkWidget *label_dest_folder;//目标子卷
GtkWidget *label_subvol_name;//目的子卷名
GtkWidget *text_dest_folder;//目标子卷的输入框
GtkWidget *text_subvol_name;//目标子卷的
GtkWidget *dest_folder_box;//用于目的文件夹的布局
GtkWidget *dest_pack_box;
GtkWidget *name_pack_box;
GtkWidget *subvol_name_box;//用于子卷名的布局
GtkWidget *label_subvol_create_title;//创建子卷的标题栏
GtkWidget *subvol_create_pack_box;  //包裹创建盒子
GtkWidget *button_subvol_create_box;//子卷创建按钮和输出状态的盒子
GtkWidget *button_subvol_create;//子卷的创建按钮
GtkWidget *subvol_create_box;//子卷创建的面版
GtkWidget *frame_main_box; //子卷创建面板的主盒子
GtkWidget *align_frame;//排列组建
GtkWidget *button_choose_folder;//目录选择按钮
GtkWidget *dialog;//对话框
GtkWidget *folder;
gchar *foldername;//文件目录名
gchar *folder_subvol_dest;//目的子卷路径

/*************************************************************************************/
/*                                                                            删除子卷                                                                                                   */
GtkWidget *table_subvol_delete;
GtkWidget *scroll_subvol_delete;
GtkWidget *label_subvol_delete_title;
//GtkWidget * button_subvol_delete[ACTIVE_SIZE];
GtkWidget *label_subvol_info[ACTIVE_SIZE][ACTIVE_SIZE];
GtkWidget *subvol_delete_box;
GtkWidget *subvol_delete_back_box;
GtkWidget *viewport_subvol_box;
char subvol_full_path[ACTIVE_SIZE];

/*************************************************************************************/
/*                                                                           扫描子卷                                                                                                  */
/*    scan subvolume            */
GtkWidget *subvol_item_box;//左侧子卷列表容器
//GtkWidget *view_subvol_scan_box;
GtkWidget *label_subvol_item_title;
GtkWidget *label_subvol_info_title;
GtkWidget *table_subvol_items_scan;
GtkWidget *table_subvol_info_show;
GtkWidget *item_subvol_list[ACTIVE_SIZE][ACTIVE_SIZE];//左侧列表的标签
GtkWidget *label_subvol_tag[12];//右侧主标签名
GtkWidget *label_subvol_contents[12];//右侧列表的标签
GtkWidget *button_subvol_info_show[ACTIVE_SIZE];
GtkWidget *subvol_details_box;//右侧子卷容器
GtkWidget *button_file_change_show[ACTIVE_SIZE];
GtkWidget *label_file_change_title; 
GtkWidget *file_change_box;
GtkWidget *table_file_change;
GtkWidget *scroll_file_change;//滚动条
GtkWidget *label_file_change_info[ACTIVE_SIZE];//显示最近修改文件的标签
GtkWidget *scroll_subvol_list;//列出子卷
 extern int subvol_list_num;

char *needed_path[ACTIVE_SIZE];

/*************************************************************************************/
/*                                                                            外部函数接口                                                                                           */
extern int cmd_subvol_show(int argc,char **argv);
extern int cmd_subvol_list(int argc,char **argv);
extern int cmd_subvol_create(int argc,char **argv);
extern int cmd_subvol_delete(int argc,char ** argv);
extern int cmd_find_new(int argc, char **argv);
extern int subvol_index;
extern char subvol_details_buffer[1024];
#endif
