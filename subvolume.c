#include "subvolume.h"
char *subvol_list_argv[2] = {
	" ","/"
}  ;
char *subvol_show_argv1[2] = {
	"-a","/"
};
  enum ListCols{  
        LIST_ID,  
        LIST_GEN,  
        LIST_LEVEL,
		LIST_PATH,
        LIST_TYPE,  
        LIST_CNT  
    };  
void subvol_create_handle(GtkWidget *widget,gpointer data){
	if(!strcmp(gtk_entry_get_text(GTK_ENTRY(text_dest_folder)), "") || !strcmp(gtk_entry_get_text(GTK_ENTRY(text_subvol_name)),"")){
		gtk_label_set_markup(GTK_LABEL(label_output),"<span font_desc='12'>CAUTION:check if dest_folder exists or subvol_name exists</span>");
		return ;
	}
	folder_subvol_dest = malloc(sizeof(char)*strlen(gtk_entry_get_text(GTK_ENTRY(text_dest_folder)))+128);//128为名字的有效个数
	strcpy(folder_subvol_dest,gtk_entry_get_text(GTK_ENTRY(text_dest_folder)));
	strcat(folder_subvol_dest,"/");
	strcat(folder_subvol_dest,gtk_entry_get_text(GTK_ENTRY(text_subvol_name)));
	//args3[0] = folder_subvol_dest;
	args3[1] = folder_subvol_dest;
	cmd_subvol_create(2,args3);
	//返回标记，用于判断是否正确
	free(folder_subvol_dest);
}
void subvol_details_handle(GtkTreeView *treeview,GtkTreePath *path,GtkTreeViewColumn *col,gpointer userdata){
	//GtkTreeModel *model;
	GtkTextBuffer *buffer = NULL;
	//GtkTreeIter iter;
	g_print("a row has been double clicked");
	cmd_subvol_show(2,subvol_show_argv1);
	/*
	*获得绝对路径，并显示具体子卷的信息
	*/
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_subvol_details));
	gtk_text_buffer_set_text(buffer,subvol_details_buffer,-1);
	g_print("handle over");
	/*if(gtk_tree_model_get_iter(model,&iter,path)){
		gchar *name;
		gtk_tree_model_get(model,&iter,0,&name,-1);
		g_print("double clicked row contains name %s\n",name);
		g_free(name);
	}*/
}
void select_dest_folder(GtkMenuItem *item,gpointer data){
	GtkWidget *folder;
	gtk_widget_destroy(folder);
	folder = gtk_file_chooser_dialog_new("Select Dest Path",NULL,GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
	if(gtk_dialog_run(GTK_DIALOG(folder)) == GTK_RESPONSE_ACCEPT){
		char *foldername = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder));
		gtk_entry_set_text(GTK_ENTRY(text_dest_subvol),foldername);
		gtk_widget_destroy(folder);
	}
	else
		gtk_widget_destroy(folder);
}
void subvol_create_dialog(GtkMenuItem *item,gpointer data){
	subvol_dialog = gtk_dialog_new_with_buttons("Create a new subvolume",
					(GtkWindow *)window_main,
					GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_ACCEPT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_REJECT,
					NULL);
	gtk_widget_set_size_request(subvol_dialog,460,300);
	gtk_widget_show_all(subvol_dialog);
	
	dest_subvol_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(dest_subvol_box,460,35);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(subvol_dialog)->vbox),dest_subvol_box,FALSE,FALSE,50);
	gtk_widget_show(dest_subvol_box);

	label_dest_subvol = gtk_label_new("dest_subvol");
	gtk_widget_set_size_request(label_dest_subvol,82,35);
	gtk_box_pack_start(GTK_BOX(dest_subvol_box),label_dest_subvol,FALSE,FALSE,30);
	gtk_widget_show(label_dest_subvol);

	text_dest_subvol = gtk_entry_new();
	gtk_widget_set_size_request(text_dest_subvol,150,35);
	gtk_box_pack_start(GTK_BOX(dest_subvol_box),text_dest_subvol,FALSE,FALSE,0);
	gtk_widget_show(text_dest_subvol);
	
	button_dest_browse = gtk_button_new_with_label("browse..");
	gtk_widget_set_size_request(button_dest_browse,60,35);
	gtk_box_pack_start(GTK_BOX(dest_subvol_box),button_dest_browse,FALSE,FALSE,0);
	gtk_widget_show(button_dest_browse);
	g_signal_connect(G_OBJECT(button_dest_browse),"clicked",G_CALLBACK(select_dest_folder),NULL);

	name_subvol_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(name_subvol_box,460,35);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(subvol_dialog)->vbox),name_subvol_box,FALSE,FALSE,0);
	gtk_widget_show(name_subvol_box);

	label_name_subvol = gtk_label_new("subvol_name");
	gtk_widget_set_size_request(label_name_subvol,82,35);
	gtk_box_pack_start(GTK_BOX(name_subvol_box),label_name_subvol,FALSE,FALSE,30);
	gtk_widget_show(label_name_subvol);

	text_name_subvol = gtk_entry_new();
	gtk_widget_set_size_request(text_name_subvol,220,35);
	gtk_box_pack_start(GTK_BOX(name_subvol_box),text_name_subvol,FALSE,FALSE,0);
	gtk_widget_show(text_name_subvol);
	result = gtk_dialog_run(GTK_DIALOG(subvol_dialog));
	switch(result){  
		case GTK_RESPONSE_OK:  
		/*
		*创建子卷
		*/
				subvol_create_handle();
            break;  
      case GTK_RESPONSE_CANCEL:  
				gtk_widget_destroy(subvol_dialog);
            g_print("cancel is press!\n");  
  
            break;  
	}
	
}

void subvol_folder_open(GtkMenuItem *item,gpointer data){
		system("xdg-open /home");
}
void subvolume_create(GtkMenuItem *item,gpointer data){		
	/*
	**删除整个中间显示面板
	*/
	g_print("subvolume create");
	gtk_widget_destroy(itemlist_box);
	gtk_widget_destroy(contents_box);
	gtk_widget_destroy(panel);
	gtk_widget_destroy(main_box);
		

	main_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(main_box,800,430);
	gtk_box_pack_start(GTK_BOX(box),main_box,FALSE,FALSE,0);
	gtk_widget_show(main_box);
	/*
	**操作按钮显示模块
	*/
	main_subvol_icon_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(main_subvol_icon_box,800,55);
	gtk_box_pack_start(GTK_BOX(main_box),main_subvol_icon_box,FALSE,FALSE,10);
	gtk_widget_show(main_subvol_icon_box);
	
	button_subvol_create = gtk_button_new();
	gtk_widget_set_size_request(button_subvol_create,55,50);
	subvol_icon_create = gtk_image_new_from_file("add.png");
    gtk_image_set_pixel_size((GtkImage *)subvol_icon_create,50);
	gtk_container_add(GTK_CONTAINER(button_subvol_create),subvol_icon_create);
	gtk_box_pack_start(GTK_BOX(main_subvol_icon_box),button_subvol_create,FALSE,FALSE,0);
	gtk_widget_show(subvol_icon_create);
	gtk_widget_show(button_subvol_create);
	g_signal_connect(G_OBJECT(button_subvol_create),"clicked",G_CALLBACK(subvol_create_dialog),NULL);

	button_subvol_open = gtk_button_new();
	gtk_widget_set_size_request(button_subvol_open,55,50);
	subvol_icon_open = gtk_image_new_from_file("open.png");
	gtk_container_add(GTK_CONTAINER(button_subvol_open),subvol_icon_open);
	gtk_box_pack_start(GTK_BOX(main_subvol_icon_box),button_subvol_open,FALSE,FALSE,0);
	gtk_widget_show(subvol_icon_open);
	gtk_widget_show(button_subvol_open);
	g_signal_connect(G_OBJECT(button_subvol_open),"clicked",G_CALLBACK(subvol_folder_open),NULL);

	button_subvol_delete = gtk_button_new();
	gtk_widget_set_size_request(button_subvol_delete,55,50);
	subvol_icon_delete = gtk_image_new_from_file("delete.png");
	gtk_container_add(GTK_CONTAINER(button_subvol_delete),subvol_icon_delete);
	gtk_box_pack_start(GTK_BOX(main_subvol_icon_box),button_subvol_delete,FALSE,FALSE,0);
	gtk_widget_show(subvol_icon_delete);
	gtk_widget_show(button_subvol_delete);

	button_subvol_change = gtk_button_new();
	subvol_icon_change  = gtk_image_new_from_file("change.png");
	gtk_container_add(GTK_CONTAINER(button_subvol_change),subvol_icon_change);
	gtk_box_pack_start(GTK_BOX(main_subvol_icon_box),button_subvol_change,FALSE,FALSE,0);
	gtk_widget_set_size_request(button_subvol_change,55,50);
	gtk_widget_show(subvol_icon_change);
	gtk_widget_show(button_subvol_change);
	/*
	**子卷信息显示模块
	*/
	main_subvol_info_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(main_subvol_info_box,800,200);
	gtk_box_pack_start(GTK_BOX(main_box),main_subvol_info_box,FALSE,FALSE,0);
	gtk_widget_show(main_subvol_info_box);

	subvol_info_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(subvol_info_scroll,800,200);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(subvol_info_scroll),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(main_subvol_info_box),subvol_info_scroll,TRUE,TRUE,5);
	gtk_widget_show(subvol_info_scroll);
	
	subvol_info_treeview = gtk_tree_view_new(); 
	subvol_info_list_store =(GtkWidget *) gtk_list_store_new(LIST_CNT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	gtk_tree_view_set_model((GtkTreeView *)subvol_info_treeview,(GtkTreeModel *)subvol_info_list_store);
	g_object_unref(subvol_info_list_store);

	subvol_info_render = gtk_cell_renderer_text_new();
	subvol_info_column = gtk_tree_view_column_new_with_attributes("id",subvol_info_render,"text",LIST_ID,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)subvol_info_column,120);
	gtk_tree_view_append_column((GtkTreeView *)subvol_info_treeview, subvol_info_column);

	subvol_info_render = gtk_cell_renderer_text_new();
	subvol_info_column = gtk_tree_view_column_new_with_attributes("gen",subvol_info_render,"text",LIST_GEN,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)subvol_info_column,120);
	gtk_tree_view_append_column((GtkTreeView *)subvol_info_treeview, subvol_info_column);

	subvol_info_render = gtk_cell_renderer_text_new();
	subvol_info_column = gtk_tree_view_column_new_with_attributes("level",subvol_info_render,"text",LIST_LEVEL,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)subvol_info_column,120);
	gtk_tree_view_append_column((GtkTreeView *)subvol_info_treeview, subvol_info_column);

	subvol_info_render = gtk_cell_renderer_text_new();
	subvol_info_column = gtk_tree_view_column_new_with_attributes("path",subvol_info_render,"text",LIST_PATH,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)subvol_info_column,120);
	gtk_tree_view_column_set_expand((GtkTreeViewColumn *)subvol_info_column,TRUE);
	gtk_tree_view_append_column((GtkTreeView *)subvol_info_treeview, subvol_info_column);

	subvol_info_render = gtk_cell_renderer_text_new();
	subvol_info_column = gtk_tree_view_column_new_with_attributes("type",subvol_info_render,"text",LIST_TYPE,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)subvol_info_column,120);
	gtk_tree_view_append_column((GtkTreeView *)subvol_info_treeview, subvol_info_column);
	gtk_container_add(GTK_CONTAINER(subvol_info_scroll),subvol_info_treeview);
	gtk_widget_show(subvol_info_treeview);
	/*
	**执行函数接口cmd_subvol_list
	*/	
	cmd_subvol_list(2,subvol_list_argv);

	/*
	*树视图响应
	*/
 	selection = (GtkWidget*)gtk_tree_view_get_selection((GtkTreeView *)subvol_info_treeview);  
   gtk_tree_selection_set_mode((GtkTreeSelection*)selection, GTK_SELECTION_SINGLE);  
   g_signal_connect(G_OBJECT(subvol_info_treeview), "row-activated",G_CALLBACK(subvol_details_handle), NULL);  
	/*
	**子卷细节显示模块
	*/
	main_subvol_details_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(main_subvol_details_box,800,130);
	gtk_box_pack_start(GTK_BOX(main_box),main_subvol_details_box,FALSE,FALSE,0);
	gtk_widget_show(main_subvol_details_box);
		
	details_title_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(details_title_box,800,20);
	gtk_box_pack_start(GTK_BOX(main_subvol_details_box),details_title_box,FALSE,FALSE,0);
	gtk_widget_show(details_title_box);

	label_subvol_details_pic = gtk_image_new_from_file("arrow.png");
	gtk_box_pack_start(GTK_BOX(details_title_box),label_subvol_details_pic,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_details_pic);
	
	label_subvol_details_title = gtk_label_new("info");
	gtk_widget_set_size_request(label_subvol_details_title,30,20);
	gtk_box_pack_start(GTK_BOX(details_title_box),label_subvol_details_title,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_details_title);
	
	details_show_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(details_show_box,800,110);
	gtk_box_pack_start(GTK_BOX(main_subvol_details_box),details_show_box,FALSE,FALSE,0);
	gtk_widget_show(details_show_box);

	subvol_details_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(subvol_details_scroll,800,110);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(subvol_details_scroll),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(details_show_box),subvol_details_scroll,TRUE,TRUE,5);
	gtk_widget_show(subvol_details_scroll);

	text_subvol_details = gtk_text_view_new();
	gtk_widget_set_size_request(text_subvol_details,800,110);
	gtk_text_view_set_editable((GtkTextView *)text_subvol_details,FALSE);
	gtk_text_view_set_cursor_visible((GtkTextView *)screen_view,FALSE);
	gtk_container_add(GTK_CONTAINER(subvol_details_scroll),text_subvol_details);
	gtk_widget_show(text_subvol_details);
	/*
	**操作记录显示模块
	*/
	main_subvol_log_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(main_subvol_log_box,800,20);
	gtk_box_pack_start(GTK_BOX(main_box),main_subvol_log_box,FALSE,FALSE,0);
	gtk_widget_show(main_subvol_log_box);
	
	label_subvol_log = gtk_label_new("create .snapshot ...");
	gtk_widget_set_size_request(label_subvol_log,100,20);
	gtk_label_set_justify(GTK_LABEL(label_subvol_log),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(main_subvol_log_box),label_subvol_log,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_log);
}
