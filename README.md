# utils

## TODO
* Make usage for "angleConv", "angleDiff" and "unwrap"

## util_cpp.cpp : c++ utility functions.

#### system related  

  * cout_indented()
  * error()
  * file_2_list_of_list_of_string()
  * is_image_file()
  * is_only_number()
  * is_this_string_empty
  * is_this_camera_index()
  * is_this_directory_existing()
  * is_this_file_existing()
  * is_inside_docker()
  * itos_formatted()
  * get_exact_file_name_from_path()
  * get_file_paths_of_given_extension_under_this_directory()
  * get_id_of_file_as_number()
  * get_last_integer_substring()
  * get_list_of_image_path_under_this_directory() 
  * get_list_of_list_of_ids_as_number
  * lap_time
  * make_string_lowercase()
  * make_string_uppercase()
  * mkdir_p()
  * mkdirs()
  * python_join_equivalent()
  * split_string_by_delimiter()
  * string_list_2_homogeneous_matrix
  * to_string_with_precision()
  * what_time_in_seconds_is_it_now()   
  
#### math related

  * angleConv()
  * angleDiff()
  * average_of_vector()
  * calc_angle_deg_three_points()
  * calc_area_quadrangle()
  * calc_area_triangle()
  * cameraPoseFromHomography()
  * ChordalL1Mean_of_rotation()
  * closeEnough()
  * combine_euler_degree_translation_into_homogeneous_matrix()
  * compute_angle_deg_between_two_lines()
  * compute_bilinear_weight()
  * compute_list_of_possible_rotation_degree()
  * compute_remainder()
  * constrainAngle()
  * deg2rad()
  * Det()
  * dist_two_points()
  * eulerAngles()
  * eulerAnglesToRotationMatrix()
  * eulerDegrees2RotationMatrix()
  * eulerRadians2RotationMatrix()
  * func_add_absolute()
  * generate_random_color_list()
  * GeodesicL1Mean_of_rotation()
  * geometric_median()  
  * hls_01_2_color_name()
  * homography_dlt()
  * IsExp2()
  * is_first_a_factor_of_second()
  * is_this_point_on_the_line_of_two_points()
  * is_this_simple_float()
  * LineLineIntersect()
  * logarithm_map()
  * matlab_mod_equivalent()
  * mcosc()
  * mean_absolute_of_vector()
  * median_of_vector()
  * msinc()
  * normal_pdf()
  * orthonormalize()
  * pose_from_homography_dlt()
  * rad2deg()
  * random_number_in_between()
  * rotation_degree_of_euler_degrees()
  * RotationFromUnitAxisAngle()
  * rotationMatrixToEulerAngles()
  * rotationMatrix2EulerDegrees()
  * rotationMatrix2EulerRadians()
  * SkewSymmetricMatrix()
  * sinc()
  * unwrap()  
  * which_side_this_point_is_on_of_line_with_two_points()

  
#### OpenCV related  

  * alpha_blend()
  * are_all_seqs_gray()
  * binary_mat_2_point_list()
  * cluster_histograms()
  * combine_rotation_translation_into_homogeneous_matrix()
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
  * compute_pseudo_inverse()
  * compute_ratio_of_largest_blob()
  * compute_size_smaller_than()
  * concatenate_images()
  * concatenate_images_from_seqeunces_into_video_or_sequence()
  * connect_broken_contour()
  * contour_2_shape()  
  * cout_mat_indented()
  * cout_mat_2d_indented()
  * cout_mat_3d_indented()  
  * cout_mat_type_indented()
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
  * exponential_map_direct()
  * find_blackhole_by_correlation()
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
  * init_mat_with_array_of_values()
  * init_mat_with_one_value()
  * init_video_writer()
  * is_rotation_matrix()
  * is_this_contour_circle_or_ellipse()
  * make_set_of_rotated_square_images()
  * match_intra()  
  * mat_norm_channel_wise()
  * Mat_to_vector_Vec2f()
  * mat_type_2_str() 
  * mean_rotation_matrix_moakher()
  * mean_traslation_vector()
  * merge_mask()
  * non_maxima_suppression_on_mat()
  * ones_like()
  * pad_image()
  * pseudo_inverse()
  * print_matrix_min_max()
  * resize_image()
  * rotate_1st_around_2nd_by_3rd_radian()
  * rotate_image_by_degree()
  * RotateWrapFill()
  * RotateWrapFillFastSrcSizeExp2()
  * rot_mat_2_quaternion()
  * save_one_image_under_directory()
  * set_cam_properties_ocv()
  * skewMat()
  * skew_symmetric()
  * sort_two_seqs_as_first_seq_sorted()
  * split_homogeneous_transform_matrix_into_rotation_and_translation()
  * sqrt_of_mean_square()
  * sum_of_squared()
  * svd_opencv()
  * write_one_frame_to_video()
  * writeMat2File()
  * zeros_like()

    
  
## util_python.py : python utility functions.

#### system related  

  * add_postfix_right_b4_extension()
  * count_substring()
  * is_array_like()
  * is_only_letter()
  * is_only_number()
  * is_only_letter_or_digit()
  * filter_coi()
  * float3()
  * is_dict_with_given_keys()
  * is_this_list_empty()
  * isNaN
  * find_nth_largest()
  * get_list_of_file_path_under_1st_with_2nd_extension()
  * round_i()
  * full_path_from_dir_id_extension()
  * get_exact_file_name_from_path()
  * is_this_empty_string()  
  * is_this_existing_directory()
  * is_this_existing_file()
  * merge_divided_detections()
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
  * print_indented()
  * remove_directory()
  * rm_directory_if_exist()
  * rm_and_mkdir()  
  * str2bool()
  * split_string_by_delimiter()

#### math related  
 
  * angle_axis_2_euler_angles_rpy()
  * ap_per_class()
  * bbox_ios()
  * bbox_iou()
  * compute_loss()
  * compute_offsets_4_mosaicking()
  * deg2rad()
  * euler_angles_rpy_2_angle_axis()
  * get_interval()
  * get_num_of_division()
  * get_offset_list()
  * get_overlap()
  * get_overlap_ratio()
  * get_side_length_of_division()
  * get_num_and_side_length_of_division()
  * is_rotation_matrix()
  * letterbox_bbox_2_ori_bbox()
  * ltrb_2_ltwh()
  * ltrb_2_xywh()
  * ltwh_2_ltrb()
  * ltwh_2_xywh()
  * ori_bbox_2_letterbox_bbox()  
  * rad2deg()
  * rotation_matrix_2_euler_angles_rpy()
  * scale_bbox()
  * wh_iou()
  * xywh_2_ltrb()
  * xywh_2_ltwh()     


#### image related  

  * aspectcrop()
  * centercrop_and_resize()
  * compensate_division()
  * compute_margin_ratio_left_top()
  * convert_bbox_type()  
  * cropbbox()
  * get_list_of_image_path_under_this_directory()
  * genereate_random_color_list()
  * gen_random_color_bgr()
  * letterboxing_pil()
  * letterboxing_opencv()
  * non_max_suppression_4_mosaic_ltrb()
  * plot_one_box()  
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
  * split_image_into_left_and_right()
  * split_image_into_up_and_down()
  * split_image_into_left_and_right_then_save()
  * split_image_into_up_and_down_then_save()  
  * compute_bounding_box_of_non_zero_pixels()
  * generate_tiled_tif()
  * generate_tiled_tif_2()
  * ltwh_2_ltrb()
  * ltrb_2_ltwh()
  * xywh_2_ltrb()
  * ltrb_2_xywh()
  
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
