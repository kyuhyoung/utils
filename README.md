# utils

## TODO
* Make usage for "angleConv", "angleDiff" and "unwrap"

## util_cpp.cpp : c++ utility functions.

#### system related  

  * cout_indented()
  * error()
  * is_first_a_factor_of_second()
  * is_image_file()
  * is_only_number()
  * is_this_camera_index()
  * is_this_directory_existing()
  * is_this_file_existing()
  * itos_formatted()
  * get_exact_file_name_from_path()
  * get_id_of_file_as_number()
  * get_last_integer_substring()
  * get_list_of_image_path_under_this_directory() 
  * get_list_of_list_of_ids_as_number
  * make_string_lowercase()
  * make_string_uppercase()
  * mkdirs()
  * python_join_equivalent()
  * split_string_by_delimiter()
  * what_time_in_seconds_is_it_now()    
  
#### math related

  * angleConv()
  * angleDiff()
  * average_of_vector()
  * calc_angle_deg_three_points()
  * calc_area_quadrangle()
  * calc_area_triangle()
  * compute_angle_deg_between_two_lines()
  * compute_bilinear_weight()
  * compute_list_of_possible_rotation_degree()
  * constrainAngle()
  * deg2rad()
  * Det()
  * dist_two_points()
  * func_add_absolute()
  * generate_random_color_list()
  * geometric_median()  
  * hls_01_2_color_name()
  * IsExp2()
  * is_this_point_on_the_line_of_two_points()
  * LineLineIntersect()
  * matlab_mod_equivalent()
  * mean_absolute_of_vector()
  * median_of_vector()
  * rad2deg()
  * random_number_in_between()
  * unwrap()  
  * which_side_this_point_is_on_of_line_with_two_points()

  
#### OpenCV related  

  * are_all_seqs_gray()
  * cluster_histograms()
  * compute_area_of_contour()
  * compute_center_of_contour()
  * compute_circle_margin()
  * compute_descriptor()
  * compute_edge_bilateral()
  * compute_edge_gaussian()
  * compute_edge_median()
  * compute_histogram_4_emd()
  * compute_indice_of_no_hole_contour()
  * compute_offset_for_puttext()
  * compute_ratio_of_largest_blob()
  * compute_size_smaller_than()
  * concatenate_images()
  * concatenate_images_from_seqeunces_into_video_or_sequence()
  * connect_broken_contour()
  * contour_2_shape()
  * create_mat_with_some_value()
  * crop_image()
  * crop_with_center_and_radius()
  * detect_keypoint()
  * distance_btn_histograms()
  * dist_two_points()
  * draw_arc()
  * draw_match()
  * draw_rect_with_padding() 
  * draw_rotation_pencil()
  * emd_btn_histograms()
  * find_peaks_on_mat()
  * find_peaks_2D()
  * get_boundary_point_of_1st_radiated_from_2nd()
  * get_histogram()   
  * get_hsv_histogram()
  * get_hls_histogram()
  * get_next_index()
  * get_row_or_column_or_channel_wise_norm()
  * image_inside_circle()
  * init_from_cam_or_video_or_directory()
  * init_mat()
  * init_video_writer()
  * is_this_contour_circle_or_ellipse()
  * make_set_of_rotated_square_images()
  * match_intra()  
  * mat_norm_channel_wise()
  * Mat_to_vector_Vec2f()
  * mat_type_2_str() 
  * merge_mask()
  * non_maxima_suppression_on_mat()
  * pad_image()
  * print_mat()
  * print_mat_2d()
  * print_mat_3d()
  * print_mat_type()
  * print_matrix_min_max()
  * resize_image()
  * rotate_1st_around_2nd_by_3rd_radian()
  * rotate_image_by_degree()
  * RotateWrapFill()
  * RotateWrapFillFastSrcSizeExp2()
  * save_one_image_under_directory()
  * set_cam_properties_ocv()
  * sort_two_seqs_as_first_seq_sorted()
  * write_one_frame_to_video()
  * writeMat2File()

    
  
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
