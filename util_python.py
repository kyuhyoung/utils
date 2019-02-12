# Generate a list of (random) colors of the given number
# first 15 colors : non-random
# > 15 colors : random between 100 and 255
# input 
#    n_class : # of colors to be generated
# output
#    li_color_bgr : list of the size [n_class x 3]. It doesn't have to be 'bgr' (It can be 'rgb')

def make_color_list(n_class):
    li_color_bgr = []
    li_color_bgr.append((255, 0, 0))
    li_color_bgr.append((0, 255, 0))
    li_color_bgr.append((0, 0, 255))
    if len(li_color_bgr) < n_class:
        li_color_bgr.append((255, 255, 0))
        li_color_bgr.append((255, 0, 255))
        li_color_bgr.append((0, 255, 255))
        if len(li_color_bgr) < n_class:
            li_color_bgr.append((255, 128, 0))
            li_color_bgr.append((255, 0, 128))
            li_color_bgr.append((0, 255, 128))
            if len(li_color_bgr) < n_class:
                li_color_bgr.append((128, 255, 0))
                li_color_bgr.append((128, 0, 255))
                li_color_bgr.append((0, 128, 255))
                if len(li_color_bgr) < n_class:
                    li_color_bgr.append((128, 128, 0))
                    li_color_bgr.append((128, 0, 128))
                    li_color_bgr.append((0, 128, 128))
                    if len(li_color_bgr) < n_class:
                        more = n_class - len(li_color_bgr)                        
                        t1 = [(random.randint(100, 255), random.randint(100, 255), random.randint(100, 255)) for k in range(more)]
                        li_color_bgr += t1 
    return li_color_bgr

# In most case, the sizes of the original image and the input image of a detection-network are not the same.  
# So the original image has to be resized and padded with additial borders at either top/bottom or left/right sides
# This function computes the ratio of either top/bottom or left/right borders against the network input imags.
# input
#    w_h_ori : the width and height of the original image
#        [w_ori, h_ori]
#    w_h_net : the width and height of the network input image
#        [w_ori, h_ori]
# output
#    ratios of left, right, top and bottom margin against the network input image

def compute_margin_ratio_l_r_t_b(w_h_ori, w_h_net):
    w_ori, h_ori = w_h_ori; w_net, h_net = w_h_net;
    ratio_l, ratio_r, ratio_t, ratio_b = 0, 0, 0, 0
    ratio_w = w_net / w_ori
    ratio_h = h_net / h_ori
    if ratio_w > ratio_h:
        ratio = ratio_h
        w_resized = w_ori * ratio
        ratio_l = (w_net - w_resized) / (w_net * 2.0)
        ratio_r = ratio_l
    else:
        ratio = ratio_w
        h_resized = h_ori * ratio
        ratio_t = (h_net - h_resized) / (h_net * 2.0)
        ratio_b = ratio_t
    return [ratio_l, ratio_r, ratio_t, ratio_b]




# In most case, the sizes of the original image and the input image of a detection-network are not the same.  
# So the original image has to be resized and padded with additial borders at either top/bottom or left/right sides (such as using cv2.copyMakeBorder)  
# After forwarding thru the detection-net, the output is likely to be an array of normalized bonding boxes.  
# To draw the resulted bounding boxes on the original image, we should compute the shfited and rescaled normalized bounding boxes first.
# input
#    boxes : 2d array of normalized bounding boxes of the size [# box x 4]
#       [[x_from_1, y_from_1, x_to_1, y_to_1]
#        [x_from_2, y_from_2, x_to_2, y_to_2]
#        ... 
#        [x_from_N, y_from_N, x_to_N, y_to_N]]
#        0 <= x_from, x_to <= 1
#        0 <= y_from, y_to <= 1
#    li_margin_ratio_l_r_t_b : list of the ratios of 4 margins for which pixels are filled with dummy values.
#        [margin_ratio_left, margin_ratio_right, margin_ratio_top, margin_ratio_bottom] 
# output
#    boxes : shfited and rescaled normalized bounding boxes.

def rescale_normalized_bounding_boxes_with_margin_ratio(boxes, li_margin_ratio_l_r_t_b):
    margin_ratio_l, margin_ratio_r, margin_ratio_t, margin_ratio_b = li_margin_ratio_l_r_t_b 
    if 0 == margin_ratio_t:
        bunmo = 1.0 - (margin_ratio_l + margin_ratio_r)
        boxes[:, 0] -= margin_ratio_l
        boxes[:, 0] /= bunmo
        boxes[:, 2] -= margin_ratio_l
        boxes[:, 2] /= bunmo
    elif 0 == margin_ratio_l:
        bunmo = 1.0 - (margin_ratio_t + margin_ratio_b)
        boxes[:, 1] -= margin_ratio_t
        boxes[:, 1] /= bunmo
        boxes[:, 3] -= margin_ratio_t
        boxes[:, 3] /= bunmo
    return boxes 


# In most case, the sizes of the original image and the input image of a detection-network are not the same.  
# So the original image has to be resized and padded with additial borders at either top/bottom or left/right sides (such as using cv2.copyMakeBorder)  
# After forwarding thru the detection-net, the output is likely to be an array of normalized bonding boxes.  
# To draw the resulted bounding boxes on the original image, we should compute the shfited and rescaled normalized bounding boxes first and then scale as the original image size. 
# input
#    boxes : 2d array of normalized bounding boxes of the size [# box x 4]
#       [[x_from_1, y_from_1, x_to_1, y_to_1]
#        [x_from_2, y_from_2, x_to_2, y_to_2]
#        ... 
#        [x_from_N, y_from_N, x_to_N, y_to_N]]
#        0 <= x_from, x_to <= 1
#        0 <= y_from, y_to <= 1
#    li_margin_ratio_l_r_t_b : list of the ratios of 4 margins for which pixels are filled with dummy values.
#        [margin_ratio_left, margin_ratio_right, margin_ratio_top, margin_ratio_bottom] 
#    w_h_ori : the width and height of the original image
#        [w_ori, h_ori]
# output
#    boxes : shfited and rescaled bounding boxes in original image scale.
    
def convert_bounding_boxes_to_original_image_scale(boxes, li_margin_ratio_l_r_t_b, w_h_ori):
    w_or, h_ori = w_h_ori
    boxes = compute_bounding_boxes_in_original_image_scale(boxes, li_margin_ratio_l_r_t_b)
    boxes[:, 0] *= w_ori 
    boxes[:, 2] *= w_ori 
    boxes[:, 1] *= h_ori 
    boxes[:, 3] *= h_ori
    return boxes


# convert a video (avi, mpeg) to an animaged gif
# ffmpeg should be installed in prior.
# input
#    fn_vid : path to the video file

import os
def convert_vid_2_animated_gif(fn_vid):
    return os.system('ffmpeg -i {} -r 10 {}'.format(fn_record, os.path.splitext(fn_vid)[0] + '.gif'))     
   

# check if a file name is that of video file by extension.
# input
#    fn : path to the file
# output
#    boolean whether it is video file or not.   

def is_video_file(fn): 
    ext = (".3g2", ".3gp", ".asf", ".asx", ".avi", ".flv", ".m2ts", ".mkv", ".mov", ".mp4", ".mpg", ".mpeg", ".rm", ".swf", ".vob", ".wmv")
    return fn.endswith(ext)

#######################################################################################################################################
########        opencv related        #######################################################################################

# open a camera divice or video file using opencv.
# input
#    id_cam : string of camera ID or video file path
# output
#    kam : camera handle
#    w_h_cam : the width and height of camera image.        

import cv2

def init_cam(id_cam):
    if is_video_file(id_cam):
        #print('this is video file')
        kam = cv2.VideoCapture(id_cam)    
    else:
        kam = cv2.VideoCapture(int(id_cam))
    if kam is None or not kam.isOpened():
        print('Unable to open camera ID : ', id_cam);   exit()
    print('Camera : {} is opened'.format(id_cam))
    w_h_cam = (int(kam.get(cv2.CAP_PROP_FRAME_WIDTH)), int(kam.get(cv2.CAP_PROP_FRAME_HEIGHT))) # float
    return kam, w_h_cam   
    
    
# In most case, the sizes of the original image and the input image of a detection-network are not the same.  
# So the original image has to be resized and padded with additial borders at either top/bottom or left/right sides (such as using cv2.copyMakeBorder)  
# input
#    im_rgb : 3d array of color image
#    color_rgb : color values of pixels to be padded.
#    w_h_desired : width and height of the desired image size which is supposed to be the input of a neural network.
# output
#    im_rgb : the resized and padded images whose size is 'w_h_desired'.  

import cv2

def resize_and_pad_border(im_rgb, color_rgb, w_h_desired):
    w_desired, h_desired = w_h_desired
    h_old, w_old = im_rgb.shape[:2]
    #print('h_old : ', h_old);   print('w_old : ', w_old);   #exit()
    ratio_w = float(w_desired) / float(w_old)
    ratio_h = float(h_desired) / float(h_old)
    ratio = min(ratio_w, ratio_h)
    w_new = int(w_old * ratio)
    h_new = int(h_old * ratio)
    #print('w_new : ', w_new);   print('w_new : ', w_new);   #exit()
    im_rgb = cv2.resize(im_rgb, (w_new, h_new))
    if ratio_w != ratio_h:
        delta_w = w_desired - w_new
        delta_h = h_desired - h_new
        top = delta_h // 2; bottom = delta_h - top
        left = delta_w // 2;    right = delta_w - left
        im_rgb = cv2.copyMakeBorder(im_rgb, top, bottom, left, right, cv2.BORDER_CONSTANT, value=color_rgb)
    return im_rgb    


# open a video recorder using opencv.
# input
#    fn_vid : video file name
#    w_h_vid : the desired video width and height.        
# output
#    video writer handle.        

import cv2

def make_video_recorder(fn_vid, w_h_vid, fps):
    fourcc = cv2.VideoWriter_fourcc('M','J','P','G')
    return cv2.VideoWriter(fn_vid, fourcc, fps, w_h_vid)
#######################################################################################################################################


#######################################################################################################################################
########        pytorch related        #######################################################################################

# make a single image to a mini-batch to a PyTorch network.
# input
#    im_bgr : 3d array of color image
#    means_bgr : 1d array of BGR mean of pixels leanred for the training set.
#        [mean_blue, mean_green, mean_red]
#    w_h_net : width and height of the input image of a neural network.
# output
#    batch_rgb : 1 x 3 x height x width of tensor.   

import torch
from torch.autograd import Variable

def im2batch(im_bgr, means_bgr, w_h_net):
    #print('im_bgr.shape : ', im_bgr.shape)
    im_bgr_resized = resize_and_pad_border(im_bgr, means_bgr, w_h_net)
    #cv2.imshow('im_bgr', im_bgr);   cv2.imshow('im_bgr_resized', im_bgr_resized);   cv2.waitKey();  exit()
    im_bgr_norm_resized = im_bgr_resized - means_bgr
    im_rgb_norm_resized = im_bgr_norm_resized.transpose((2, 0, 1))
    ts_rgb_norm = torch.from_numpy(im_rgb_norm_resized).float()
    batch_rgb = ts_rgb_norm.unsqueeze(0)
    if args.cuda:
        batch_rgb = Variable(batch_rgb.cuda(), volatile=True)
    return batch_rgb


# draw fps and threshold parameter on an image.
# input
#    im_bgr : 3d array of color image
#    n_processed : # of frames processed so far.
#    sec_start : the time (sec) this program started.
#    w_h_img : width and height of the image
#    th_conf : threashold value.
# output
#    im_bgr : the image with fps and thereshold drawing.   

import torch
import time

def compute_and_draw_fps_and_cofidence_threshold(im_bgr, n_processed, sec_start, w_h_img, th_conf):
    wid, hei = w_h_img
    torch.cuda.synchronize()
    sec_end = time.perf_counter()
    fps = n_processed / (sec_end - sec_start)
    #print('fps : ', fps);   exit()
    cv2.putText(im_bgr, "conf. thres. : {:.2f}".format(th_conf), (int(wid * 0.5 - 80), int(hei * 0.97)), cv2.FONT_HERSHEY_SIMPLEX, FONT_SCALE_CONFIDIENCE, (0, 255, 0))
    cv2.putText(im_bgr, "fps : {:.1f}".format(fps), (int(wid * 0.5 - 50), int(hei * 0.06)), cv2.FONT_HERSHEY_SIMPLEX, FONT_SCALE_FPS, (0, 0, 255))
    return im_bgr

#######################################################################################################################################
    
