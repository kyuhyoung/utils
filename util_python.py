#######################################################################################################################################
########        system related        #######################################################################################
#########################################################################################################


#########################################################################################################
# input
# str_path = '/path/to/the/file.ext'
# prephix = '_prefix'
# print('new path : ', add_postfix_right_b4_extension(str_path, postphix)
# => new path : /path/to/the/file_postfix.ext 
def add_postfix_right_b4_extension(str_path, postphix):
    base, extenzion = os.path.splitext(str_path)
    return base + postphix + extenzion

#########################################################################################################
# input
#   strin : string
#   sub_str : string
# output
#   kount : how many times 'sub_str' occurs in 'strin'.

def count_substring(strin, sub_str):
    kount = 0
    idx_sub = strin.find(sub_str)
    if idx_sub >= 0:
        kount = 1 + count_substring(strin[idx_sub + 1:], sub_str)
    return kount



#########################################################################################################
def is_array_like(obj):
    return hasattr(obj, '__iter__') and hasattr(obj, '__len__')



#########################################################################################################
# input
#   strin : string
# output
#   boolean : True if 'strin' is only composed of letter.

def is_only_letter(strin):
    return strin.isalpha()

#########################################################################################################
# input
#   strin : string
# output
#   boolean : True if 'strin' is only composed of number.

def is_only_number(strin):
    return strin.isdigit()

#########################################################################################################
# input
#   strin : string
# output
#   is_letter_or_digit : whether the input string only consists of alphabet letters or digits.

def is_only_letter_or_digit(strin):
    is_letter_or_digit = False
    if is_only_letter(strin) or is_only_number(strin):
        is_letter_or_digit = True
    else:
        t1 = str.lower()
        t2 = ''.join([char for char in t1 if char not in 'abcdefghijklmnopqrstuvwxyz0123456789'])
        if not t2:
            is_letter_or_digit = True
    return is_letter_or_digit    

#########################################################################################################
# input
#   li_num : list of numbers
#   n : n_th largest. 
#       1 -> the most largest
#       2 -> the second largest
#       3 -> the third largest
# output
#   n_th_largest : the n the largest number in the list
#       For the input [1, 4, 1, 5, 4],
#       if n is 1, the return should be 5
#       if n is 2, the return should be 4
#       if n is 3, the return should be 1
#       if n is > 3, the return should be None

def find_nth_largest(li_num, n):
    n_th_largest = None
    if li_num:        
        for iN in range(n):
            t1 = max(li_num)
            while max(li_num) == t1:
                li_num.remove(t1)
            if not li_num:
                break
        if li_num:
            n_th_largest = max(li_num)
    return n_th_largest

#########################################################################################################
# input
#   direc : path of a folder.
#   ext : string of file extension. 
#       For example both '.txt' and 'txt' are OK
# output
#   list of file path

def get_list_of_file_path_under_1st_with_2nd_extension(direc, ext = ''):
    li_path_total = []
    is_extension_given = is_this_empty_string(ext)
    for dirpath, dirnames, filenames in os.walk(os.path.expanduser(direc)):
        n_file_1 = len(filenames)
        if n_file_1:
            if is_extension_given:
                li_path = [os.path.join(dirpath, f) for f in filenames if f.lower().endswith(ext.lower())]
            else:
                li_path = [os.path.join(dirpath, f) for f in filenames]
            n_file_2 = len(li_path)
            if n_file_2:
                li_path_total += li_path
    return sorted(li_path_total)

#########################################################################################################
# input
#   x : number
# output
#   integer of rounded 'x'

def round_i(x):
    return int(round(x))

#########################################################################################################
# input
#   direc : path of a folder.
#       ex) '/mnt/d/img/'    
#   aidi : string of only exact file name without extension. 
#       ex) 'people_in_office'
#   ext : string of file extension.
#       For example both '.txt' and 'txt' are OK
#       ex) '.bmp'
# output
#   full paht composed of 'direc', 'aidi' and 'ext'
#       ex) '/mnt/d/img/people_in_office.bmp'

def full_path_from_dir_id_extension(direc, aidi, ext):
    return path.join(os.path.expanduser(direc), aidi + "." + ext.split('.')[-1])

#########################################################################################################
# input
#   str_path : path of a file.
#       ex) '/mnt/d/img/people_in_office.bmp'    
# output
#   string of only the file name extracted
#       ex) 'people_in_office'

def get_exact_file_name_from_path(str_path):
    return os.path.splitext(os.path.basename(str_path))[0]

#########################################################################################################
# input
#   strin : string.
#       ex) 'kyuhyoung choi', '', '  '    
# output
#   boolean whether 'strin' is really a string.
#       ex) True if 'strin' is 'kyuhyoung choi'
#           False if 'strin' is '' or '  '.

def is_this_empty_string(strin):
    return (strin in (None, '')) or (not strin.stip())


#########################################################################################################
# input
#   path_dir : string of a directory path.
#       ex) '/mnt/d/images'    
# output
#   boolean whether 'path_dir' is a existing directory.
#       ex) True if '/mnt/d/images' exists.

def is_this_existing_directory(path_dir):
    return os.path.isdir(os.path.expanduser(path_dir))
    #return os.path.isdir(path_dir)


#########################################################################################################
# input
#   path_dir : string of a directory path.
#       ex) '/mnt/d/images'    
# output
#   is_newly_made : True if 'path_dir' is newly made and False otherwise

def mkdir_if_not_exist(path_dir):
    path_dir = os.path.expanduser(path_dir)
    is_newly_made = False
    if not os.path.exists(path_dir):
        os.makedirs(path_dir)
        is_newly_made = True
    return is_newly_made




#########################################################################################################
# input
#   path_file : string of file path.
#       ex) '/mnt/d/images/img.bmp'  
#   with_dot : boolean whether dot is included in the return
# output
#   string of the file exstension w/wo a dot.
#       ex) '.bmp' if 'with_dot' is True, 'bmp' otherwise.

def extract_file_extension(path_file, with_dot):
    extension_with_dot = os.path.splitext(path_file)
    return extension_with_dot if with_dot else extension_with_dot.split('.')[-1] 

#########################################################################################################
# input
#   direc : string of directory path.
#       ex) '/mnt/d/images'  
# output
#   list of string of immediate sub-directories.
#       ex) ['/mnt/d/images/seq0', '/mnt/d/images/seq1', '/mnt/d/images/seq2'].

import os
def get_immediate_subdirectories(direc):
    return sorted([os.path.join(direc, name) for name in os.listdir(direc) if os.path.isdir(os.path.join(direc, name))])

#########################################################################################################
def flatten(x):
    if isinstance(x, collections.Iterable):
        return [a for i in x for a in flatten(i)]
    else:
        return [x]


#########################################################################################################
def get_num_gpu_nvidia():
    cmd = ['nvidia-smi', '--query-gpu=temperature.gpu', '--format=csv,noheader']
    try:
        output = subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]
        li_gpu_temperature = output.split()
        try:
            n_gpu = len(li_gpu_temperature)
        except ValueError:
            n_gpu = 0
    except:
        n_gpu = 0
    return n_gpu
    

#########################################################################################################
def get_file_path_if_string_is_a_substring_of_the_path_among_the_list(li_fn, strng):
    li_path = [fn for fn in li_fn if strng in get_exact_file_name_from_path(fn)]
    n_file = len(li_path)
    if len(li_path) > 1:
        print('There is more than one file whose name includes : ' + strng)
        sys.exit(1)
    elif 0 == n_file:
        print('There is NO such a file whose name includes : ' + strng)
        return None
    return li_path[0]

#########################################################################################################
def find_paths_from_the_list_whose_file_name_is_the_same_as_query(li_path, fn_query):
    return [path for path in li_path if fn_query == basename(fn)]

#########################################################################################################
def is_this_file_name_in_the_path_list(li_fn, fn_query):
    li_path = find_paths_from_the_list_whose_file_name_is_the_same_as_query(li_fn, fn_query)
    n_same = len(li_path)
    return n_same > 0


#########################################################################################################
def get_list_of_file_names_with_string_in_multi_directories_of_text_file(txt_li_dir):
    li_fn = []
    with open(txt_li_dir) as f:
        for line in f:
            line = line.strip()
            li_str = line.split()
            n_str = len(li_str)
            if 3 <= n_str:
                dir = li_str[0]
                ext = li_str[1]
                substring = li_str[2]
                li_fn_str = \
                    [join(dir, f) for f in listdir(dir) if (isfile(join(dir, f)) and f.endswith(ext) and substring in f and (not is_this_file_name_in_the_path_list(li_fn, f)))]
            elif 2 == n_str:
                dir = li_str[0]
                ext = li_str[1]
                li_fn_str = \
                    [join(dir, f) for f in listdir(dir) if (isfile(join(dir, f)) and f.endswith(ext) and (not is_this_file_name_in_the_path_list(li_fn, f)))]
            elif 1 == n_str:
                dir = li_str[0]
                li_fn_str = \
                    [join(dir, f) for f in listdir(dir) if (isfile(join(dir, f)) and (not is_this_file_name_in_the_path_list(li_fn, f)))]
            li_fn += li_fn_str
    return li_fn


#########################################################################################################
def get_batch_size_as_multiple_of_num_gpu(len_batch):
    #batch_size = 0
    n_gpu = get_num_gpu_nvidia()
    batch_per_gpu_actuall = 0
    if len_batch >= n_gpu:
        batch_per_gpu_actuall = int(math.floor(float(len_batch) / float(n_gpu)))
        #batch_size = batch_per_gpu_actuall * n_gpu
    return batch_per_gpu_actuall





###################################################################################################################
#   image related
###################################################################################################################


def cropbbox(imagewidth, imageheight, thumbwidth, thumbheight):
    """ cropbbox(imagewidth,imageheight, thumbwidth,thumbheight)

        Compute a centered image crop area for making thumbnail images.
          imagewidth,imageheight are source image dimensions
          thumbwidth,thumbheight are thumbnail image dimensions

        Returns bounding box pixel coordinates of the cropping area
        in this order (left,upper, right,lower).
    """
    # determine scale factor
    fx = float(imagewidth) / thumbwidth
    fy = float(imageheight) / thumbheight
    f = fx if fx < fy else fy

    # calculate size of crop area
    cropheight, cropwidth = int(thumbheight * f), int(thumbwidth * f)

    # for centering use half the size difference of the image and the crop area
    dx = (imagewidth - cropwidth) / 2
    dy = (imageheight - cropheight) / 2

    # return bounding box of centered crop area on source image
    return dx, dy, cropwidth + dx, cropheight + dy


def aspectcrop(im, wh_2_be):
    thumbwidth, thumbheight = wh_2_be
    #im = Image.open(StringIO(f))
    imagewidth, imageheight = im.size
    dx, dy, cropwidth_plus_dx, cropheight_plus_dy = cropbbox(imagewidth, imageheight, thumbwidth, thumbheight)
    im_cropped = im.crop((dx, dy, cropwidth_plus_dx, cropheight_plus_dy))
    return im_cropped 

def centercrop_and_resize(im, wh_2_be):
    #w_2_be, h_2_be = wh_2_be
    #h_over_w_2_be = h_2_be / w_2_be
    #im_cropped = aspectcrop(im, h_over_w_2_be)
    im_cropped = aspectcrop(im, wh_2_be)
    im_resized = im_cropped.resize(wh_2_be, Image.ANTIALIAS)
    return im_resized


def letterbox_image_pil(image, size):
    '''resize image with unchanged aspect ratio using padding'''
    iw, ih = image.size
    w, h = size
    scale = min(w/iw, h/ih)
    nw = int(iw*scale)
    nh = int(ih*scale)
    image = image.resize((nw,nh), Image.BICUBIC)
    new_image = Image.new('RGB', size, (128,128,128))
    new_image.paste(image, ((w-nw)//2, (h-nh)//2))
    return new_image

def letterbox_image_opencv(image, size):
    '''resize image with unchanged aspect ratio using padding'''
    iw, ih = image.shape[0:2][::-1]
    w, h = size
    scale = min(w/iw, h/ih)
    nw = int(iw*scale)
    nh = int(ih*scale)
    image = cv2.resize(image, (nw,nh), interpolation=cv2.INTER_CUBIC)
    new_image = np.zeros((size[1], size[0], 3), np.uint8)
    new_image.fill(128)
    dx = (w-nw)//2
    dy = (h-nh)//2
    new_image[dy:dy+nh, dx:dx+nw,:] = image
    return new_image    
    

#########################################################################################################
# input
#   dir_img : string of directory path.
#       ex) '/mnt/d/images'
#   ext : string of iamge extension.
# output
#   li_fn_img : sorted list of image file paths.
#       ex) ['/mnt/d/images/img001.bmp', '/mnt/d/images/img002.bmp', '/mnt/d/images/img003.bmp']

def get_list_of_image_path_under_this_directory(dir_img, ext = ''):
    dir_img = os.path.expanduser(dir_img)
    li_fn_img = get_list_of_file_path_under_1st_with_2nd_extension(dir_img, ext)
    if is_this_empty_string(ext):
        li_fn_img = [fn for fn in li_fn_img if is_image_file(fn)]
    return sorted(li_fn_img)

#########################################################################################################
# Generate a list of (random) colors of the given number
# first 15 colors : non-random
# > 15 colors : random between 100 and 255
# input 
#    n_class : # of colors to be generated
# output
#    li_color_bgr : list of the size [n_class x 3]. It doesn't have to be 'bgr' (It can be 'rgb')
   
def genereate_random_color_list(n_class):
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

#########################################################################################################
# input 
#   r_min   : minimum intensity of red channel
#   g_min   : minimum intensity of green channel
#   b_min   : minimum intensity of blue channel
# output
#    tuple of random rgb values.
def gen_random_color_bgr(r_min, g_min, b_min):
    rr = np.random.randint(r_min, 256)
    gg = np.random.randint(g_min, 256)
    bb = np.random.randint(b_min, 256)
    return (rr, gg, bb)


#########################################################################################################
# In most case, the sizes of the original image and the input image of a detection-network are not the same.  
# So the original image has to be resized and padded with additial borders at either top/bottom or left/right sides
# This function computes the ratio of either top/bottom or left/right borders against the network input imags.
# input
#    w_h_ori : the width and height of the original image
#        [w_ori, h_ori]
#    w_h_net : the width and height of the network input image
#        [w_net, h_net]
# output
#    ratios of left, right, top and bottom margin against the network input image

def compute_margin_ratio_left_top(w_h_ori, w_h_net, is_letterbox):
    w_ori, h_ori = w_h_ori; w_net, h_net = w_h_net;
    ratio_l, ratio_t = 0, 0
    ratio_w = w_net / w_ori
    ratio_h = h_net / h_ori
    is_ratio_w_larger = ratio_w > ratio_h
    if (is_letterbox and is_ratio_w_larger) or not(is_letterbox or is_ratio_w_larger):
        ratio = ratio_h
        w_resized = w_ori * ratio
        ratio_l = (w_net - w_resized) / (w_net * 2.0)
        #ratio_r = ratio_l
    else      
        ratio = ratio_w
        h_resized = h_ori * ratio
        ratio_t = (h_net - h_resized) / (h_net * 2.0)
        #ratio_b = ratio_t
    return ratio_l, ratio_t, ratio
    #return [ratio_l, ratio_r, ratio_t, ratio_b]



#########################################################################################################
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


#########################################################################################################
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


#########################################################################################################
# convert a video (avi, mpeg) to an animaged gif
# ffmpeg should be installed in prior.
# input
#    fn_vid : path to the video file

import os
def convert_vid_2_animated_gif(fn_vid):
    return os.system('ffmpeg -i {} -r 10 {}'.format(fn_record, os.path.splitext(fn_vid)[0] + '.gif'))     
   

#########################################################################################################
# check if a file name is that of video file by extension.
# input
#    fn : path to the file
# output
#    boolean whether it is video file or not.   

def is_video_file(fn): 
    ext = (".3g2", ".3gp", ".asf", ".asx", ".avi", ".flv", ".m2ts", ".mkv", ".mov", ".mp4", ".mpg", ".mpeg", ".rm", ".swf", ".vob", ".wmv")
    return fn.endswith(ext)

#########################################################################################################
# check if a file name is that of image file by extension.
# input
#    fn : path to the file
# output
#    boolean whether it is image file or not.   

def is_image_file(fn): 
    ext = (".bmp", ".ppm", ".png", ".gif", ".jpg", ".jpeg", ".tif", ".pgm")
    return fn.endswith(ext)

#########################################################################################################
#   print(get_sequence_id_from_directory('/home/someuser/seq_eyedea_104/, true)
#   => 104
#   print(get_sequence_id_from_directory('/home/someuser/seq_eyedea_104/, false)
#   => seq_eyedea_104

def get_sequence_id_from_directory(direc, is_ai_challenge_19):
    if is_ai_challenge_19:
        return int(direc.split('_')[-1])
    else:
        return os.path.basename(os.path.normpath(direc))


#########################################################################################################
#   Generalized version of cropping subimage : The subimage is kind of moving window such like bouncing ball inside the image.  
#   With 'xy_previous' as '(0, 0)', this becomes a regular image cropping getting subimage of cv2.Rect(xy_shift, wh_cropped)
def crop_image(im_bgr, xy_previous, xy_shift, wh_cropped):
# shift x : '+' means from left to right
#           '-' means from right to left
# shift y : '+' means from top to bottom
#           '-' means from bottom to top
    is_x_bouncing, is_y_bouncing = False, False;
    h_ori, w_ori = im_bgr.shape[:2]
    x_prev, y_prev = xy_previous;   w_cropped, h_cropped = wh_cropped;  x_shift, y_shift = xy_shift
    x_cropped = x_prev + x_shift
    if x_cropped < 0:
        x_cropped = float(0)
        is_x_bouncing = True
    if x_cropped + w_cropped > w_ori:
        
        x_cropped = float(w_ori - w_cropped)
        is_x_bouncing = True
    y_cropped = y_prev + y_shift
    if y_cropped < 0:
        y_cropped = float(0)
        is_y_bouncing = True
    if y_cropped + h_cropped > h_ori:
        y_cropped = float(h_ori - h_cropped)
        is_y_bouncing = True
    xy_previous = [x_cropped, y_cropped]
    if is_x_bouncing:
        xy_shift[0] *= -1.0
    if is_y_bouncing:
        xy_shift[1] *= -1.0
    x_cropped_i, y_cropped_i = round_i(x_cropped), round_i(y_cropped)
    im_bgr_cropped = im_bgr[y_cropped_i : y_cropped_i + h_cropped, x_cropped_i : x_cropped_i + w_cropped]
    #cv2.rectangle(im_bgr, (x_cropped_i, y_cropped_i), (x_cropped_i + w_cropped, y_cropped_i + h_cropped), (0,       0, 255), 1);  cv2.imshow('cropped', im_bgr)
    return im_bgr_cropped, xy_previous, xy_shift


#########################################################################################################
def compute_optical_density(intensity, intensity_0):
    t1 = np.maximum(1., intensity.astype(float))
    #t6 = np.max(t1)
    #t7 = np.min(t1)
    t2 = t1 / intensity_0
    #t8 = np.max(t2)
    #t9 = np.min(t2)
    t3 = -np.log(t2)
    #t10 = np.max(t3)
    #t11 = np.min(t3)
    return t3


#########################################################################################################
def get_image_size_from_list_of_contour(li_li_point, margin):
    x_margin, y_margin = margin
    li_xy = flatten(li_li_point)
    li_x, li_y = li_xy[::2], li_xy[1::2]
    w_img = int(round(max(li_x) + x_margin))
    h_img = int(round(max(li_y) + y_margin))
    return (w_img, h_img)

#########################################################################################################
def convert_list_of_contour_2_opencv_contours(li_li_point):
    contours = []
    for li_point in li_li_point:
        li_point_int = [[int(round(point[0])), int(round(point[1]))] for point in li_point]
        contour = np.array(li_point_int, dtype=np.int32)
        contours.append(contour)
#        contours = [numpy.array([[1, 1], [10, 50], [50, 50]], dtype=numpy.int32),
#                numpy.array([[99, 99], [99, 60], [60, 99]], dtype=numpy.int32)]
    return contours

#########################################################################################################
def resize_if_necessary(im, r_x, r_y, min_r):
    if r_x < min_r or r_y < min_r:
        ratio = min(r_x, r_y)
        im = cv2.resize(im, None, fx = ratio, fy = ratio)
    return im, im.shape[1], im.shape[0]

#########################################################################################################
def compute_bounding_box_of_non_zero_pixels(im_bool):
    ar_y, ar_x = np.nonzero(im_bool)
    x_min = min(ar_x)
    x_max = max(ar_x)
    y_min = min(ar_y)
    y_max = max(ar_y)
    return (x_min, y_min), (x_max, y_max)


#########################################################################################################
def generate_tiled_tif(fn_img, shall_remove_non_tif, postfix):
    #fn_tif = marked_image_path.replace('.untiled.tif', '.mark.tif')
    if None == postfix:
        fn_tif = os.path.splitext(fn_img)[0] + '.tif'
    else:
        fn_tif = os.path.splitext(fn_img)[0] + '_' + postfix + '.tif'
    cmd = 'vips tiffsave "%s" "%s" --compression=jpeg --vips-progress --tile --pyramid --tile-width=240 --tile-height=240' % (fn_img, fn_tif)
    #print(cmd)
    call(cmd, shell=True)
    if shall_remove_non_tif:
        os.remove(fn_img)
        
        
#########################################################################################################
def generate_tiled_tif_2(fn_img, fn_result, postfix):
    #file_name_only = get_exact_file_name_from_path(fn_img)
    #fn_tif = marked_image_path.replace('.untiled.tif', '.mark.tif')
    fn_tif = fn_result + '.' + postfix + '.tif'
    cmd = 'vips tiffsave "%s" "%s" --compression=jpeg --vips-progress --tile --pyramid --tile-width=240 --tile-height=240' % (fn_img, fn_tif)
    #print(cmd)
    call(cmd, shell=True)



#######################################################################################################################################
########        opencv related        #######################################################################################
#########################################################################################################


#########################################################################################################
# open a camera divice or video file using opencv.
# input
#    id_cam : string of camera ID or video file path
# output
#    kam : camera handle
#    w_h_cam : the width and height of camera image.        

import cv2


def init_from_cam_or_video(idx_cam_or_video_path):
    if is_video_file(idx_cam_or_video_path):
        path_video = idx_cam_or_video_path
        #print('this is video file : ', path_video)
        kam = cv2.VideoCapture(path_video)
        if kam is None or not kam.isOpened():
            print('Unable to open video file at : ', path_video);   exit()
    else:
        idx_cam = int(idx_cam_or_video_path)
        #print('this is camera index at : ', idx_cam)
        kam = cv2.VideoCapture(idx_cam)
        if kam is None or not kam.isOpened():
            print('Unable to open camera with index : ', idx_cam);   exit()
 
    print('Camera : {} is opened'.format(id_cam)); #exit()
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

#########################################################################################################
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


#########################################################################################################
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

#########################################################################################################
# draw bounding boxes given as xyxy format and show the image with bboxes.
# input
#   im_bgr : image with bgr order
#   li_xyxy : list of bounding box with the format of x_from, y_from, x_to, y_to
#   wait_ms : time for displaying in milli-seconds.        
# output
#   nothing.        

import cv2

def draw_and_show_xyxy_bboxes(im_bgr, li_xyxy, wait_ms=0):
    for x_from, y_from, x_end, y_end in li_xyxy:
        im_bgr = cv2.rectangle(im_bgr, (x_from, y_from), (x_end, y_end), (0, 0, 255), 1)
    cv2.imshow('im_bgr', im_bgr);   cv2.waitKey(wait_ms)  
    

#########################################################################################################
# draw bounding boxes given as ltwh format and show the image with bboxes.
# input
#   im_bgr : image with bgr order
#   li_ltwh : list of bounding box with the format of x_left, y_top, width, height
#   wait_ms : time for displaying in milli-seconds.        
# output
#   nothing.        

import cv2

def draw_and_show_ltwh_bboxes(im_bgr, li_ltwh, wait_ms=0):
    
    li_xyxy = []
    for ltwh in li_ltwh:
        x_from, y_from, wid, hei = ltwh
        x_end, y_end = x_from + wid - 1, y_from + hei - 1
        li_xyxy.append((x_from, y_from, x_end, y_end))
    return draw_and_show_xyxy_bboxes(im_bgr, li_xyxy, wait_ms)


#########################################################################################################
def write_one_frame_to_video(im_bgr, video_writer, dir_vid, id_seq, postphix, fps, wh_img):
    if video_writer is None:
        #id_seq = get_last_directory_name(dir_seq);
        #dir_res = 'result/video/';
        mkdir_if_not_exist(dir_vid);
        path_res = full_path_from_dir_id_extension(dir_vid, id_seq + postphix if postphix else id_seq, '.avi')
        fourcc = cv2.VideoWriter_fourcc(*'MJPG')
        video_writer = cv2.VideoWriter(path_res, fource, fps, wh_img)
    video_writer.write(im_bgr);
    return video_writer
        
    
#########################################################################################################
#def save_one_image_under_directory(im_bgr, id_seq, path_ori_img, postphix):
def save_one_image_under_directory(im_bgr, dir_save, id_seq, path_ori_img, postphix):
    #dir_res = os.path.join('result/sequence/', id_seq)
    dir_res = os.path.join(dir_save, id_seq)
    mkdir_if_not_exist(dir_res)
    id_img = get_exact_file_name_from_path(path_ori_img);
    path_res = full_path_from_dir_id_extension(dir_res, id_img + postphix, 'bmp')
    cv2.imwrite(path_res, im_bgr);
        
      

#######################################################################################################################################
########        skimage related        #######################################################################################
#########################################################################################################


#########################################################################################################
from skimage.filters import threshold_otsu
def otsu_thresholding(im_float, scale_otsu = 1.0):
    print ('threshold_otsu')
    threshold_global_Otsu = threshold_otsu(im_float)
    threshold_global_Otsu *= scale_otsu
    #   thresholding을 한다.
    im_bool = im_float >= threshold_global_Otsu
    return im_bool
    
    
#########################################################################################################
from skimage.transform.integral import integrate
def get_sum_of_rectangle(im_int, x, y, w, h):
    x_f = round_i(x)
    y_f = round_i(y)
    x_t = round_i(x + w) - 1
    y_t = round_i(y + h) - 1
    area =  integrate(im_int, y_f, x_f, y_t, x_t)
    if isinstance(area, (collections.Sequence, np.ndarray)):
        return area[0]
    else:
        return area

    
#########################################################################################################
def is_this_rect_belong_2_blob(im_int, x, y, wid, hei, th_occ_rate):
    h_int, w_int = im_int.shape
    if x + wid < w_int and y + hei < h_int:
        #   점유도를 구한다.
        #im_integral, y_from, x_from, y_to, x_to
        area = get_sum_of_rectangle(im_int, x, y, wid, hei)
        area_tile = wid * hei
        r_occu = float(area) / float(area_tile)
    else:
        r_occu = 0
    #   점유도가 충분히 크면
    return r_occu >= th_occ_rate, r_occu


#########################################################################################################
def is_this_patch_below_threshold(im_e_i, th_n_pxl, x_f, y_f, wid, hei):
    n_pixel = get_sum_of_rectangle(im_e_i, x_f, y_f, wid, hei)
    return n_pixel < th_n_pxl

#########################################################################################################
def is_this_patch_below_or_equal_to_threshold(im_e_i, th_n_pxl, x_f, y_f, wid, hei):
    n_pixel = get_sum_of_rectangle(im_e_i, x_f, y_f, wid, hei)
    return n_pixel <= th_n_pxl

#########################################################################################################
def is_this_patch_above_threshold(im_e_i, th_n_pxl, x_f, y_f, wid, hei):
    return (not is_this_patch_below_or_equal_to_threshold(im_e_i, th_n_pxl, x_f, y_f, wid, hei))

#########################################################################################################
def is_this_patch_above_or_equal_to_threshold(im_e_i, th_n_pxl, x_f, y_f, wid, hei):
    return (not is_this_patch_below_threshold(im_e_i, th_n_pxl, x_f, y_f, wid, hei))

#########################################################################################################
def compute_edge_integral(im_rgb, th_Canny_1 = 130, th_Canny_2 = 230):
    im_tissue_gray = cv2.cvtColor(im_rgb, cv2.COLOR_RGB2GRAY)
    im_edge_255 = cv2.Canny(im_tissue_gray, th_Canny_1, th_Canny_2)
    _, im_edge_bin = cv2.threshold(im_edge_255, 1, 1, cv2.THRESH_BINARY)
    im_uint64_edge_integral = integral_image(im_edge_bin)
    return im_uint64_edge_integral, im_edge_bin



#######################################################################################################################################
########        pytorch related        #######################################################################################
#######################################################################################################################################

#########################################################################################################
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


#########################################################################################################
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

#########################################################################################################
#   Convert the detection result as bouding boxes in the letterbox image to those in the original image.
def torch_tensor_det_letterbox_2_li_ltwh_ori(torch_tensor_det_letterbox, wh_ori, wh_letterbox):
    li_ltwh_ori = []
    w_letterbox, h_letterbox = wh_letterbox
    w_ori, h_ori = wh_ori
    ratio_ori_over_letterbox = max(w_ori / w_letterbox, h_ori / h_letterbox)
    ratio_l, ratio_t = compute_margin_ratio_left_top(wh_ori, wh_letterbox)
    margin_l, margin_t = ratio_l * w_letterbox, ratio_t * h_letterbox
    n_det, n_attr = torch_tensor_det_letterbox.shape
    for idx in range(n_det):
        x_left_letterbox = float(torch_tensor_det_letterbox[idx, 0])
        x_left_letterbox_no_margin = x_left_letterbox - margin_l
     
        x_left_ori = x_left_letterbox_no_margin * ratio_ori_over_letterbox
        y_top_letterbox = float(torch_tensor_det_letterbox[idx, 1])
        y_top_letterbox_no_margin = y_top_letterbox - margin_t
        y_top_ori = y_top_letterbox_no_margin * ratio_ori_over_letterbox

        x_right_letterbox = float(torch_tensor_det_letterbox[idx, 2])
        x_right_letterbox_no_margin = x_right_letterbox - margin_l
        x_right_ori = x_right_letterbox_no_margin * ratio_ori_over_letterbox
        y_bottom_letterbox = float(torch_tensor_det_letterbox[idx, 3])
        y_bottom_letterbox_no_margin = y_bottom_letterbox - margin_t
        y_bottom_ori = y_bottom_letterbox_no_margin * ratio_ori_over_letterbox

        wid_ori = x_right_ori - x_left_ori + 1.0
        hei_ori = y_bottom_ori - y_top_ori + 1.0

        li_ltwh_ori.append([x_left_ori, y_top_ori, wid_ori, hei_ori])
    return li_ltwh_ori

#########################################################################################################
#   'idx_class' is the pre-determined index for detected object class
#   In yolo, 'idx_class' is the last column of 'tensor_det' which can be obtatined by index '-1'
def get_class_string_from_torch_tensor(tensor_det, li_class, idx_class):
    return [li_class[int(tensor_det[idx, idx_class])] for idx in range(len(tensor_det))]

    
