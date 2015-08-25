#include "filesystem.h"

GtkWidget *screen_view,*scwin;//一个文本显示窗口和一个滚动条窗口
GtkTextBuffer *buffer; //接收输入字符串的buffer
GtkTextIter start,end; //指向buffer的头部和尾部

void scan_filesystem(GtkMenuItem *item,gpointer data){
	gtk_widget_destroy(screen_view);
	gtk_widget_destroy(scwin);
	scwin = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(contents_box),scwin,TRUE,TRUE,5);
	screen_view = gtk_text_view_new();
	gtk_text_view_set_editable((GtkTextView *)screen_view,FALSE);
	gtk_text_view_set_cursor_visible((GtkTextView *)screen_view,FALSE);
	gtk_container_add(GTK_CONTAINER(scwin),screen_view);
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(screen_view));	;
	//cmd_show(0,NULL);
	g_print("hello");
	gtk_widget_show(scwin);
	gtk_widget_show(screen_view);
}
