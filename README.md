# utils
## util_cpp.cpp : c++ utility functions.
  * python_join_equivalent()
  * what_time_in_seconds_is_it_now()    
  * is_this_existing_directory()
  * mkdir_if_not_exist()
  * error()
  * is_only_number()
  * is_this_camera_index()
  * split_string_by_delimiter()
  * rad2deg()
  * deg2rad()
  * make_string_uppercase()
  * make_string_lowercase()
  * is_image_file()
  * get_last_integer_substring()
  * get_exact_file_name_from_path()
  * get_id_of_file_as_number()
  * get_list_of_image_path_under_this_directory() 
  

  
#### OpenCV related  

  * draw_rect_with_padding() 
  * init_from_cam_or_video()
  * set_cam_properties_ocv()
  * crop_image()
  * crop_with_center_and_radius()
  * concatenate_images()
  * rotate_image_by_degree()
  * make_set_of_rotated_square_images()
  * compute_circle_margin()
  * image_inside_circle()
  
  

  
  
## util_python.py : python utility functions.
  * count_substring()
  * is_only_letter()
  * is_only_number()
  * is_only_letter_or_digit()
  * find_nth_largest()
  * get_list_of_file_path_under_1st_with_2nd_extension()
  * round_i()
  * full_path_from_dir_id_extension()
  * get_exact_file_name_from_path()
  * is_this_empty_string()  
  * is_this_existing_directory()
  * mkdir_if_not_exist()  
  * extract_file_extension()  
  * get_immediate_subdirectories()
  
#### image related  
  * get_list_of_image_path_under_this_directory()
  * make_color_list()
  * compute_margin_ratio_left_top()
  * rescale_normalized_bounding_boxes_with_margin_ratio()
  * convert_bounding_boxes_to_original_image_scale()
  * convert_vid_2_animated_gif()
  * is_video_file()
  * is_image_file()
  * init_from_cam_or_video()
  * resize_and_pad_border()
  * make_video_recorder()
  * draw_and_show_xyxy_bboxes()
  * draw_and_show_ltwh_bboxes()  
  * crop_image()
  * write_one_frame_to_video()
  * save_one_image_under_directory()
  

#### Pytorch related  

  * im2batch()
  * compute_and_draw_fps_and_cofidence_threshold()
  * torch_tensor_det_letterbox_2_li_ltwh_ori()
  * get_class_string_from_torch_tensor()
