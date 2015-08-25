#include "snapshot-scan.h"
    enum ListCols{  
        LIST_ID,  
        LIST_DATE,  
        LIST_LEVEL,
		  LIST_PATH,
        LIST_DESC,  
        LIST_CNT  
    };  
void snapshot_create_dialog(GtkMenuItem *item,gpointer data){
	snapshot_dialog = gtk_dialog_new_with_buttons("Create a new snapshot",
					(GtkWindow *)window_main,
					GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_STOCK_OK,
					GTK_RESPONSE_ACCEPT,
					GTK_STOCK_CANCEL,
					GTK_RESPONSE_REJECT,
					NULL);
	gtk_widget_set_size_request(snapshot_dialog,460,300);
	gtk_widget_show_all(snapshot_dialog);
	
	basep_snap_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(basep_snap_box,460,35);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(snapshot_dialog)->vbox),basep_snap_box,FALSE,FALSE,32);
	gtk_widget_show(basep_snap_box);

	label_basep_snap = gtk_label_new("based point");
	gtk_widget_set_size_request(label_basep_snap,82,32);
	gtk_box_pack_start(GTK_BOX(basep_snap_box),label_basep_snap,FALSE,FALSE,30);
	gtk_widget_show(label_basep_snap);

	combo_basep_snap = gtk_combo_box_new_text();
	gtk_widget_set_size_request(combo_basep_snap,120,30);
  	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_basep_snap), "/");
  	gtk_combo_box_append_text(GTK_COMBO_BOX(combo_basep_snap), "/home");
	gtk_box_pack_start(GTK_BOX(basep_snap_box),combo_basep_snap, TRUE, FALSE, 0);
	gtk_widget_show(combo_basep_snap);

	desp_snap_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(desp_snap_box,460,32);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(snapshot_dialog)->vbox),desp_snap_box,FALSE,FALSE,0);
	gtk_widget_show(desp_snap_box);

	label_desp_snap = gtk_label_new("description");
	gtk_widget_set_size_request(label_desp_snap,82,32);
	gtk_box_pack_start(GTK_BOX(desp_snap_box),label_desp_snap,FALSE,FALSE,30);
	gtk_widget_show(label_desp_snap);

	text_desp_snap = gtk_entry_new();
	gtk_widget_set_size_request(text_desp_snap,220,32);
	gtk_box_pack_start(GTK_BOX(desp_snap_box),text_desp_snap,FALSE,FALSE,0);
	gtk_widget_show(text_desp_snap);

	name_snap_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(name_snap_box,460,32);
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(snapshot_dialog)->vbox),name_snap_box,FALSE,FALSE,32);
	gtk_widget_show(name_snap_box);

	label_name_snap = gtk_label_new("dest_name");
	gtk_widget_set_size_request(label_name_snap,82,32);
	gtk_box_pack_start(GTK_BOX(name_snap_box),label_name_snap,FALSE,FALSE,30);
	gtk_widget_show(label_name_snap);

	text_name_snap = gtk_entry_new();
	gtk_widget_set_size_request(text_name_snap,220,32);
	gtk_box_pack_start(GTK_BOX(name_snap_box),text_name_snap,FALSE,FALSE,0);
	gtk_widget_show(text_name_snap);


	result = gtk_dialog_run(GTK_DIALOG(snapshot_dialog));
	switch(result){  
		case GTK_RESPONSE_OK:  
				g_print("点击成功");
            break;  
      case GTK_RESPONSE_CANCEL:  
				gtk_widget_destroy(snapshot_dialog);
            g_print("cancel is press!\n");  
            break;  
	}
	
}
void snapshot_create(GtkMenuItem *item,gpointer data){
	/*
	**删除整个中间显示面板
	*/
	g_print("snapshotume create");
	gtk_widget_destroy(itemlist_box);
	gtk_widget_destroy(contents_box);
	gtk_widget_destroy(main_box);
		
	main_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(main_box,800,430);
	gtk_box_pack_start(GTK_BOX(box),main_box,FALSE,FALSE,0);
	gtk_widget_show(main_box);
	/*
	**操作按钮显示模块
	*/
	main_snapshot_icon_box = gtk_hbox_new(FALSE,5);
	gtk_widget_set_size_request(main_snapshot_icon_box,800,55);
	gtk_box_pack_start(GTK_BOX(main_box),main_snapshot_icon_box,FALSE,FALSE,10);
	gtk_widget_show(main_snapshot_icon_box);
	
	button_snapshot_create = gtk_button_new();
	gtk_widget_set_size_request(button_snapshot_create,55,50);
	snapshot_icon_create = gtk_image_new_from_file("add.png");
   gtk_image_set_pixel_size((GtkImage *)snapshot_icon_create,50);
	gtk_container_add(GTK_CONTAINER(button_snapshot_create),snapshot_icon_create);
	gtk_box_pack_start(GTK_BOX(main_snapshot_icon_box),button_snapshot_create,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(button_snapshot_create),"clicked",G_CALLBACK(snapshot_create_dialog),NULL);
	gtk_widget_show(snapshot_icon_create);
	gtk_widget_show(button_snapshot_create);

	button_snapshot_open = gtk_button_new();
	gtk_widget_set_size_request(button_snapshot_open,55,50);
	snapshot_icon_open = gtk_image_new_from_file("open.png");
	gtk_container_add(GTK_CONTAINER(button_snapshot_open),snapshot_icon_open);
	gtk_box_pack_start(GTK_BOX(main_snapshot_icon_box),button_snapshot_open,FALSE,FALSE,0);
	gtk_widget_show(snapshot_icon_open);
	gtk_widget_show(button_snapshot_open);

	button_snapshot_delete = gtk_button_new();
	gtk_widget_set_size_request(button_snapshot_delete,55,50);
	snapshot_icon_delete = gtk_image_new_from_file("delete.png");
	gtk_container_add(GTK_CONTAINER(button_snapshot_delete),snapshot_icon_delete);
	gtk_box_pack_start(GTK_BOX(main_snapshot_icon_box),button_snapshot_delete,FALSE,FALSE,0);
	gtk_widget_show(snapshot_icon_delete);
	gtk_widget_show(button_snapshot_delete);

	button_snapshot_change = gtk_button_new();
	snapshot_icon_change  = gtk_image_new_from_file("change.png");
	gtk_container_add(GTK_CONTAINER(button_snapshot_change),snapshot_icon_change);
	gtk_box_pack_start(GTK_BOX(main_snapshot_icon_box),button_snapshot_change,FALSE,FALSE,0);
	gtk_widget_set_size_request(button_snapshot_change,55,50);
	gtk_widget_show(snapshot_icon_change);
	gtk_widget_show(button_snapshot_change);
	/*
	**子卷信息显示模块
	*/
	main_snapshot_info_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(main_snapshot_info_box,800,200);
	gtk_box_pack_start(GTK_BOX(main_box),main_snapshot_info_box,FALSE,FALSE,0);
	gtk_widget_show(main_snapshot_info_box);

	snapshot_info_treeview = gtk_tree_view_new(); 
	snapshot_info_list_store =(GtkWidget *) gtk_list_store_new(LIST_CNT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	gtk_list_store_append((GtkListStore *)snapshot_info_list_store,&snapshot_iter);
	gtk_list_store_set(( GtkListStore *)snapshot_info_list_store,&snapshot_iter,LIST_ID,"1",LIST_DATE,"2015.8.15 09.25",LIST_LEVEL,"5",LIST_PATH,"/home/",LIST_DESC,"snapshot",-1);
	gtk_tree_view_set_model((GtkTreeView *)snapshot_info_treeview,(GtkTreeModel *)snapshot_info_list_store);
	g_object_unref(snapshot_info_list_store);

	snapshot_info_render = gtk_cell_renderer_text_new();
	snapshot_info_column = gtk_tree_view_column_new_with_attributes("Id",snapshot_info_render,"text",LIST_ID,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)snapshot_info_column,120);
	snapshot_info_column = gtk_tree_view_append_column((GtkTreeView *)snapshot_info_treeview, snapshot_info_column);

	snapshot_info_render = gtk_cell_renderer_text_new();
	snapshot_info_column = gtk_tree_view_column_new_with_attributes("Date",snapshot_info_render,"text",LIST_DATE,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)snapshot_info_column,120);
	gtk_tree_view_column_set_expand((GtkTreeViewColumn *)snapshot_info_column,TRUE);
	snapshot_info_column = gtk_tree_view_append_column((GtkTreeView *)snapshot_info_treeview, snapshot_info_column);

	snapshot_info_render = gtk_cell_renderer_text_new();
	snapshot_info_column = gtk_tree_view_column_new_with_attributes("Type",snapshot_info_render,"text",LIST_LEVEL,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)snapshot_info_column,120);
	snapshot_info_column = gtk_tree_view_append_column((GtkTreeView *)snapshot_info_treeview, snapshot_info_column);

	snapshot_info_render = gtk_cell_renderer_text_new();
	snapshot_info_column = gtk_tree_view_column_new_with_attributes("Path",snapshot_info_render,"text",LIST_PATH,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)snapshot_info_column,120);
	gtk_tree_view_column_set_expand((GtkTreeViewColumn *)snapshot_info_column,TRUE);
	snapshot_info_column = gtk_tree_view_append_column((GtkTreeView *)snapshot_info_treeview, snapshot_info_column);

	snapshot_info_render = gtk_cell_renderer_text_new();
	snapshot_info_column = gtk_tree_view_column_new_with_attributes("Desciption",snapshot_info_render,"text",LIST_DESC,NULL);
	gtk_tree_view_column_set_min_width((GtkTreeViewColumn *)snapshot_info_column,120);
	snapshot_info_column = gtk_tree_view_append_column((GtkTreeView *)snapshot_info_treeview, snapshot_info_column);
	gtk_box_pack_start(GTK_BOX(main_snapshot_info_box),snapshot_info_treeview,TRUE,TRUE,1);
	gtk_widget_show(snapshot_info_treeview);
	/*
	**子卷细节显示模块
	*/
	main_snapshot_details_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(main_snapshot_details_box,800,130);
	gtk_box_pack_start(GTK_BOX(main_box),main_snapshot_details_box,FALSE,FALSE,0);
	gtk_widget_show(main_snapshot_details_box);
		
	details_title_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(details_title_box,800,20);
	gtk_box_pack_start(GTK_BOX(main_snapshot_details_box),details_title_box,FALSE,FALSE,0);
	gtk_widget_show(details_title_box);

	label_snapshot_details_pic = gtk_image_new_from_file("arrow.png");
	gtk_box_pack_start(GTK_BOX(details_title_box),label_snapshot_details_pic,FALSE,FALSE,0);
	gtk_widget_show(label_snapshot_details_pic);
	
	label_snapshot_details_title = gtk_label_new("info");
	gtk_widget_set_size_request(label_snapshot_details_title,30,20);
	gtk_box_pack_start(GTK_BOX(details_title_box),label_snapshot_details_title,FALSE,FALSE,0);
	gtk_widget_show(label_snapshot_details_title);
	
	details_show_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(details_show_box,800,110);
	gtk_box_pack_start(GTK_BOX(main_snapshot_details_box),details_show_box,FALSE,FALSE,0);
	gtk_widget_show(details_show_box);

	snapshot_details_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(snapshot_details_scroll,800,110);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(snapshot_details_scroll),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(details_show_box),snapshot_details_scroll,TRUE,TRUE,5);
	gtk_widget_show(snapshot_details_scroll);

	text_snapshot_details = gtk_text_view_new();
	gtk_widget_set_size_request(text_snapshot_details,800,110);
	gtk_text_view_set_editable((GtkTextView *)text_snapshot_details,FALSE);
	/*gtk_text_view_set_cursor_visible((GtkTextView *)screen_view,FALSE);*/
	gtk_container_add(GTK_CONTAINER(snapshot_details_scroll),text_snapshot_details);
	gtk_widget_show(text_snapshot_details);
	/*
	**操作记录显示模块
	*/
	main_snapshot_log_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(main_snapshot_log_box,800,20);
	gtk_box_pack_start(GTK_BOX(main_box),main_snapshot_log_box,FALSE,FALSE,0);
	gtk_widget_show(main_snapshot_log_box);
	
	label_snapshot_log = gtk_label_new("create .snapshot ...");
	gtk_widget_set_size_request(label_snapshot_log,100,20);
	gtk_label_set_justify(GTK_LABEL(label_snapshot_log),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(main_snapshot_log_box),label_snapshot_log,FALSE,FALSE,0);
	gtk_widget_show(label_snapshot_log);
}
