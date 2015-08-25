#include "filesystem.h"
#include "subvolume.h"
extern int snap_flag;
//#include "snapshot-scan.h"
GtkWidget *window_main;//主窗口
GtkWidget *box,*itemlist_box,*contents_box;//主容器，左边的列表容器，右边的显示区域容器
GtkWidget *menubar;//菜单条
GtkAccelGroup *accel_group;//快捷键集
GtkItemFactory *item_factory;//菜单项
GtkWidget *separator;//分割线
GtkWidget *label_title1,*label_title2;//两个标题栏
GtkWidget *panel;//分割面板
GtkWidget *view,*view1;//容纳列表的视图容器
GtkWidget *list;//列表
GtkWidget *list_item;//列表项
GtkWidget *scsub;//左侧滚动条

extern void subvolume_delete(GtkMenuItem *window,gpointer data);
extern void subvol_default_scan(GtkMenuItem *window,gpointer data);
extern void subvol_readonly_scan (GtkMenuItem *window,gpointer data);
extern void  subvolume_create(GtkMenuItem *window,gpointer data);
extern void  subvol_file_scan(GtkMenuItem *window,gpointer data);
extern void  snapshot_create(GtkMenuItem *window,gpointer data);
GdkColor color;
void destroy(GtkWidget *window,gpointer data);
//void scan_subvol(GtkMenuItem *window,gpointer data);
/*static void debug(GtkWidget *window,gpointer window_main){
	GtkWidget *dialog;
	dialog=gtk_message_dialog_new(window_main,
	GTK_DIALOG_DESTROY_WITH_PARENT,
	GTK_MESSAGE_INFO,
	GTK_BUTTONS_OK,
	"Warning Information!");
	gtk_window_set_title(GTK_WINDOW(dialog),"Warning!");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}*/

GtkItemFactoryEntry menu_items[] = {
	{ "/_Filesystem",         NULL,         NULL, 0, "<Branch>" },
	{ "/Filesystem/_Create Btrfs",     "<control>N", NULL, 0, "<StockItem>",GTK_STOCK_NEW},
	{ "/Filesystem/_Scan Filesystem",    "<control>S", scan_filesystem, 0,"<StockItem>",GTK_STOCK_FIND},
	{ "/Filesystem/_Check Btrfs",    "<control>C", NULL,0,"<StockItem>",GTK_STOCK_OPEN},
	{ "/Filesystem/_Version", NULL,         NULL, 0,"<StockItem>",GTK_STOCK_INFO},
	{ "/Filesystem/sep1",     NULL,         NULL, 0, "<Separator>" },
	{ "/Filesystem/_Exit",     "<control>Q", destroy, 0, "<StockItem>",GTK_STOCK_QUIT },
	{ "/_Subvolume",      NULL,         NULL, 0, "<Branch>" },
	{ "/Subvolume/_Scan Subvolume",  NULL,         NULL, 0, "<Branch>" },
	{ "/Subvolume/Scan Subvolume/default",	NULL, NULL ,	0,"<StockItem>",GTK_STOCK_FIND},	
	{ "/Subvolume/Scan Subvolume/readonly",	NULL, NULL ,0, "<StockItem>" ,GTK_STOCK_FIND},
	{ "/Subvolume/Modifiled files",	NULL,	NULL ,	0,	NULL},
	{ "/Subvolume/Create",  NULL,         subvolume_create, 0 , NULL },
	{ "/Subvolume/Delete",  NULL,         NULL, 0, NULL },
	{ "/_Snapshot",      NULL,         NULL, 0, "<Branch>" },
	{ "/Snapshot/Scan Snapshot",      NULL,     NULL, 0, NULL },
	{ "/Snapshot/Manage Snapshot",      NULL,         NULL, 0, NULL },
	{ "/Snapshot/Create",      NULL,         snapshot_create, 0, NULL },
	{ "/Snapshot/Delete",      NULL,         NULL, 0, NULL },
	{ "/_Help",         NULL,         NULL, 0, "<Branch>" },
	{ "/_Help/About",   NULL,         NULL, 0, NULL },
};

gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

void destroy(GtkWidget *window,gpointer data){
		gtk_main_quit();
}


int main(int argc, char *argv[]){	
	gtk_init(&argc, &argv);//主窗口初始化
	//snap_flag = 0;
	window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window_main),"btrfs_gui_utilities");
	gtk_window_set_default_size(GTK_WINDOW(window_main),800,500);
	gtk_window_set_position(GTK_WINDOW(window_main),GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window_main),10);	
	g_signal_connect(G_OBJECT(window_main),"destroy",G_CALLBACK(destroy),NULL);	
		
	gdk_color_parse("white",&color);//初始化颜色
	
	box = gtk_vbox_new(FALSE,2);//创建纵向box容器
	gtk_container_add(GTK_CONTAINER(window_main),box);
	gtk_widget_show(box);
	
	accel_group = gtk_accel_group_new();//创建菜单栏
	gtk_window_add_accel_group(GTK_WINDOW(window_main),accel_group);
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<main>",accel_group);
	gtk_item_factory_create_items(item_factory,nmenu_items,menu_items,NULL);
	gtk_window_add_accel_group(GTK_WINDOW(window_main),accel_group);
	menubar = gtk_item_factory_get_widget (item_factory,"<main>");
	gtk_box_pack_start(GTK_BOX(box),menubar,FALSE,FALSE,0);

	separator=gtk_hseparator_new();//创建分割线
	gtk_box_pack_start(GTK_BOX(box),separator,FALSE,FALSE,0);

	panel = gtk_hpaned_new();//创建分割面板
	gtk_box_pack_start(GTK_BOX(box),panel,TRUE,TRUE,5);

	itemlist_box=gtk_vbox_new(FALSE,0);//左侧分割面板添加纵向box容器,即列表容器
	gtk_paned_add1(GTK_PANED(panel),itemlist_box);
	
	label_title1=gtk_label_new("Item List");//左侧box容器添加label
	gtk_widget_set_size_request(label_title1,200,20);
	gtk_box_pack_start(GTK_BOX(itemlist_box),label_title1,FALSE,FALSE,0);

	view = gtk_viewport_new(NULL,NULL);//在左侧box中添加视图容器，并在视图容器中添加列表
	gtk_widget_set_size_request(view,200,400);
	gtk_box_pack_start(GTK_BOX(itemlist_box),view,FALSE,FALSE,0);//将视图容器添加至列表容器
	list = gtk_list_new();//新建列表
	gtk_list_set_selection_mode(GTK_LIST(list),GTK_SELECTION_SINGLE);
	gtk_container_add(GTK_CONTAINER(view),list);//将列表添加至视图容器中
	list_item=gtk_list_item_new_with_label("mount           disk           type");
	gtk_container_add(GTK_CONTAINER(list),list_item);
	list_item=gtk_list_item_new_with_label("/                 /dev/sda6        btrfs");
	gtk_container_add(GTK_CONTAINER(list),list_item);
	list_item=gtk_list_item_new_with_label("/home         /dev/sda6        btrfs");
	gtk_container_add(GTK_CONTAINER(list),list_item);
	list_item=gtk_list_item_new_with_label("/                 /dev/sda1        btrfs");
	gtk_container_add(GTK_CONTAINER(list),list_item);
	//gtk_signal_connect(GTK_OBJECT(list),"select-child",GTK_SIGNAL_FUNC(test),NULL);//为list item添加选中时出发的事件
	//gtk_signal_connect(GTK_OBJECT(list_item),"deselect",G_CALLBACK(test),NULL);

	contents_box=gtk_vbox_new(FALSE,0);//右侧分割面板添加纵向box容器
	gtk_paned_add2(GTK_PANED(panel),contents_box);
	
	
	label_title2 = gtk_label_new("contents");//右侧box容器添加label容器
	gtk_widget_set_size_request(label_title2,200,20);
	gtk_box_pack_start(GTK_BOX(contents_box),label_title2,FALSE,FALSE,0);
	gtk_widget_show_all(window_main);
	
	
	gtk_main();
	return 0;
}
