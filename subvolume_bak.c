#include "subvolume.h"
//
 char *args[2]={
		"-a","/"
};
 char *args1[2] = {	
	"show","/"
};
 char *args2[2] = {
	"-r","/"
};
 char *args3[2]={
	"",""
};
char *args4[2] = {
	"",""
};
 char *args5[3] = {
	"","",""
};

char *title[11] = {
	"Name :","uuid :","Parent_uid :","Creation time :","Object ID :","Generation(gen) :","Gen at creation :","Parent :","Top level :","Flags","Snapshot :"
};

char *path_to_full_path(char path_str[]){
	strcpy(subvol_full_path,"/");
	if(path_str[0] == '@'){
		strcat(subvol_full_path,path_str+1);
		return subvol_full_path;
	}
	strcat(subvol_full_path,path_str);
	return subvol_full_path;
}	
/*************************************************************************************/
/*                                                                           最近变动文件                                                                                             */
void subvol_file_change(GtkMenuItem *item,gpointer data){
	g_print("----------------subvol_file_change_show------------\n");
	gdk_color_parse("white",&color);
	args5[1] = path_to_full_path(list_def_path[GPOINTER_TO_INT(data)]);
	args5[2] = list_def_gen[GPOINTER_TO_INT(data)];
	cmd_find_new(3,args5);	
	
	gtk_widget_destroy(right_subvol_box);
	right_subvol_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(right_subvol_box,400,400);
	gtk_paned_add2(GTK_PANED(panel),right_subvol_box);
	gtk_widget_show(right_subvol_box);
	
	gtk_widget_set_size_request(left_subvol_box,600,400);
	label_file_change_title = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_file_change_title),"<span foreground='grey' font_desc='18'>recent file changes</span>");
	gtk_widget_set_size_request(label_file_change_title,200,40);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),label_file_change_title,FALSE,FALSE,0);
	gtk_widget_show(label_file_change_title);
	
	file_change_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(file_change_box,360,400);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),file_change_box,FALSE,FALSE,0);
	gtk_widget_show(file_change_box);

	/*gtk_widget_set_size_request(file_change_box,400,400);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),file_change_box,FALSE,FALSE,0);
	gtk_widget_modify_bg(file_change_box,GTK_STATE_NORMAL,&color);
	gtk_widget_show(file_change_box);*/

	scroll_file_change = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(scroll_file_change,400,200);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_file_change),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(file_change_box),scroll_file_change);
	gtk_widget_show(scroll_file_change);

	file_change_pack_box = gtk_event_box_new();
	gtk_widget_set_size_request(file_change_pack_box,360,400);
	gtk_widget_modify_bg(file_change_pack_box,GTK_STATE_NORMAL,&color);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll_file_change),file_change_pack_box);	
	gtk_widget_show(file_change_pack_box);
	
	table_file_change = gtk_table_new(6,file_change_num,TRUE);
	gtk_widget_set_size_request(table_file_change,400,400);
	gtk_container_add(GTK_CONTAINER(file_change_pack_box),table_file_change);
	gtk_widget_show(table_file_change);

	int i;
	for(i = 0; i< file_change_num ;i++){
			label_file_change_info[i] = gtk_label_new("");
			gtk_label_set_markup(GTK_LABEL(label_file_change_info[i]),file_change_info[i]);
			gtk_label_set_line_wrap(GTK_LABEL(label_file_change_info[i]),TRUE);
			gtk_widget_set_size_request(label_file_change_info[i],350,50);
			gtk_table_attach(GTK_TABLE(table_file_change),label_file_change_info[i],1,5,i,i+1,GTK_FILL,GTK_FILL,0,5);
			gtk_widget_show(label_file_change_info[i]);
	}
}

/*************************************************************************************/
/*                                                                            列出子卷                                                                                                   */
void subvol_details_list(GtkMenuItem *item,gpointer data){
	g_print("list subvolume details\n");	
	gtk_widget_destroy(right_subvol_box);
	//view1 = gtk_viewport_new(NULL,NULL);
	gtk_widget_set_size_request(left_subvol_box,500,400);
	right_subvol_box = gtk_vbox_new(FALSE,0);
	gtk_paned_add2(GTK_PANED(panel),right_subvol_box);
	gtk_widget_show(right_subvol_box);
	
	label_subvol_info_title = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_subvol_info_title),"<span foreground='grey' font_desc='18'>subvolume info</span>");
	gtk_widget_set_size_request(label_subvol_info_title,200,40);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),label_subvol_info_title,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_info_title);

	subvol_details_box = gtk_event_box_new();		
	gtk_box_pack_start(GTK_BOX(right_subvol_box),subvol_details_box,FALSE,FALSE,0);
	gtk_widget_modify_bg(subvol_details_box,GTK_STATE_NORMAL,&color);
	gtk_widget_show(subvol_details_box);

	table_subvol_info_show = gtk_table_new(8,6,FALSE);
	gtk_container_add(GTK_CONTAINER(subvol_details_box),table_subvol_info_show);
	gtk_widget_set_size_request(table_subvol_info_show,450,400);
	gtk_widget_show(table_subvol_info_show);
	int i;
	int pos = 0;
	for(i = 0;i < 11;i++){

		char *str_temp = g_strdup_printf("<span font_desc='11'>%s</span>",title[pos]);
		label_subvol_tag[i] = gtk_label_new("");
		gtk_label_set_markup(GTK_LABEL(label_subvol_tag[i]),str_temp);
		gtk_label_set_justify(GTK_LABEL(label_subvol_tag[i]),GTK_JUSTIFY_LEFT);
		gtk_widget_set_size_request(label_subvol_tag[i],120,30);
		label_subvol_contents[i] = gtk_label_new("");
		gtk_label_set_justify(GTK_LABEL(label_subvol_contents[i]),GTK_JUSTIFY_LEFT);
		gtk_widget_set_size_request(label_subvol_contents[i],280,30);
		gtk_table_attach(GTK_TABLE(table_subvol_info_show),label_subvol_tag[i],0,2,i,i+1,GTK_FILL,GTK_FILL,10,2);
		gtk_table_attach(GTK_TABLE(table_subvol_info_show),label_subvol_contents[i],2,5,i,i+1,GTK_EXPAND,GTK_EXPAND,10,2);
		pos++;
		gtk_widget_show(label_subvol_tag[i]);
		gtk_widget_show(label_subvol_contents[i]);
		g_free(str_temp);
	}
	g_print("need = %d\n",GPOINTER_TO_INT(data));
	args1[1] = needed_path[GPOINTER_TO_INT(data)];
	cmd_subvol_show(2,args1);
}
/*
 *		judge mode_code = 0  代表 subvol_default_scan
 *		judge mode_code = 1  代表 subvol_readonly_scan
 *		judge mode_code = 2  代表 subvol_file_sca
 */
void subvolume_list(int judge_mode_code){
	g_print("default subvolume");
	char subvol_scan_str[40]; 
	subvol_list_num = 1;
	gtk_widget_destroy(itemlist_box);
	gtk_widget_destroy(contents_box);
	gtk_widget_destroy(left_subvol_box);

	left_subvol_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(left_subvol_box,500,400);
	gtk_paned_add1(GTK_PANED(panel),left_subvol_box);
	gtk_widget_show(left_subvol_box);

	label_subvol_item_title = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_subvol_item_title),"<span foreground='grey' font_desc='18'>subvolume list</span>");
	gtk_widget_set_size_request(label_subvol_item_title,200,40);
	gtk_box_pack_start(GTK_BOX(left_subvol_box),label_subvol_item_title,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_item_title);


	scroll_subvol_list = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(scroll_subvol_list,400,400);
	gtk_box_pack_start(GTK_BOX(left_subvol_box),scroll_subvol_list,FALSE,FALSE,0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_subvol_list),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_widget_show(scroll_subvol_list);

	subvol_item_box = gtk_event_box_new();		
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll_subvol_list),subvol_item_box);
	gtk_widget_modify_bg(subvol_item_box,GTK_STATE_NORMAL,&color);
	gtk_widget_show(subvol_item_box);	
	/*view_subvol_scan_box = gtk_vbox_new(FALSE,5);
	gtk_container_add(GTK_CONTAINER(scroll_subvol_list),view_subvol_scan_box);
	gtk_widget_show(view_subvol_scan_box);*/


	/*label_subvol_info_title = gtk_label_new("subvolume info");
	gtk_widget_set_size_request(label_subvol_info_title,200,20);
	gtk_box_pack_start(GTK_BOX(view_subvol_scan_box),label_subvol_info_title,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_info_title);*/

	if(judge_mode_code == 0){
		cmd_subvol_list(2,args);
		strcpy(subvol_scan_str,"<span font_desc='12'>info</span>");
	}
	if(judge_mode_code == 1){
		cmd_subvol_list(2,args2);
		strcpy(subvol_scan_str,"<span font_desc='12'>info</span>");
	}
	if(judge_mode_code == 2){
		cmd_subvol_list(2,args);
		strcpy(subvol_scan_str,"<span font_desc='12'>operation</span>");
	}

	//table_subvol_items_scan = gtk_table_new(subvol_list_num/4,6,TRUE);
	table_subvol_items_scan = gtk_table_new(subvol_list_num/4+5,6,TRUE);
	gtk_container_add(GTK_CONTAINER(subvol_item_box),table_subvol_items_scan);
	gtk_widget_set_size_request(table_subvol_items_scan,400,400);
	gtk_widget_show(table_subvol_items_scan);
	int i;
	int j;
	g_print("subvol num is %d \n",subvol_list_num);
	for(i = 0; i < subvol_list_num/4+1 ;i++){
		for(j = 0;j <= 4;j++){
			item_subvol_list[i][j] = gtk_label_new("");
			gtk_widget_set_size_request(item_subvol_list[i][j],150,90);
			gtk_table_attach(GTK_TABLE(table_subvol_items_scan),item_subvol_list[i][j],j,j+1,i,i+1,GTK_FILL,GTK_FILL,0,5);
			//gtk_label_set_justify(GTK_LABEL(list_new[i][j]),GTK_JUSTIFY_LEFT);
			if(j == 3){
				gtk_label_set_line_wrap(GTK_LABEL(item_subvol_list[i][j]),TRUE);
			}
			gtk_widget_show(item_subvol_list[i][j]);
		}
	}	
	gtk_table_set_col_spacing(GTK_TABLE(table_subvol_items_scan),3,20);
	gtk_label_set_markup(GTK_LABEL(item_subvol_list[0][0]),"<span font_desc='12'>id</span>");	
	gtk_label_set_markup(GTK_LABEL(item_subvol_list[0][1]),"<span font_desc='12'>gen</span>");	
	gtk_label_set_markup(GTK_LABEL(item_subvol_list[0][2]),"<span font_desc='12'>level</span>");	
	gtk_label_set_markup(GTK_LABEL(item_subvol_list[0][3]),"<span font_desc='12'>path</span>");	
	gtk_label_set_markup(GTK_LABEL(item_subvol_list[0][4]),subvol_scan_str);	
	for(i = 1; i < subvol_list_num/4+1;i++){
			printf("//////////////////////%s,%s,%s,%s////////////////////\n",list_def_id[i-1],list_def_gen[i-1],list_def_level[i-1],list_def_path[i-1]);
			gtk_label_set_text(GTK_LABEL(item_subvol_list[i][0]),list_def_id[i-1]);
			gtk_label_set_text(GTK_LABEL(item_subvol_list[i][1]),list_def_gen[i-1]);
			gtk_label_set_text(GTK_LABEL(item_subvol_list[i][2]),list_def_level[i-1]);
			gtk_label_set_text(GTK_LABEL(item_subvol_list[i][3]),list_def_path[i-1]);
	}
	//初始化details按钮
	if(judge_mode_code == 0 || judge_mode_code == 1){
		for(i = 0; i < subvol_list_num/4;i++){
			button_subvol_info_show[i] = gtk_button_new_with_label("details");
			gtk_table_attach(GTK_TABLE(table_subvol_items_scan),button_subvol_info_show[i],4,5,i+1,i+2,GTK_EXPAND,GTK_EXPAND,0,5);
			g_signal_connect(G_OBJECT(button_subvol_info_show[i]),"clicked",G_CALLBACK(subvol_details_list),GINT_TO_POINTER(i));
			gtk_widget_show(button_subvol_info_show[i]);
		}
	}
	if(judge_mode_code == 2){
	//初始化最近变动文件按钮
		for(i = 0; i < subvol_list_num/4;i++){
			button_file_change_show[i] = gtk_button_new_with_label("file changes");
			gtk_table_attach(GTK_TABLE(table_subvol_items_scan),button_file_change_show[i],4,5,i+1,i+2,GTK_EXPAND,GTK_EXPAND,0,5);
			g_signal_connect(G_OBJECT(button_file_change_show[i]),"clicked",G_CALLBACK(subvol_file_change),GINT_TO_POINTER(i));
			gtk_widget_show(button_file_change_show[i]);
		}
	}
}
void subvol_default_scan(GtkMenuItem *window,gpointer data){
	printf("scan subvol default\n");
	subvolume_list(0);
}

void subvol_readonly_scan(GtkMenuItem *window,gpointer data){
	printf("scan subvol readonly\n");
	subvolume_list(1);
}
void subvol_file_scan(GtkMenuItem *window,gpointer data){
	printf("scan subvol file changes ");
	subvolume_list(2);
}
/*************************************************************************************/
/*                                                                            创建子卷                                                                                                   */
//选择目的文件夹
void print_foldername(GtkWidget *folder){
	foldername = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(folder));
	gtk_widget_destroy(folder);
	gtk_entry_set_text(GTK_ENTRY(text_dest_folder),foldername);
	/*dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,foldername);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);*/
}
void select_dest_folder(GtkWidget *widget,gpointer data){
	folder = gtk_file_chooser_dialog_new("Select Dest Path",NULL,GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OK,GTK_RESPONSE_ACCEPT,NULL);
	if(gtk_dialog_run(GTK_DIALOG(folder)) == GTK_RESPONSE_ACCEPT)
		print_foldername(folder);
	else
		gtk_widget_destroy(folder);
}
void handle_subvol_create(GtkWidget *widget,gpointer data){
	//做简单检查
	g_print("-----------handle subvolume create ---------------------\n");	
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

void subvolume_create(GtkMenuItem *item,gpointer data){
	//删除左侧面板
	g_print("subvolume create");
	gtk_widget_destroy(itemlist_box);
	gtk_widget_destroy(contents_box);
	gtk_widget_destroy(left_subvol_box);
	gtk_widget_destroy(right_subvol_box);
	gdk_color_parse("white",&color);
	
	right_subvol_box = gtk_vbox_new(FALSE,0);
	gtk_paned_add2(GTK_PANED(panel),right_subvol_box);
	gtk_widget_set_size_request(right_subvol_box,400,400);
	gtk_widget_show(right_subvol_box);

	label_subvol_create_title = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_subvol_create_title),"<span foreground='grey' font_desc='18'>subvolume create</span>");
	gtk_widget_set_size_request(label_subvol_create_title,200,40);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),label_subvol_create_title,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_create_title);
	
	
	subvol_create_box  = gtk_event_box_new();
	gtk_widget_modify_bg(subvol_create_box,GTK_STATE_NORMAL,&color);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),subvol_create_box,FALSE,FALSE,0);
	gtk_widget_show(subvol_create_box);

	frame_main_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(frame_main_box,800,400);
	gtk_container_add(GTK_CONTAINER(subvol_create_box),frame_main_box);
	gtk_widget_show(frame_main_box);
	
	subvol_create_pack_box = gtk_vbox_new(FALSE,20);
	gtk_box_pack_start(GTK_BOX(frame_main_box),subvol_create_pack_box,TRUE,FALSE,40);
	gtk_widget_show(subvol_create_pack_box);

	dest_pack_box = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(subvol_create_pack_box),dest_pack_box,FALSE,FALSE,0);
	gtk_widget_show(dest_pack_box);

	dest_folder_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(dest_folder_box,300,40);
	gtk_box_pack_start(GTK_BOX(dest_pack_box),dest_folder_box,TRUE,FALSE,0);
	gtk_widget_show(dest_folder_box);


	label_dest_folder = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_dest_folder),"<span font_desc='12'>desc_subvol</span>");
	gtk_widget_set_size_request(label_dest_folder,100,30);
	gtk_box_pack_start(GTK_BOX(dest_folder_box),label_dest_folder,FALSE,FALSE,0);
	gtk_widget_show(label_dest_folder);

	text_dest_folder = gtk_entry_new();
	gtk_widget_set_size_request(text_dest_folder,150,35);
	gtk_entry_set_editable(GTK_ENTRY(text_dest_folder),FALSE);
	gtk_box_pack_start(GTK_BOX(dest_folder_box),text_dest_folder,FALSE,FALSE,10);
	gtk_widget_show(text_dest_folder);
	
	//目录选择
	button_choose_folder = gtk_button_new_with_label("browse..");
	gtk_widget_set_size_request(button_choose_folder,60,25);
	gtk_box_pack_start(GTK_BOX(dest_folder_box),button_choose_folder,FALSE,FALSE,5);
	gtk_widget_show(button_choose_folder);
	g_signal_connect(G_OBJECT(button_choose_folder),"clicked",G_CALLBACK(select_dest_folder),NULL);

	name_pack_box = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(subvol_create_pack_box),name_pack_box,FALSE,FALSE,0);
	gtk_widget_show(name_pack_box);

	subvol_name_box = gtk_hbox_new(FALSE,0);
	gtk_widget_set_size_request(subvol_name_box,300,40);
	gtk_box_pack_start(GTK_BOX(name_pack_box),subvol_name_box,TRUE,FALSE,0);
	gtk_widget_show(subvol_name_box);
	
	label_subvol_name = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_subvol_name),"<span font_desc ='12'>subvol_name</span>");
	gtk_widget_set_size_request(label_subvol_name,100,30);
	gtk_label_set_justify(GTK_LABEL(label_subvol_name),GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(subvol_name_box),label_subvol_name,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_name);
	//gtk_container_add(GTK_CONTAINER(align_frame),subvol_name_box);
	
	
	text_subvol_name = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(subvol_name_box),text_subvol_name,FALSE,FALSE,0);
	gtk_widget_set_size_request(text_subvol_name,222,35);
	gtk_widget_show(text_subvol_name);
	
	button_subvol_create_box = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(subvol_create_pack_box),button_subvol_create_box,FALSE,FALSE,0);
	gtk_widget_show(button_subvol_create_box);

	button_subvol_create = gtk_button_new_with_label("create");
	gtk_widget_set_size_request(button_subvol_create,100,50);
	gtk_box_pack_start(GTK_BOX(button_subvol_create_box),button_subvol_create,TRUE,FALSE,0);
	gtk_widget_show(button_subvol_create);
	g_signal_connect(G_OBJECT(button_subvol_create),"clicked",G_CALLBACK(handle_subvol_create),NULL);

	label_output = gtk_label_new("");
	gtk_widget_set_size_request(label_output,200,30);
	gtk_box_pack_start(GTK_BOX(subvol_create_pack_box),label_output,FALSE,FALSE,10);
	gtk_widget_show(label_output);	

}
/*************************************************************************************/
/*                                                                            删除子卷                                                                                                   */
void handle_subvol_delete(GtkMenuItem *widget,gpointer data){
	g_print("handle subvol delete\n");
	//重新更新子卷数据
	/*int i;
	for(i = GPOINTER_TO_INT(data);i < subvol_list_num/4 + 1; i++){
		list_def[i-1] = list_def[i];
	}
	//重新绘制表格
	for(i = GPOINTER_TO_INT(data); i < subvol_list_num/4 +1; i++){
		if(i == GPOINTER_TO_INT(data)){
			gtk_widget_destroy(label_subvol_info[i][0]);
			gtk_widget_destroy(label_subvol_info[i][1]);
			gtk_widget_destroy(label_subvol_info[i][2]);
			gtk_widget_destroy(label_subvol_info[i][3]);
			gtk_widget_destroy(button_subvol_delete[i]);
		}
	}
	subvol_list_num = subvol_list_num - 4;*/
	gtk_widget_set_sensitive(button_subvol_delete[GPOINTER_TO_INT(data)],FALSE);
	args4[1] = path_to_full_path(list_def_path[GPOINTER_TO_INT(data)-1]);
	cmd_subvol_delete(2,args4);
}
void subvolume_delete(GtkMenuItem *window,gpointer data){
	g_print("subvolume delete \n");
	//gtk_widget_destroy(view);
	subvol_list_num  = 1;
	gtk_widget_destroy(itemlist_box);
	gtk_widget_destroy(contents_box);
	gtk_widget_destroy(right_subvol_box);
	gtk_widget_destroy(left_subvol_box);
	//gtk_widget_destroy(subvol_delete_box);
	//扫描子卷
	cmd_subvol_list(2,args);

	right_subvol_box = gtk_vbox_new(FALSE,0);
	gtk_widget_set_size_request(right_subvol_box,400,400);
	gtk_paned_add2(GTK_PANED(panel),right_subvol_box);
	gtk_widget_show(right_subvol_box);
	
	label_subvol_delete_title = gtk_label_new("");
	gtk_label_set_markup(GTK_LABEL(label_subvol_delete_title),"<span foreground='grey' font_desc='18'>subvolume delete</span>");
	gtk_widget_set_size_request(label_subvol_delete_title,200,40);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),label_subvol_delete_title,FALSE,FALSE,0);
	gtk_widget_show(label_subvol_delete_title);
	
	subvol_delete_back_box = gtk_event_box_new();
	gtk_widget_modify_bg(subvol_delete_back_box,GTK_STATE_NORMAL,&color);
	gtk_box_pack_start(GTK_BOX(right_subvol_box),subvol_delete_back_box,FALSE,FALSE,0);
	gtk_widget_show(subvol_delete_back_box);

	scroll_subvol_delete  = gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_subvol_delete),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request(scroll_subvol_delete,400,400);

	gtk_container_add(GTK_CONTAINER(subvol_delete_back_box),scroll_subvol_delete);
	gtk_widget_show(scroll_subvol_delete);

	subvol_delete_box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(scroll_subvol_delete),subvol_delete_box);
	gtk_widget_show(subvol_delete_box);

	table_subvol_delete = gtk_table_new(8,6,FALSE);
	//gtk_widget_set_size_request(table_subvol_delete,400,400);
	gtk_box_pack_start(GTK_BOX(subvol_delete_box),table_subvol_delete,FALSE,FALSE,0);
//	gtk_container_add(GTK_CONTAINER(subvol_delete_box),table_subvol_delete);
	gtk_widget_show(table_subvol_delete);



	int i;
	int j;
	for(i = 0; i < subvol_list_num/4+1;i++){
		for(j = 0; j < 4;j++){
			label_subvol_info[i][j] = gtk_label_new("");
			gtk_table_attach(GTK_TABLE(table_subvol_delete),label_subvol_info[i][j],j,j+1,i,i+1,GTK_EXPAND,GTK_EXPAND,0,5);
			gtk_widget_show(label_subvol_info[i][j]);
		}
	}
	gtk_table_set_col_spacing(GTK_TABLE(table_subvol_delete),3,5);
	gtk_label_set_markup(GTK_LABEL(label_subvol_info[0][0]),"<span font_desc='12'>id</span>");
	gtk_label_set_markup(GTK_LABEL(label_subvol_info[0][1]),"<span font_desc='12'>gen</span>");
	gtk_label_set_markup(GTK_LABEL(label_subvol_info[0][2]),"<span font_desc='12'>level</span>");
	gtk_label_set_markup(GTK_LABEL(label_subvol_info[0][3]),"<span font_desc='12'>path</span>");
	
	for(i = 1; i < subvol_list_num/4+1;i++){
		button_subvol_delete[i] = gtk_button_new_with_label("delete");
		gtk_table_attach(GTK_TABLE(table_subvol_delete),button_subvol_delete[i],4,5,i,i+1,GTK_EXPAND,GTK_EXPAND,0,5);
		g_signal_connect(G_OBJECT(button_subvol_delete[i]),"clicked",G_CALLBACK(handle_subvol_delete),GINT_TO_POINTER(i));
		gtk_widget_show(button_subvol_delete[i]);
	}
	for(i = 1; i < subvol_list_num/4+1;i++){
			printf("//////////////////////%s,%s,%s,%s////////////////////\n",list_def_id[i-1],list_def_gen[i-1],list_def_level[i-1],list_def_path[i-1]);
			gtk_label_set_text(GTK_LABEL(label_subvol_info[i][0]),list_def_id[i-1]);
			gtk_label_set_text(GTK_LABEL(label_subvol_info[i][1]),list_def_gen[i-1]);
			gtk_label_set_text(GTK_LABEL(label_subvol_info[i][2]),list_def_level[i-1]);
			gtk_label_set_text(GTK_LABEL(label_subvol_info[i][3]),list_def_path[i-1]);
	}	
}

