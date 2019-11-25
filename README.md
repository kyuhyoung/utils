# utils
## util_cpp.cpp : c++ utility functions.

#### system related  

  * python_join_equivalent()
  * what_time_in_seconds_is_it_now()    
  * is_this_existing_directory()
  * mkdir_if_not_exist()
  * error()
  * is_only_number()
  * is_this_camera_index()
  * split_string_by_delimiter()
  * is_first_a_factor_of_second()
  * itos_formatted()
  * make_string_uppercase()
  * make_string_lowercase()
  * is_image_file()
  * get_last_integer_substring()
  * get_exact_file_name_from_path()
  * get_id_of_file_as_number()
  * get_list_of_list_of_ids_as_number
  * get_list_of_image_path_under_this_directory() 
  
#### math related

  * matlab_mod_equivalent()
  * rad2deg()
  * deg2rad()
  * compute_bilnear_weight()
  * dist_two_points()
  * calc_area_triangle()
  * calc_area_quadrangle()
  * Det()
  * LineLineIntersect()
  * which_side_this_point_is_on_of_line_with_two_points()
  * is_this_point_on_the_line_of_two_points()
  * calc_angle_deg_three_points()
  * compute_angle_deg_between_two_lines()
  
#### OpenCV related  

  * detect_keypoint()
  * get_boundary_point_of_1st_radiated_from_2nd()
  * pad_image()
  * draw_rect_with_padding() 
  * init_from_cam_or_video_or_directory()
  * set_cam_properties_ocv()
  * crop_image()
  * crop_with_center_and_radius()
  * concatenate_images()
  * rotate_image_by_degree()
  * make_set_of_rotated_square_images()
  * compute_circle_margin()
  * image_inside_circle()
  * sort_two_seqs_as_first_seq_sorted()
  * get_next_index()
  * concatenate_images_from_seqeunces_into_video_or_sequence()
  * save_one_image_under_directory()
  * write_one_frame_to_video()
  * compute_size_smaller_than()
  * resize_image()
  * are_all_seqs_gray()
  * non_maxima_suppression_on_mat()
  * find_peaks_on_mat()
    
  
## util_python.py : python utility functions.

#### system related  

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
  * flatten()
  * get_num_gpu_nvidia()
  * get_file_path_if_string_is_a_substring_of_the_path_among_the_list()
  * find_paths_from_the_list_whose_file_name_is_the_same_as_query()
  * is_this_file_name_in_the_path_list()
  * get_list_of_file_names_with_string_in_multi_directories_of_text_file()
  * get_batch_size_as_multiple_of_num_gpu()



#### image related  
  * get_list_of_image_path_under_this_directory()
  * genereate_random_color_list()
  * gen_random_color_bgr()
  * compute_margin_ratio_left_top()
  * rescale_normalized_bounding_boxes_with_margin_ratio()
  * convert_bounding_boxes_to_original_image_scale()
  * convert_vid_2_animated_gif()
  * is_video_file()
  * is_image_file()
  * crop_image()
  * compute_optical_density()
  * get_image_size_from_list_of_contour()
  * convert_list_of_contour_2_opencv_contours()
  * resize_if_necessary()
  * compute_bounding_box_of_non_zero_pixels()
  * generate_tiled_tif()
  * generate_tiled_tif_2()

  
#### OpenCV related   
  * init_from_cam_or_video()
  * resize_and_pad_border()
  * make_video_recorder()
  * draw_and_show_xyxy_bboxes()
  * draw_and_show_ltwh_bboxes()  
  * write_one_frame_to_video()
  * save_one_image_under_directory()
  
#### skimage related  
  * otsu_thresholding()
  * get_sum_of_rectangle()
  * is_this_rect_belong_2_blob()
  * is_this_patch_below_threshold()
  * is_this_patch_below_or_equal_to_threshold()
  * is_this_patch_above_threshold()
  * is_this_patch_above_or_equal_to_threshold()
  * compute_edge_integral()


#### Pytorch related  

  * im2batch()
  * compute_and_draw_fps_and_cofidence_threshold()
  * torch_tensor_det_letterbox_2_li_ltwh_ori()
  * get_class_string_from_torch_tensor()
