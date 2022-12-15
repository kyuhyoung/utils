#######################################################################################################################################
########        system related        #######################################################################################
#########################################################################################################

#########################################################################################################
# str_ori = 'Beautiful, is; better*than\nugly'
# str_delimiter = '; |, '
# li_str = split_string_by_delimiter(str_ori, str_delimiter)
# print(li_str)
# => ['Beautiful', 'is', 'better', 'than', 'ugly']
import re
def split_string_by_delimiter(str_ori, str_delimiter):
    #li_str = re.split('; |, ',str)
    li_str = re.split(str_delimiter, str_ori)
    return li_str


#########################################################################################################
# $ x = float('nan')
# $ isNaN(x)
# $ => True
# $ isNaN(1.6)
# $ => False  
import math
def isNaN(num):
    return math.isnan(num)


#########################################################################################################
# input
# direc = '/path/to/the/directory'
# remove_directory(direc)  
def remove_directory(direc):
    return shutil.rmtree(direc)

#########################################################################################################
# input
# direc = '/path/to/the/directory'
# rm_directory_if_exist(direc)  
def rm_directory_if_exist(direc):
    if is_this_existing_directory(direc):
        remove_directory(direc)    

#########################################################################################################
# input
# direc = '/path/to/the/directory'
# rm_and_mkdir(direc)  
def rm_and_mkdir(direc):
    rm_directory_if_exist(direc)
    os.makedirs(direc)


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
def filter_coi(li_det, li_class, li_coi, idx_class, device):
    #n_det = len(li_det);
    #print('len(li_det) :', len(li_det));  #exit()
    #print('type(li_det) :', type(li_det));  exit()
    idx_coi = torch.tensor([], dtype=torch.long);
    for idx in range(len(li_det)):
        if li_class[int(li_det[idx, idx_class])] in li_coi:
            idx_coi = torch.cat((idx_coi, torch.tensor([idx])), 0)
    #print('li_det b4 : ', li_det);    
    idx_coi = idx_coi.to(device)
    #t1 = torch.index_select(li_det, 0, idx_coi)
    #print('t1 : ', t1); exit()    
    return torch.index_select(li_det, 0, idx_coi)
    #return list(filter(lambda x: li_class[int(x[idx_class])] in li_coi, li_det)) 


#########################################################################################################
def float3(x):  # format floats to 3 decimals
    return float(format(x, '.3f'))



#########################################################################################################
def is_array_like(obj):
    return hasattr(obj, '__iter__') and hasattr(obj, '__len__')



#########################################################################################################
def is_dict_with_given_keys(di, li_key):
    #print('di : ', di)
    #print('AAA')
    if not any(di):             return False
    #print('BBB')
    if len(di) != len(li_key):  return False
    #print('CCC')
    for key in li_key:
        #print('key : ')
        #print(key)
        if not (key in di):
            return False
    return True


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

def is_this_list_empty(li):
    return (not li)

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

def get_list_of_file_path_under_1st_with_3rd_extension(direc, include_subdirectories, ext = ''):
    li_path_total = []
    is_extension_given = not (is_this_empty_string(ext))
    if include_subdirectories:
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
    else:
        for name_file_dir in os.listdir(direc):
            path_file_dir = os.path.join(direc, name_file_dir)
            if os.path.isfile(path_file_dir):
                if is_extension_given:
                    if name_file_dir.lower().endswith(ext.lower()):
                        li_path_total.append(path_file_dir)
                else:
                    li_path_total.append(path_file_dir)
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
    return (strin in (None, '')) or (not strin.strip())


#########################################################################################################
# input
#   path_dir : string of a directory path.
#       ex) '/mnt/d/images'    
# output
#   boolean whether 'path_dir' is a existing directory.
#       ex) True if '/mnt/d/images' exists.

def is_this_existing_directory(path_dir):
    return os.path.exists(path_dir) and os.path.isdir(path_dir)
    #return os.path.isdir(os.path.expanduser(path_dir))
    #return os.path.isdir(path_dir)

    
#########################################################################################################
# input
#   path_file : string of a file path.
#       ex) '/mnt/d/images/img.bmp'    
# output
#   boolean whether 'path_file' is a existing file.
#       ex) True if '/mnt/d/images/img.bmp' exists.

import os.path
def is_this_existing_file(path_file):
    return os.path.exists(path_file) and os.path.isfile(path_file)


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
import os.path.isfile
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





#########################################################################################################
def merge_divided_detections(det_batch, idx_bbox_from, li_offset_xy, is_whole_included, wh_letterbox, wh_tile, wh_ori, letterbox_type, bbox_type, n_sp):
    '''
    bbox_type : one of 'ltrb' / 'ltwh' / 'xywh'
         for image_i, pred in enumerate(li_det):
                 pred[:, 0] += li_offset_xy[image_i][0]; 
                         pred[:, 1] += li_offset_xy[image_i][1];
                             '''
                                 #im_bgr_resized = cv2.resize(im_bgr_hwc_ori_np, None, fx = ratio_resize, fy = ratio_resize)
                                     
    print_indented(n_sp, 'merge_divided_detections START')
    '''
    print_indented(n_sp + 1, 'is_whole_included :', is_whole_included);  #exit()
    print_indented(n_sp + 1, 'li_offset_xy.shape :', li_offset_xy.shape);  #exit()
    print_indented(n_sp + 1, 'type(li_offset_xy) :', type(li_offset_xy));  #exit()
    print_indented(n_sp + 1, 'det_batch.shape :', det_batch.shape);  #exit()
    print_indented(n_sp + 1, 'bbox_type :', bbox_type);  #exit()
    '''
    #print_indented(n_sp + 1, 'type(im_bgr_hwc_ori_np) :', type(im_bgr_hwc_ori_np)); #exit()
    if isinstance(det_batch, torch.Tensor):
        li_offset_xy = torch.from_numpy(li_offset_xy).to(det_batch)
    #'''
    for image_i, offset_xy in enumerate(li_offset_xy):
        print_indented(n_sp + 2, 'image_i :', image_i, ' / ', len(li_offset_xy))
        #print('offset_xy.shape :', offset_xy.shape);     #exit()
        #print_indented(n_sp + 3, 'offset_xy :', offset_xy);     #exit()
        #offset_xy[0] = 100; offset_xy[1] = 1000;
        #print('offset_xy after :', offset_xy);     #exit()
        #print_indented(n_sp + 3, 'det_batch[image_i, 1, :4] b4 :', det_batch[image_i, 1, :4])
        det_batch[image_i, :, idx_bbox_from : idx_bbox_from + 4] = letterbox_bbox_2_ori_bbox(det_batch[image_i, :, idx_bbox_from : idx_bbox_from + 4], wh_letterbox, wh_tile, letterbox_type, bbox_type, offset_xy, n_sp + 3)
        #det_batch[image_i, :, idx_bbox_from : idx_bbox_from + 2] += offset_xy[:]
        #if 'ltrb' == bbox_type:
        #    det_batch[image_i, :, idx_bbox_from + 2 : idx_bbox_from + 4] += offset_xy[:]
        #print_indented(n_sp + 3, 'det_batch[image_i, 1, :4] after :', det_batch[image_i, 1, :4])
        #print_indented(n_sp + 3, 'offset_xy :', offset_xy)
        #if offset_xy[0] and offset_xy[1]:
        #    exit()
        #print('AAA');   exit()
        #for xy in range(2):     
        #    det_batch[image_i, :, xy] += offset_xy[xy]
    #exit()
    #'''
    if is_whole_included:
        bbox_letterbox = det_batch[-1, :, idx_bbox_from : idx_bbox_from + 4]
        #print_indented(n_sp + 3, 'bbox_type :', bbox_type)
        #print_indented(n_sp + 3, 'bbox_letterbox.shape :', bbox_letterbox.shape);   exit()
        
        #wh_ori = (im_bgr_hwc_ori_np.shape[1], im_bgr_hwc_ori_np.shape[0])
        bbox_ori = letterbox_bbox_2_ori_bbox(bbox_letterbox, wh_letterbox, wh_ori, letterbox_type, bbox_type, (0, 0), n_sp + 2)
        
        ''' 
        iB = 0
        for bbox in bbox_ori:
            dx = abs(126 - bbox[0]);    dy = abs(1367 - bbox[1]);
            if dx < 1 and dy < 1:
                print_indented(n_sp + 4, 'iB :', iB, ', bbox :', bbox, ', objectness : ', det_batch[-1, iB, 4], ', class confidences :', det_batch[-1, iB, 5:])
            iB += 1
        print_indented(n_sp + 3, 'iB :', iB);   #exit()
        '''
        #print_indented(n_sp + 3, 'det_batch[-1, 1, :4] b4 :', det_batch[-1, 1, :4])
        det_batch[-1, :, idx_bbox_from : idx_bbox_from + 4] = bbox_ori
        #print_indented(n_sp + 3, 'det_batch[-1, 1, :4] after :', det_batch[-1, 1, :4])
        #print_indented(n_sp + 3, 'det_batch[len(li_offset_xy) - 1, 1, :4] after :', det_batch[len(li_offset_xy) -1, 1, :4])
    #exit()     
    n_batch, n_det, n_attribute = tuple(det_batch.size())
    n_det_total = n_batch * n_det;
    #print('n_batch : ', n_batch);   print('n_det : ', n_det);   print('n_attribute : ', n_attribute);   print('n_det_total : ', n_det_total);  #exit();
    #det = np.vstack(li_det)
    det_merged = det_batch.view(-1, n_attribute);
    #print('det_merged.size() : ', det_merged.size()); #exit()
    det_merged.unsqueeze_(0)
    return det_merged






#########################################################################################################
def print_indented(n_sp, *args):
    if n_sp >= 0:
        print('  ' * n_sp, *args)


#########################################################################################################
# example
# parser.add_argument("--nice", type=str2bool, nargs='?',
#                        const=True, default=False,
#                        help="Activate nice mode.")
def str2bool(v):
    if isinstance(v, bool):
       return v
    if v.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif v.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Boolean value expected.')    
    
    
    
    
#########################################################################################################################
########        math related        ##################################################################################
########################################################################################################################



#########################################################################################################
#   aa_rad = (1.2443, -1.9191, 0.6236)
#   rpy_rad = angle_axis_2_euler_angles_rpy(aa_rad)
#   rpy_deg = rad2deg(rpy_rad)
#   print('rpy_det :', rpy_deg)
#   rpy_det : (0, 180, 20)

import cv2
def angle_axis_2_euler_angles_rpy(aa_rad):
    rot_mat = np.zeros(shape=(3, 3))
    cv2.Rodrigues(np.array(aa_rad), rot_mat)
    rpy_rad = rotation_matrix_2_euler_angles_rpy(rot_mat)
    return rpy_rad



#########################################################################################################
def ap_per_class(tp, conf, pred_cls, target_cls):
    """ Compute the average precision, given the recall and precision curves.
    Source: https://github.com/rafaelpadilla/Object-Detection-Metrics.
    # Arguments
        tp:    True positives (list).
        conf:  Objectness value from 0-1 (list).
        pred_cls: Predicted object classes (list).
        target_cls: True object classes (list).
    # Returns
        The average precision as computed in py-faster-rcnn.
    """

    # Sort by objectness
    i = np.argsort(-conf)
    tp, conf, pred_cls = tp[i], conf[i], pred_cls[i]

    # Find unique classes
    unique_classes = np.unique(target_cls)

    # Create Precision-Recall curve and compute AP for each class
    ap, p, r = [], [], []
    for c in unique_classes:
        i = pred_cls == c
        n_gt = (target_cls == c).sum()  # Number of ground truth objects
        n_p = i.sum()  # Number of predicted objects

        if n_p == 0 and n_gt == 0:
            continue
        elif n_p == 0 or n_gt == 0:
            ap.append(0)
            r.append(0)
            p.append(0)
        else:
            # Accumulate FPs and TPs
            fpc = (1 - tp[i]).cumsum()
            tpc = (tp[i]).cumsum()

            # Recall
            recall_curve = tpc / (n_gt + 1e-16)
            r.append(recall_curve[-1])

            # Precision
            precision_curve = tpc / (tpc + fpc)
            p.append(precision_curve[-1])

            # AP from recall-precision curve
            ap.append(compute_ap(recall_curve, precision_curve))

            # Plot
            # plt.plot(recall_curve, precision_curve)

    # Compute F1 score (harmonic mean of precision and recall)
    p, r, ap = np.array(p), np.array(r), np.array(ap)
    f1 = 2 * p * r / (p + r + 1e-16)

    return p, r, ap, f1, unique_classes.astype('int32')


#########################################################################################################
def bbox_ios(box_self, box_other, bbox_type, n_sp):
    #print('type(box1) : ', type(box1));     print('type(box2) : ', type(box2)); #exit()
    #print('box1.shape : ', box1.shape);     print('box2.shape : ', box2.shape); #exit()
    # Returns the intersecion over self_area of box_self wrt box_other. box_self is 4, box_other is nx4
    print_indented(n_sp, 'bbox_ios START')
    print_indented(n_sp + 1, 'box_self.shape :', box_self.shape);   #exit();
    print_indented(n_sp + 1, 'box_other.shape :', box_other.shape);   #exit();
    print_indented(n_sp + 1, 'bbox_type :', bbox_type);   #exit();

    box_other = box_other.t()
    # Get the coordinates of bounding boxes
    if 'ltrb' == bbox_type:
        # x1, y1, x2, y2 = box1
        self_x1, self_y1, self_x2, self_y2 = box_self[0], box_self[1], box_self[2], box_self[3]
        other_x1, other_y1, other_x2, other_y2 = box_other[0], box_other[1], box_other[2], box_other[3]
    elif 'xywh' == bbox_type:
        # x, y, w, h = box1
        self_x1, self_x2 = box_self[0] - box_self[2] / 2, box_self[0] + box_self[2] / 2
        self_y1, self_y2 = box_self[1] - box_self[3] / 2, box_self[1] + box_self[3] / 2
        other_x1, other_x2 = box_other[0] - box_other[2] / 2, box_other[0] + box_other[2] / 2
        other_y1, other_y2 = box_other[1] - box_other[3] / 2, box_other[1] + box_other[3] / 2
    
    elif 'ltwh' == bbox_type:
        self_x1, self_y1 = box_self[0], box_self[1]
        self_x2 = self_x1 + box_self[2];    self_y2 = self_y1 + box_self[3]
        other_x1, other_y1 = box_other[0], box_other[1]
        other_x2 = other_x1 + box_other[2]; other_y2 = other_y1 + box_other[3]
    else:
        raise NameError('invalid bbox_type')   
   
    # Intersection area
    #inter_area = (torch.min(b1_x2, b2_x2) - torch.max(b1_x1, b2_x1)).clamp(0) * (torch.min(b1_y2, b2_y2) - torch.max(b1_y1, b2_y1)).clamp(0)
    inter_area = (min(self_x2, other_x2) - torch.max(self_x1, other_x1)).clamp(0) * (min(self_y2, other_y2) - max(self_y1, other_y1)).clamp(0)
    print_indented(n_sp + 1, 'inter_area.shape :', inter_area.shape);   #exit();
    # Self Area
    self_area = (self_x2 - self_x1) * (self_y2 - self_y1) + 1e-16
    print_indented(n_sp, 'bbox_ios END')
    return inter_area / self_area  # ios




#########################################################################################################
def bbox_iou(box1, box2, bbox_type, n_sp):
    # Returns the IoU of box1 to box2. box1 is 4, box2 is nx4
    print_indented(n_sp, 'bbox_iou START')
    #print_indented(n_sp + 1, 'box1.shape :', box1.shape);   #exit();
    #print_indented(n_sp + 1, 'box2.shape :', box2.shape);   #exit();
    ##   box1.shape : torch.Size([7])
    ##   box2.shape : torch.Size([100, 7])
    box2 = box2.t()
    # Get the coordinates of bounding boxes
    if 'ltrb' == bbox_type:
        # x1, y1, x2, y2 = box1
        b1_x1, b1_y1, b1_x2, b1_y2 = box1[0], box1[1], box1[2], box1[3]
        b2_x1, b2_y1, b2_x2, b2_y2 = box2[0], box2[1], box2[2], box2[3]
    elif 'xywh' == bbox_type:
        # x, y, w, h = box1
        b1_x1, b1_x2 = box1[0] - box1[2] / 2, box1[0] + box1[2] / 2
        b1_y1, b1_y2 = box1[1] - box1[3] / 2, box1[1] + box1[3] / 2
        b2_x1, b2_x2 = box2[0] - box2[2] / 2, box2[0] + box2[2] / 2
        b2_y1, b2_y2 = box2[1] - box2[3] / 2, box2[1] + box2[3] / 2
    elif 'ltwh' == bbox_type:
        b1_x1, b1_y1 = box1[0], box1[1]
        b1_x2 = b1_x1 + box1[2];    b1_y2 = b1_y1 + box1[3]
        b2_x1, b2_y1 = box2[0], box2[1]
        b2_x2 = b2_x1 + box2[2];    b2_y2 = b2_y1 + box2[3]
    else:
        raise NameError('invalid bbox_type')   
    # Intersection area
    inter_area = (torch.min(b1_x2, b2_x2) - torch.max(b1_x1, b2_x1)).clamp(0) * (torch.min(b1_y2, b2_y2) - torch.max(b1_y1, b2_y1)).clamp(0)
    #inter_area = (min(b1_x2, b2_x2) - max(b1_x1, b2_x1)).clamp(0) * (min(b1_y2, b2_y2) - max(b1_y1, b2_y1)).clamp(0)
    #print_indented(n_sp + 1, 'inter_area.shape :', inter_area.shape);   #exit();
    ##   inter_area.shape : torch.Size([100])
    # Union Area
    union_area = ((b1_x2 - b1_x1) * (b1_y2 - b1_y1) + 1e-16) + (b2_x2 - b2_x1) * (b2_y2 - b2_y1) - inter_area
    print_indented(n_sp, 'bbox_iou END')
    return inter_area / union_area  # iou



#########################################################################################################
def compute_ap(recall, precision):
    """ Compute the average precision, given the recall and precision curves.
    Source: https://github.com/rbgirshick/py-faster-rcnn.
    # Arguments
        recall:    The recall curve (list).
        precision: The precision curve (list).
    # Returns
        The average precision as computed in py-faster-rcnn.
    """
    # correct AP calculation
    # first append sentinel values at the end

    mrec = np.concatenate(([0.], recall, [1.]))
    mpre = np.concatenate(([0.], precision, [0.]))

    # compute the precision envelope
    for i in range(mpre.size - 1, 0, -1):
        mpre[i - 1] = np.maximum(mpre[i - 1], mpre[i])

    # to calculate area under PR curve, look for points
    # where X axis (recall) changes value
    i = np.where(mrec[1:] != mrec[:-1])[0]

    # and sum (\Delta recall) * prec
    ap = np.sum((mrec[i + 1] - mrec[i]) * mpre[i + 1])
    return ap



#########################################################################################################
def compute_loss(p, targets, model):  # predictions, targets, model
    ft = torch.cuda.FloatTensor if p[0].is_cuda else torch.Tensor
    lxy, lwh, lcls, lconf = ft([0]), ft([0]), ft([0]), ft([0])
    txy, twh, tcls, indices = build_targets(model, targets)

    # Define criteria
    MSE = nn.MSELoss()
    CE = nn.CrossEntropyLoss()  # (weight=model.class_weights)
    BCE = nn.BCEWithLogitsLoss()

    # Compute losses
    h = model.hyp  # hyperparameters
    bs = p[0].shape[0]  # batch size
    k = bs  # loss gain
    for i, pi0 in enumerate(p):  # layer i predictions, i
        b, a, gj, gi = indices[i]  # image, anchor, gridy, gridx
        tconf = torch.zeros_like(pi0[..., 0])  # conf

        # Compute losses
        if len(b):  # number of targets
            pi = pi0[b, a, gj, gi]  # predictions closest to anchors
            tconf[b, a, gj, gi] = 1  # conf
            # pi[..., 2:4] = torch.sigmoid(pi[..., 2:4])  # wh power loss (uncomment)

            lxy += (k * h['xy']) * MSE(torch.sigmoid(pi[..., 0:2]), txy[i])  # xy loss
            lwh += (k * h['wh']) * MSE(pi[..., 2:4], twh[i])  # wh yolo loss
            lcls += (k * h['cls']) * CE(pi[..., 5:], tcls[i])  # class_conf loss

        # pos_weight = ft([gp[i] / min(gp) * 4.])
        # BCE = nn.BCEWithLogitsLoss(pos_weight=pos_weight)
        lconf += (k * h['conf']) * BCE(pi0[..., 4], tconf)  # obj_conf loss
    loss = lxy + lwh + lconf + lcls

    return loss, torch.cat((lxy, lwh, lconf, lcls, loss)).detach()




#########################################################################################################
def compute_offsets_4_mosaicking(min_side, max_side_ratio, min_overlap_ratio, wid, hei, n_sp):
    print_indented(n_sp, 'compute_offsets_4_mosaicking START')
    print_indented(n_sp + 1, 'min_side :', min_side, ', min_overlap_ratio :', min_overlap_ratio, ', wid :', wid, ', hei :', hei)
    #   compute min_side_enough
    max_side = min_side * max_side_ratio
    print_indented(n_sp + 1, 'max_side : ' + str(max_side))
    #   if both w and h is smaller than max_side
    if wid <= max_side and hei <= max_side:
        print_indented(n_sp + 1, "wid <= max_side and hei <= max_side")
        li_offset_x = [0];    li_offset_y = [0];    
        #len_side = -1; 
        len_side = max(wid, hei); 
    #   else if h is smaller than max_side
    elif hei <= max_side:
        print_indented(n_sp + 1, "hei <= max_side")
        li_offset_y = [0];  
        len_side = hei
        n_x = get_num_of_division(wid, len_side, min_overlap_ratio, n_sp + 2) 
        li_offset_x = get_offset_list(wid, len_side, n_x, n_sp + 2)
    #   else if h is smaller than min_side_enough
    elif wid <= max_side:
        print_indented(n_sp + 1, "wid <= max_side")
        li_offset_x = [0]
        len_side = wid
        n_y = get_num_of_division(hei, len_side, min_overlap_ratio, n_sp + 2) 
        li_offset_y = get_offset_list(hei, len_side, n_y, n_sp + 2)
    #   else #  both w and h is larger than min_side_enough
    else:
        print_indented(n_sp + 1, "wid > max_side and hei > max_side")
        n_x, len_side_x = get_num_and_side_length_of_division(wid, min_side, max_side, min_overlap_ratio, n_sp + 2)
        #len_side_x = get_side_length_of_division(wid, n_x, min_overlap_ratio, n_sp + 1)
        #print_indented(n_sp + 2, 'n_x b4 : ' + str(n_x) + ', len_side_x : ' + str(len_side_x))
        n_y, len_side_y = get_num_and_side_length_of_division(hei, min_side, max_side, min_overlap_ratio, n_sp + 2)
        #len_side_y = get_side_length_of_division(hei, n_y, min_overlap_ratio, n_sp + 1)
        #print_indented(n_sp + 2, 'n_y b4 : ' + str(n_y) + ', len_side_y : ' + str(len_side_y)) #exit()
        len_side = math.floor(max([len_side_x, len_side_y]))
        #len_side = math.floor(min([len_side_x, len_side_y]))
        n_x = get_num_of_division(wid, len_side, min_overlap_ratio, n_sp + 2)
        n_y = get_num_of_division(hei, len_side, min_overlap_ratio, n_sp + 2)
        li_offset_x = get_offset_list(wid, len_side, n_x, n_sp + 2)
        li_offset_y = get_offset_list(hei, len_side, n_y, n_sp + 2)
    li_offset_xy = np.floor(list(itertools.product(li_offset_x, li_offset_y)))
    print_indented(n_sp + 1, 'li_offset_xy :'); print(li_offset_xy);
    print_indented(n_sp + 1, 'len_side :', len_side);  #exit(0);
    print_indented(n_sp, 'compute_offsets_4_mosaicking END')
    return li_offset_xy, len_side





#########################################################################################################
#   deg = 180
#   rad = deg2rad(deg)
#   print('deg :', deg, ', rad :', rad)
#   deg : 180, rad : 3.141592
#   deg = (0, 180, 360)
#   rad = deg2rad(deg)
#   print('deg :', deg, ', rad :', rad)
#   deg : (0, 180, 360), rad : (0, 3.141592, 6.2830)

import numpy as np
def deg2rad(deg):
    return np.deg2rad(deg)




#########################################################################################################
#   roll, pitch, yaw = 0, 180, 20
#   roll, pitch, yaw = deg2rad((roll, pitch, yaw))
#   aa_rad = euler_angles_rpy_2_angle_axis((roll, pitch, yaw))
#   print('aa_rad :', aa_rad)
#   aa_rad : (1.2443, -1.9191, 0.6236)

def euler_angles_rpy_2_angle_axis(rpy_rad):
    roll, pitch, yaw = rpy_rad
    yawMatrix = np.matrix([[math.cos(yaw), -math.sin(yaw), 0],
                           [math.sin(yaw), math.cos(yaw), 0], [0, 0, 1]])
    pitchMatrix = np.matrix([[math.cos(pitch), 0,
                              math.sin(pitch)], [0, 1, 0],
                             [-math.sin(pitch), 0,
                              math.cos(pitch)]])
    rollMatrix = np.matrix([[1, 0, 0], [0, math.cos(roll), -math.sin(roll)],
                            [0, math.sin(roll),
                             math.cos(roll)]])
    R = yawMatrix * pitchMatrix * rollMatrix
    theta = math.acos(((R[0, 0] + R[1, 1] + R[2, 2]) - 1) / 2)
    multi = 1 / (2 * math.sin(theta))
    rx = multi * (R[2, 1] - R[1, 2]) * theta
    ry = multi * (R[0, 2] - R[2, 0]) * theta
    rz = multi * (R[1, 0] - R[0, 1]) * theta
    return (rx, ry, rz)



#########################################################################################################
def get_interval(wid, ss, nn, n_sp):
    print_indented(n_sp, 'get_interval START')
    #print_indented(n_sp + 1, 'wid :', wid, ', ss :', ss, ', nn :', nn)
    interval = int(0)
    if nn > 0:
        overlap_ratio = get_overlap_ratio(wid, ss, nn)
        interval = int(round((1.0 - overlap_ratio) * ss))
        #interval = int(round((1.0 - overlap_ratio) * ss))
    #print_indented(n_sp + 1, 'interval : ' + str(interval))
    #exit(0)
    print_indented(n_sp, 'get_interval END')
    return interval


#########################################################################################################
def get_num_of_division(wid, fixed_side, min_overlap_ratio, n_sp):
    n_div = 0
    if wid > fixed_side:
        len_delta = (1.0 - min_overlap_ratio) * fixed_side
        len_cur = fixed_side
        n_div += 1
        while len_cur <= wid:
            len_cur += len_delta
            n_div += 1
        n_div -= 1
    return n_div


#########################################################################################################
def get_offset_list(wid, ss, nn, n_sp):
    print_indented(n_sp, 'get_offset_list START')
    #print_indented(n_sp + 1, 'wid : ' + str(wid) + ', ss : ' + str(ss) + ', nn : ' + str(nn))
    interval = get_interval(wid, ss, nn, n_sp + 1)
    overlap = ss - interval 
    #t0 = get_overlap(wid, ss, nn, n_sp + 1);    print_indented(n_sp + 1, 't0 :', t0)
    #print_indented(n_sp + 1, 'overlap :', overlap, ', interval :', interval);   #exit()
    li = [0]
    while li[-1] + ss < wid:
        li.append(li[-1] + interval)
        dif = wid - (li[-1] + ss)
        #print_indented(n_sp + 2, 'dif : ' + str(dif) + ' / overlap : ' + str(overlap))
        if dif < overlap:
            li[-1] += dif
    print_indented(n_sp + 1, 'li :', li)
    #exit(0)
    print_indented(n_sp, 'get_offset_list END')
    return li


#########################################################################################################
def get_overlap(wid, ss, nn):
    overlap = -1
    if nn > 0:
        overlap_ratio = get_overlap_ratio(wid, ss, nn)
        print('overlap_ratio : ', overlap_ratio); #  exit()
        overlap = overlap_ratio * ss;
    return overlap       



#########################################################################################################
def get_overlap_ratio(wid, ss, nn):
    return 1.0 - (wid - ss) / (nn * ss)


#########################################################################################################
def get_side_length_of_division(wid, nn, overlap_ratio, n_sp):
    print_indented(n_sp, 'get_side_length_of_division START')
    print_indented(n_sp + 1, 'wid : ' + str(wid) + ', nn : ' + str(nn) + ', overlap_ratio : ' + str(overlap_ratio))
    side_len = int(round(wid / (1.0 + nn * (1.0 - overlap_ratio))))
    print_indented(n_sp + 1, 'side_len : ' + str(side_len))
    print_indented(n_sp, 'get_side_length_of_division END')
    return side_len

#########################################################################################################
def get_num_and_side_length_of_division(wid, min_side, max_side, overlap_ratio, n_sp):
    print_indented(n_sp, 'get_num_and_side_length_of_division START')
    print_indented(n_sp + 1, 'wid : ' + str(wid) + ', min_side : ' + str(min_side) + ', max_side : ' + str(max_side) + ', overlap_ratio : ' + str(overlap_ratio))
    if wid <= max_side:
        n_div = 0;  w_pre = wid
    else:       
        n_div = 0    #print
        w_cur = wid;    w_pre = -1;
        while w_cur >= min_side:
            w_pre = w_cur
            n_div += 1
            w_cur = get_side_length_of_division(wid, n_div, overlap_ratio, n_sp + 2)
            print_indented(n_sp + 2, 'n_div : ' + str(n_div) + ', w_cur : ' + str(w_cur))
        n_div -= 1
        if 0 == n_div:
            n_div = 1;  w_pre = min_side
        if w_pre > max_side:
            n_div += 1; w_pre = w_cur
    print_indented(n_sp + 1, 'n_div : ' + str(n_div) + ', w_pre : ' + str(w_pre))
    #exit(0)
    print_indented(n_sp, 'get_num_and_side_length_of_division END')
    return n_div, w_pre






#########################################################################################################
#   rot_mat = np.identity(3, dtype=np.float)
#   is_rot_mat = is_rotation_matrix(rot_mat)
#   print('is_rot_mat :', is_rot_mat)
#   is_rot_mat : 1
#   rot_mat = np.zeros((3, 3), dtype=np.float)
#   is_rot_mat = is_rotation_matrix(rot_mat)
#   print('is_rot_mat :', is_rot_mat)
#   is_rot_mat : 0

import numpy as np
def is_rotation_matrix(R):
    Rt = np.transpose(R)
    shouldBeIdentity = np.dot(Rt, R)
    I = np.identity(3, dtype=R.dtype)
    n = np.linalg.norm(I - shouldBeIdentity)
    return n < 1e-6





#########################################################################################################
def letterbox_bbox_2_ori_bbox(bbox_letterbox, wh_letterbox, wh_ori, letterbox_type, bbox_type, xy_offset, n_sp):
    print_indented(n_sp, 'letterbox_bbox_2_ori_bbox START')
    #print('bbox_letterbox :', bbox_letterbox)
    wh_src = wh_letterbox;  wh_tgt = wh_ori;
    gain = min(wh_src[0] / wh_tgt[0], wh_src[1] / wh_tgt[1])
    bbox_ori = scale_bbox(bbox_letterbox, gain, wh_src, wh_tgt, letterbox_type, bbox_type, n_sp + 1)
    #bbox_ori[:, :2] += xy_offset[:] 
    bbox_ori[:, 0] += xy_offset[0]; bbox_ori[:, 1] += xy_offset[1] 
    if 'ltrb' == bbox_type:
        #bbox_ori[:, 2:4] += xy_offset[:]; 
        bbox_ori[:, 2] += xy_offset[0]; bbox_ori[:, 3] += xy_offset[1]; 
    #print('bbox_ori :', bbox_ori);  #exit(0)
    print_indented(n_sp, 'letterbox_bbox_2_ori_bbox END')
    return bbox_ori

#########################################################################################################
def ori_bbox_2_letterbox_bbox(bbox_ori, wh_ori, wh_letterbox, letterbox_type, n_sp):
    print_indented(n_sp, 'ori_bbox_2_letterbox_bbox START')
    wh_src = wh_ori;    wh_tgt = wh_letterbox;
    gain = max(wh_src[0] / wh_tgt[0], wh_src[1] / wh_tgt[1])
    bbox_letterbox = scale_bbox(bbox_ori, gain, wh_src, wh_tgt, letterbox_type, bbox_type, n_sp + 1)
    print_indented(n_sp, 'ori_bbox_2_letterbox_bbox END')
    return bbox_letterbox







#########################################################################################################
#   rad = math.pi
#   deg = rad2deg(rad)
#   print('rad :', rad, ', deg :', deg)
#   rad : 3.141592, deg : 180
#   rad = (0, math.pi, 2 * math.pi)
#   deg = rad2deg(rad)
#   print('rad :', rad, ', deg :', deg)
#   rad : (0, 3.141592, 6.2830), deg : (0, 180, 360)

import numpy as np
def rad2deg(rad):
    return np.rad2deg(rad)

#########################################################################################################
#   rot_mat = np.identity(3, dtype=np.float)
#   euler_angles = rotation_matrix_2_euler_angles_rpy(rot_mat)
#   print('euler_angles :', euler_angles)
#   euler_angles : [0, 0, 0]

import math
def rotation_matrix_2_euler_angles_rpy(R):
    assert (is_rotation_matrix(R))
    sy = math.sqrt(R[0, 0] * R[0, 0] + R[1, 0] * R[1, 0])
    singular = sy < 1e-6
    if not singular:
        x = math.atan2(R[2, 1], R[2, 2])
        y = math.atan2(-R[2, 0], sy)
        z = math.atan2(R[1, 0], R[0, 0])
    else:
        x = math.atan2(-R[1, 2], R[1, 1])
        y = math.atan2(-R[2, 0], sy)
        z = 0

    return np.array([x, y, z])


#########################################################################################################
def scale_bbox(bbox, gain, wh_src, wh_tgt, letterbox_type, bbox_type, n_sp):
    print_indented(n_sp, 'scale_bbox START')
    #print('bbox b4 :', bbox);
    #print('bbox.shape :', bbox.shape);
    if 'center' == letterbox_type:
        bbox[..., 0] -= (wh_src[0] - wh_tgt[0] * gain) / 2  # x padding
        bbox[..., 1] -= (wh_src[1] - wh_tgt[1] * gain) / 2  # y padding
        if 'ltrb' == bbox_type:
            bbox[..., 2] -= (wh_src[0] - wh_tgt[0] * gain) / 2  # x padding
            bbox[..., 3] -= (wh_src[1] - wh_tgt[1] * gain) / 2  # y padding
    elif not('top_left' == letterbox_type):
        raise NameError('invalid letterbox type')
    bbox[..., :4] /= gain
    bbox[..., [0, 2]] = bbox[..., [0, 2]].clamp(min = 0, max = wh_tgt[0] - 1)
    bbox[..., [1, 3]] = bbox[..., [1, 3]].clamp(min = 0, max = wh_tgt[1] - 1)
    #print('bbox after :', bbox);
    #print('gain :', gain);  #exit(0);
    print_indented(n_sp, 'scale_bbox END')
    return bbox


#########################################################################################################
def wh_iou(box1, box2):
    # Returns the IoU of wh1 to wh2. wh1 is 2, wh2 is nx2
    box2 = box2.t()

    # w, h = box1
    w1, h1 = box1[0], box1[1]
    w2, h2 = box2[0], box2[1]

    # Intersection area
    inter_area = torch.min(w1, w2) * torch.min(h1, h2)

    # Union Area
    union_area = (w1 * h1 + 1e-16) + w2 * h2 - inter_area

    return inter_area / union_area  # iou






###################################################################################################################
#   image related
###################################################################################################################



#########################################################################################################
#   video_2_image_sequence('/home/kevin/video/test.mp4', '/home/kevin/video/img_seq', (10, 10, 1920, 1080))
import os, cv2, sys, shutil
def video_2_image_sequence(fn_vid, dir_seq, xywh_crop):
    cap = cv2.VideoCapture(fn_vid)
    # Check if camera opened successfully
    if (cap.isOpened()== False): 
        print("Error opening video stream or file");    exit(0)
    if os.path.exists(dir_seq):
        shutil.rmtree(dir_seq)
    os.makedirs(dir_seq)     
    if xywh_crop:
        x_crop, y_crop, w_crop, h_crop = xywh_crop[0], xywh_crop[1], xywh_crop[2], xywh_crop[3]
    # Read until video is completed
    cnt = 0;    n_img = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    while(cap.isOpened()):
        # Capture frame-by-frame
        ret, frame = cap.read()       
        if ret == True:
            if xywh_crop:
                frame = frame[y_crop : y_crop + h_crop, x_crop : x_crop + w_crop] 
            fn_img = os.path.join(dir_seq, '%05d.png' % (cnt))
            # save image
            cv2.imwrite(fn_img, frame)
            sys.stdout.write('{} / {} th image saved at {}\r'.format(cnt, n_img, fn_img));  sys.stdout.flush();
        # Break the loop
        else: 
            break
        cnt += 1
    # When everything done, release the video capture object
    cap.release()
    return


#########################################################################################################
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


#########################################################################################################
def aspectcrop(im, wh_2_be):
    thumbwidth, thumbheight = wh_2_be
    #im = Image.open(StringIO(f))
    imagewidth, imageheight = im.size
    dx, dy, cropwidth_plus_dx, cropheight_plus_dy = cropbbox(imagewidth, imageheight, thumbwidth, thumbheight)
    im_cropped = im.crop((dx, dy, cropwidth_plus_dx, cropheight_plus_dy))
    return im_cropped 

#########################################################################################################
def centercrop_and_resize(im, wh_2_be):
    #w_2_be, h_2_be = wh_2_be
    #h_over_w_2_be = h_2_be / w_2_be
    #im_cropped = aspectcrop(im, h_over_w_2_be)
    im_cropped = aspectcrop(im, wh_2_be)
    im_resized = im_cropped.resize(wh_2_be, Image.ANTIALIAS)
    return im_resized



#########################################################################################################
def compensate_division(li_ltrb_c_cc, li_group, li_str_class, ios_threshold, n_sp): # li_ltrb_c_cc : list of torch 2D       tensor
    print_indented(n_sp, 'compensate_division START')
    li_ltrb_c_cc_filtered = []
    #for ii in range(len(li_ltrb_c_cc)):
    #    print_indented(n_sp + 1, 'ii :', ii, ', li_ltrb_c_cc[ii].shape : ', li_ltrb_c_cc[ii].shape);
    #li_id = [int(lrtb_c_cc[0, -1]) for lrtb_c_cc in li_ltrb_c_cc]
    li_id = [int(lrtb_c_cc[-1]) for lrtb_c_cc in li_ltrb_c_cc]
    li_id_unique = list(set(li_id))
    li_id_very_unique = []
    li_li_str_unique = []
    for id_unique in li_id_unique:
        str_cls = li_str_class[id_unique]
        is_new = True
        for li_str_unique in li_li_str_unique:
            if str_cls in li_str_unique:
                is_new = False; break;
        if is_new:
            li_id_very_unique.append(id_unique)
            gr = [str_cls]
            for group in li_group:
                if str_cls in group:
                    gr = group; break;
            li_li_str_unique.append(gr)
    for id_very_unique in li_id_very_unique:
        str_cls = li_str_class[id_very_unique]
        gr = [str_cls]
        for group in li_group:
            if str_cls in group:
                gr = group; break;
        #li_ltrb_c_cc_same_cls = [ltrb_c_cc for ltrb_c_cc in li_ltrb_c_cc if li_str_class[int(ltrb_c_cc[0, -1])]      in gr]
        li_ltrb_c_cc_same_cls = [ltrb_c_cc for ltrb_c_cc in li_ltrb_c_cc if li_str_class[int(ltrb_c_cc[-1])]      in gr]
        if 1 >= len(li_ltrb_c_cc_same_cls):
            li_ltrb_c_cc_filtered.append(li_ltrb_c_cc_same_cls[0]);   continue
        for i0, ltrb_c_cc_same_cls_0 in enumerate(li_ltrb_c_cc_same_cls):
            is_too_included = False
            for i1, ltrb_c_cc_same_cls_1 in enumerate(li_ltrb_c_cc_same_cls):
                #print_indented(n_sp + 1, 'i1 :', i1, ' / ', len(li_ltrb_c_cc_same_cls))
                if i1 == i0: continue
                #ios = float(bbox_ios(torch.squeeze(ltrb_c_cc_same_cls_0), ltrb_c_cc_same_cls_1, 'ltrb', n_sp + 2))
                ios = float(bbox_ios(torch.squeeze(ltrb_c_cc_same_cls_0), ltrb_c_cc_same_cls_1, 'ltrb', -100))
                if ios > ios_threshold:
                    is_too_included = True; break;
            if not is_too_included:
                li_ltrb_c_cc_filtered.append(ltrb_c_cc_same_cls_0)
    print_indented(n_sp + 1, 'len(li_ltrb_c_cc) : ', len(li_ltrb_c_cc))
    print_indented(n_sp + 1, 'len(li_ltrb_c_cc_filtered) : ', len(li_ltrb_c_cc_filtered));   #exit()
    print_indented(n_sp, 'compensate_division END')
    return li_ltrb_c_cc_filtered





#########################################################################################################
def convert_bbox_type(bbox, bbox_type_src, bbox_type_tgt):
    if bbox_type_src != bbox_type_tgt:
        if not(bbox_type_src in ('ltrb', 'ltwh', 'xywh') and bbox_type_tgt in ('ltrb', 'ltwh', 'xywh')):
            raise NameError('Invalid bbox type')
        if 'ltrb' == bbox_type_src:
            if 'ltwh' == bbox_type_tgt:
                bbox = ltrb_2_ltwh(bbox)
            else:
                bbox = ltrb_2_xywh(bbox)
        elif 'ltwh' == bbox_type_src:
            if 'ltrb' == bbox_type_tgt:
                bbox = ltwh_2_ltrb(bbox)
            else:
                bbox = ltwh_2_xywh(bbox)
        else:
            if 'ltrb' == bbox_type_tgt:
                bbox = xywh_2_ltrb(bbox)
            else:
                bbox = xywh_2_ltwh(bbox)
    return bbox                


#########################################################################################################
def letterboxing_pil(image, wh_tgt, letterbox_type, only_return_image = True, means = None, interpolation = None):
    '''resize image with unchanged aspect ratio using padding'''
    #h_src, w_src = image.size
    w_src, h_src = image.size
    w_tgt, h_tgt = wh_tgt
    #scale = min(w/iw, h/ih)
    scale = min(w_tgt / w_src, h_tgt / h_src)
    #nw = int(iw*scale);    nh = int(ih*scale)
    #image = image.resize((nw,nh), Image.BICUBIC)
    if fabs(scale - 1.0) > 1e-5:  
        w_new = int(w_src * scale); h_new = int(h_src * scale)
        if interpolation:
            image = image.resize((w_new, h_new), interpolation)
        else:     
            image = image.resize((w_new, h_new), Image.BICUBIC)
    else:
        w_new = w_src;  h_new = h_src;
    if 'top_left' == letterbox_type:
        x_offset = 0;   y_offset = 0
        x_padding = w_tgt - w_new;  y_padding = h_tgt - h_new;
    elif 'center' == letterbox_type:
        x_offset = (w_tgt - w_new) // 2;    y_offset = (h_tgt - h_new) // 2
        x_padding = x_offset;               y_padding = y_offset;
    else:
        raise NameError('Invalid letterbox_type')      
    if means:
        new_image = Image.new(image.mode, wh_tgt, means)
    else:
        new_image = Image.new(image.mode, wh_tgt)
    #new_image.paste(image, ((w-nw)//2, (h-nh)//2))
    new_image.paste(image, (x_offset, y_offset))    
    if only_return_image:
        return new_image
    else:
        return new_image, w_new, h_new, w_src, h_src, x_padding, y_padding 

#########################################################################################################
def letterboxing_opencv(image, wh_tgt, letterbox_type, n_sp, only_return_image = True, means_4_pad = None, interpolation = None):
    '''resize image with unchanged aspect ratio using padding'''
    print_indented(n_sp, 'letterboxing_opencv START');
    #iw, ih = image.shape[0:2][::-1]
    is_color = len(image.shape) > 2
    h_src, w_src = image.shape[:2]
    w_tgt, h_tgt = wh_tgt
    scale = min(w_tgt / w_src, h_tgt / h_src)
    if abs(scale - 1.0) > 1e-5:  
        w_new = int(w_src * scale); h_new = int(h_src * scale)
        #print('w_new :', w_new);    exit()
        #print('image.shape :', image.shape);    exit()
        if interpolation:
            image = cv2.resize(image, (w_new, h_new), interpolation = interpolation)
        else:     
            image = cv2.resize(image, (w_new, h_new), interpolation = cv2.INTER_CUBIC)
    else:
        w_new = w_src;  h_new = h_src;       
    if 'top_left' == letterbox_type:
        x_offset = 0;   y_offset = 0
        x_padding = w_tgt - w_new;  y_padding = h_tgt - h_new;
    elif 'center' == letterbox_type:
        x_offset = (w_tgt - w_new) // 2;    y_offset = (h_tgt - h_new) // 2
        x_padding = x_offset;               y_padding = y_offset;
    else:
        raise NameError('Invalid letterbox_type')        
    if is_color:
        chn = image.shape[2]
        new_image = np.zeros((h_tgt, w_tgt, chn), np.float32)
    else:
        new_image = np.zeros((h_tgt, w_tgt), np.float32)
        
    #print('new_image.dtype : ', new_image.dtype); exit(); 
    if means_4_pad:
        #new_image.fill(128)
        new_image[...] = means_4_pad
    #new_image[dy:dy+nh, dx:dx+nw,:] = image
    #new_image[y_offset : y_offset + h_new, x_offset : x_offset + w_new, :] = image
    new_image[y_offset : y_offset + h_new, x_offset : x_offset + w_new] = image
    print_indented(n_sp, 'letterboxing_opencv END');
    if only_return_image:
        return new_image
    else:
        return new_image, w_new, h_new, w_src, h_src, x_offset, y_offset 



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
    return fn.lower().endswith(ext)

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

    
    
#########################################################################################################
def non_max_suppression_4_mosaic_ltrb(pred_bbox_c_cc, li_offset_xy, include_original, li_group, wh_net_input, wh_tile, wh_ori, li_str_class, ios_threshold, letterbox_type, bbox_type, use_pytorch_batched_nms, n_sp, conf_thres=0.5, nms_thres=0.5): #pred_letterbox.type() : torch.cuda.FloatTensor

    """
    Input :
            bbox_type : one of 'ltrb' / 'ltwh' / 'xywh'
                pred_xywh_c_cc : tensor. shape (batch_size x N x 85 for yolov3)  85 (= x + y + w + h + 1 objectness + 80 class-confidences for yolov3)
                        li_offset_xy : ndarray.
                            Removes detections with lower object confidence score than 'conf_thres'
                                Non-Maximum Suppression to further filter detections.
                                    Returns detections with shape:
                                            (x1, y1, x2, y2, object_conf, class_conf, class)
                                                """
                                                    #print('type(li_offset_xy) : ', type(li_offset_xy))
                                                        #print('pred_xywh_c_cc.shape :', pred_xywh_c_cc.shape);  exit();
                                                            ##  type(li_offset_xy) :  <class 'numpy.ndarray'>
                                                                ##  pred_xywh_c_cc.shape : torch.Size([3, 5415, 85])
                                                                    
    #if 0 != li_offset_xy.size:
    #print('pred_xywh_c_cc.shape b4 :', pred_xywh_c_cc.shape);  exit();
    #t0 = pred_xywh_c_cc[-1].unsqueeze(0);   print('t0.shape :', t0.shape);  exit();
    #print_indented(n_sp, 'non_max_suppression_4_mosaic START')
    if li_offset_xy is not None and pred_bbox_c_cc.shape[0] > 1:
        #pred_xywh_c_cc = merge_divided_detections(pred_xywh_c_cc[-1].unsqueeze(0), 0, np.empty(shape=[0, 0]), include_original, wh_net_input, im_bgr_hwc_ori_np, letterbox_type, bbox_type, n_sp + 1) 
        pred_bbox_c_cc = merge_divided_detections(pred_bbox_c_cc, 0, li_offset_xy, include_original, wh_net_input, wh_tile, wh_ori, letterbox_type, bbox_type, n_sp + 1) 
    else:
        #print('pred_bbox_c_cc b4 :', pred_bbox_c_cc);   #exit()
        pred_bbox_c_cc = letterbox_bbox_2_ori_bbox(pred_bbox_c_cc, wh_net_input, wh_ori, letterbox_type, bbox_type, (0, 0), n_sp + 1)
        #print('pred_bbox_c_cc after :', pred_bbox_c_cc);   #exit()
    #print('pred_xywh_c_cc.shape after :', pred_xywh_c_cc.shape);  exit();
    min_wh = 2  # (pixels) minimum box width and height
    output = [None] * len(pred_bbox_c_cc)
    for image_i, bbox_c_cc in enumerate(pred_bbox_c_cc):
        print_indented(n_sp + 1, 'image_i :', image_i)
        # Experiment: Prior class size rejection
        # x, y, w, h = pred[:, 0], pred[:, 1], pred[:, 2], pred[:, 3]
        # a = w * h  # area
        # ar = w / (h + 1e-16)  # aspect ratio
        # n = len(w)
        # log_w, log_h, log_a, log_ar = torch.log(w), torch.log(h), torch.log(a), torch.log(ar)
        # shape_likelihood = np.zeros((n, 60), dtype=np.float32)
        # x = np.concatenate((log_w.reshape(-1, 1), log_h.reshape(-1, 1)), 1)
        # from scipy.stats import multivariate_normal
        # for c in range(60):
        # shape_likelihood[:, c] =
        #   multivariate_normal.pdf(x, mean=mat['class_mu'][c, :2], cov=mat['class_cov'][c, :2, :2])
        #print('xywh_c_cc[:, 4].max() :', xywh_c_cc[:, 4].max()
        #print('xywh_c_cc[:, 4].argmax() :', xywh_c_cc[:, 4].argmax())
        #print('xywh_c_cc[xywh_c_cc[:, 4].argmax(), 4] :', xywh_c_cc[xywh_c_cc[:, 4].argmax(), 4]);   exit()
        ##  xywh_c_cc[:, 4].max() : tensor(0.99119, device='cuda:0')
        ##  xywh_c_cc[:, 4].argmax() : tensor(3382, device='cuda:0')
        ##  xywh_c_cc[xywh_c_cc[:, 4].argmax(), 4] : tensor(0.99119, device='cuda:0')
        # Multiply conf by class conf to get combined confidence
        class_conf, class_pred = bbox_c_cc[:, 5:].max(1)
        #print('xywh_c_cc.shape :', xywh_c_cc.shape);
        #print('class_conf.shape :', class_conf.shape);
        #print('class_pred.shape :', class_pred.shape);  exit();
        
        ##  ixywh_c_cc.shape : torch.Size([16245, 85])  #   16245 = 3 x 5415

        ##  class_conf.shape : torch.Size([16245])
        ##  class_pred.shape : torch.Size([16245])
        
        #print_indented(n_sp + 2, 'xywh_c_cc[:, 4].max() b4 :', bbox_c_cc[:, 4].max());
        #xywh_c_cc[:, 4] *= class_conf
        #print_indented(n_sp + 2, 'xywh_c_cc[:, 4].max() after :', bbox_c_cc[:, 4].max());
        #print_indented(n_sp + 2, 'conf_thres :', conf_thres);
        
        # Select only suitable predictions
        i_conf = bbox_c_cc[:, 4] > conf_thres
        if 'xywh' == bbox_type or 'ltwh' == bbox_type:
            i_min_wh = (bbox_c_cc[:, 2 : 4] > min_wh).all(1) 
        else:
            wh = bbox_c_cc[:, [1, 3]] - bbox_c_cc[:, [0, 2]]
            i_min_wh = (wh > min_wh).all(1) 
        i_finite = torch.isfinite(bbox_c_cc).all(1)
        i = i_conf & i_min_wh & i_finite
        #i = (bbox_c_cc[:, 4] > conf_thres) & (bbox_c_cc[:, 2:4] > min_wh).all(1) & torch.isfinite(xywh_c_cc).all(1)
        #print_indented(n_sp + 2, 'class_conf :', class_conf);
        print_indented(n_sp + 2, 'len(bbox_c_cc) b4 :', len(bbox_c_cc))
        bbox_c_cc = bbox_c_cc[i]
        print_indented(n_sp + 2, 'len(bbox_c_cc) after :', len(bbox_c_cc))
        #exit()
        # If none are remaining => process next image
        if len(bbox_c_cc) == 0:
            #print('None are remaining');    exit()
            continue
            
        #print('Some are remaining');    exit()
        # Select predicted classes
        class_conf = class_conf[i]
        #class_pred = class_pred[i].unsqueeze(1).float()
        class_pred = class_pred[i]
        
        # Box (center x, center y, width, height) to (x1, y1, x2, y2)
        ltrb_c_cc = bbox_c_cc.clone()
        #ltrb_c_cc[:, :4] = xywh2xyxy(xywh_c_cc[:, :4])
        #ltrb_c_cc[:, :4] = xywh_2_ltrb(xywh_c_cc[:, :4])
        ltrb_c_cc[:, :4] = convert_bbox_type(bbox_c_cc[:, :4], bbox_type, 'ltrb')
        # pred[:, 4] *= class_conf  # improves mAP from 0.549 to 0.551
        # Detections ordered as (x1y1x2y2, obj_conf, class_conf, class_pred)
        #pred = torch.cat((pred[:, :5], class_conf.unsqueeze(1), class_pred), 1)
        
        det_max = []
        ltrb_c_cc = torch.cat((ltrb_c_cc[:, :5], class_conf.unsqueeze(1), class_pred.unsqueeze(1).float()), 1)
        if use_pytorch_batched_nms and is_batched_nms_available and isinstance(ltrb_c_cc, torch.Tensor):
            anchors_nms_idx = batched_nms(ltrb_c_cc[:, :4], class_conf, class_pred, iou_threshold = nms_thres)
            ltrb_c_cc = ltrb_c_cc[anchors_nms_idx]
            det_max = list(ltrb_c_cc)
        else:
            #ltrb_c_cc = torch.cat((ltrb_c_cc[:, :5], class_conf.unsqueeze(1), class_pred.unsqueeze(1).float()), 1)
            # Get detections sorted by decreasing confidence scores
            #pred = pred[(-pred[:, 4]).argsort()]
            ltrb_c_cc = ltrb_c_cc[(-ltrb_c_cc[:, 4]).argsort()]
            
            #nms_style = 'MERGE'  # 'OR' (default), 'AND', 'MERGE' (experimental)
            nms_style = 'OR'
            #nms_style = 'SOFT'
            #for c in pred[:, -1].unique():
            for c in ltrb_c_cc[:, -1].unique():
                dc = ltrb_c_cc[ltrb_c_cc[:, -1] == c]  # select class c
                n = len(dc)
                if n == 1:
                    #det_max.append(dc)  # No NMS required if only 1 prediction
                    det_max.append(dc.squeeze())  # No NMS required if only 1 prediction
                    continue
                elif n > 100:
                    dc = dc[:100]  # limit to first 100 boxes: https://github.com/ultralytics/yolov3/issues/117
                    
                # Non-maximum suppression
                if nms_style == 'OR':  # default
                    # METHOD1
                    # ind = list(range(len(dc)))
                    # while len(ind):
                    # j = ind[0]
                    # det_max.append(dc[j:j + 1])  # save highest conf detection
                    # reject = (bbox_iou(dc[j], dc[ind], 'ltrb') > nms_thres).nonzero()
                    # [ind.pop(i) for i in reversed(reject)]
                    
                    # METHOD2
                    while dc.shape[0]:
                        #t1 = dc[:1];    print('t1.shape :', t1.shape);  exit()
                        #det_max.append(dc[:1])  # save highest conf detection
                        det_max.append(dc[:1].squeeze())  # save highest conf detection
                        if len(dc) == 1:  # Stop if we're at the last detection
                            break
                        iou = bbox_iou(dc[0], dc[1:], 'ltrb', n_sp + 3)  # iou with other boxes
                        dc = dc[1:][iou < nms_thres]  # remove ious > threshold
                        
                elif nms_style == 'AND':  # requires overlap, single boxes erased
                    while len(dc) > 1:
                        iou = bbox_iou(dc[0], dc[1:], 'ltrb', n_sp + 3)  # iou with other boxes
                        if iou.max() > 0.5:                            
                            det_max.append(dc[:1].squeeze())
                            #det_max.append(dc[:1])
                        dc = dc[1:][iou < nms_thres]  # remove ious > threshold
                            
                elif nms_style == 'MERGE':  # weighted mixture box
                    #print('len(dc) :', len(dc));    exit();
                    while len(dc):
                        if len(dc) == 1:
                            #det_max.append(dc)
                            det_max.append(dc.squeeze())
                            break
                        i = bbox_iou(dc[0], dc, 'ltrb', n_sp + 3) > nms_thres  # iou with other boxes
                        weights = dc[i, 4:5]
                        dc[0, :4] = (weights * dc[i, :4]).sum(0) / weights.sum()
                        #det_max.append(dc[:1])
                        det_max.append(dc[:1].squeeze())
                        dc = dc[i == 0]
                elif nms_style == 'SOFT':  # soft-NMS https://arxiv.org/abs/1704.04503
                    sigma = 0.5  # soft-nms sigma parameter
                    while len(dc):
                        if len(dc) == 1:
                            #det_max.append(dc)
                            det_max.append(dc.squeeze())
                            break
                        #det_max.append(dc[:1])
                        det_max.append(dc[:1].squeeze())
                        iou = bbox_iou(dc[0], dc[1:], 'ltrb', n_sp + 3)  # iou with other boxes
                        dc = dc[1:]
                        dc[:, 4] *= torch.exp(-iou ** 2 / sigma)  # decay confidences
            
        #print_indented(n_sp + 2, 'det_max[0].shape :', det_max[0].shape);   # exit();
        #print_indented(n_sp + 2, 'len(det_max) :', len(det_max));    #exit();
        if include_original:
            #print_indented(n_sp + 3, 'len(det_max) b4 :', len(det_max));    #exit();
            #print_indented(n_sp + 3, 'ios_threshold :', ios_threshold);    exit();
            det_max = compensate_division(det_max, li_group, li_str_class, ios_threshold, n_sp + 3)
            #print_indented(n_sp + 3, 'len(det_max) after :', len(det_max));    #exit();
        if len(det_max):
            #det_max = torch.cat(det_max)  # concatenate
            det_max = torch.stack(det_max)  # concatenate
            #print('det_max.shape :', det_max.shape);    exit()
            output[image_i] = det_max[(-det_max[:, 4]).argsort()]  # sort
    #exit()

    print_indented(n_sp, 'non_max_suppression_4_mosaic END')
    return output

    
    
    
#########################################################################################################
'''
def ltwh_2_xyxy(ltwh):
    xyxy = ltwh.copy()
    xyxy[..., 2] = ltwh[..., 0] + ltwh[..., 2]
    xyxy[..., 3] = ltwh[..., 1] + ltwh[..., 3]
    return xyxy
'''
def ltwh_to_ltrb(ltwh):
    """Convert [x1 y1 w h] box format to [x1 y1 x2 y2] format."""
    if isinstance(ltwh, (list, tuple)):
        # Single box given as a list of coordinates
        assert len(ltwh) == 4
        x1, y1 = xywh[0], ltwh[1]
        x2 = x1 + np.maximum(0., ltwh[2] - 1.)
        y2 = y1 + np.maximum(0., ltwh[3] - 1.)
        return (x1, y1, x2, y2)
    elif isinstance(ltwh, np.ndarray):
        # Multiple boxes given as a 2D ndarray
        
        
        if 2 < ltwh.ndim: 
            shape_ori = ltwh.shape
            n_box = np.prod(shape_ori[:-1])
            ltwh = np.reshape(ltwh, (n_box, shape_ori[-1]))
            t0 = np.hstack((ltwh[:, 0:2], ltwh[:, 0:2] + np.maximum(0, ltwh[:, 2:4] - 1))      
            return np.reshape(t0, shape_ori)
        else: 
            return np.hstack((ltwh[:, 0:2], ltwh[:, 0:2] + np.maximum(0, ltwh[:, 2:4] - 1))
    else:
        raise TypeError('Argument xywh must be a list, tuple, or numpy array.')


#########################################################################################################
def plot_one_box(no_disp, x, img, color=None, label=None, line_thickness=None):
    if not no_disp:
        # Plots one bounding box on image img
        #tl = line_thickness or round(0.002 * max(img.shape[0:2])) + 1  # line thickness
        tl = line_thickness or max(round(0.001 * max(img.shape[0:2])), 1)  # line thickness
        color = color or [random.randint(0, 255) for _ in range(3)]
        c1, c2 = (int(x[0]), int(x[1])), (int(x[2]), int(x[3]))
        cv2.rectangle(img, c1, c2, color, thickness=tl)
        if label:
            tf = max(tl - 1, 1)  # font thickness
            #tf = max(tl - 4, 1)  # font thickness
            #print('tl - 4 : ', tl - 4)  # font thickness
            #phontScale = tl / 3
            phontScale = tl / 2
            t_size = cv2.getTextSize(label, 0, fontScale=phontScale, thickness=tf)[0]
            c2 = c1[0] + t_size[0], c1[1] - t_size[1] - 3
            cv2.rectangle(img, c1, c2, color, -1)  # filled
            cv2.putText(img, label, (c1[0], c1[1] - 2), 0, phontScale, [225, 255, 255], thickness=tf, lineType=cv2.LINE_AA)


                             
    
#########################################################################################################
'''
def xyxy_2_ltwh(xyxy):
    ltwh = xyxy.copy()
    ltwh[..., 2] = xyxy[..., 2] - xyxy[..., 0]
    ltwh[..., 3] = xyxy[..., 3] - xyxy[..., 1]
    return ltwh
'''

#########################################################################################################
def ltrb_2_ltwh(ltrb):
    ltwh = copy.deepcopy(ltrb)
    ltwh[..., 2] = ltrb[..., 2] - ltrb[..., 0]
    ltwh[..., 3] = ltrb[..., 3] - ltrb[..., 1]
    return ltwh

#########################################################################################################
def ltrb_2_xywh(ltrb):
    xywh = copy.deepcopy(ltrb)
    '''
    if isinstance(ltrb, torch.Tensor):
        xywh = ltrb.new(ltrb.shape)
    else:
        xywh = ltrb.copy() 
    '''    
    xywh[..., 0] = (ltrb[..., 0] + ltrb[..., 2]) / 2.0
    xywh[..., 1] = (ltrb[..., 1] + ltrb[..., 3]) / 2.0
    xywh[..., 2] = ltrb[..., 2] - ltrb[..., 0]
    xywh[..., 3] = ltrb[..., 3] - ltrb[..., 1]
    return xywh

#########################################################################################################
def ltwh_2_ltrb(ltwh):
    #ltrb = ltwh.copy()
    ltrb = copy.deepcopy(ltwh)
    ltrb[..., 2] = ltwh[..., 0] + ltwh[..., 2]
    ltrb[..., 3] = ltwh[..., 1] + ltwh[..., 3]
    return ltrb

#########################################################################################################
def ltwh_2_xywh(ltwh):
    #xywh = ltwh.copy()
    xywh = copy.deepcopy(ltwh)
    xywh[..., 0] = ltwh[..., 0] + ltwh[..., 2] / 2.0
    xywh[..., 1] = ltwh[..., 1] + ltwh[..., 3] / 2.0
    return xywh

                             
                             
def split_image_into_left_and_right(im_ori_bgr):
    #fn_right = full_path_from_dir_id_extension(dir_save, id_img + '_right', ext)
    wid_half = round_i(float(im_ori_bgr.shape[1]) / 2.0) 
    return im_ori_bgr[:, : wid_half, :], im_ori_bgr[:, wid_half :, :]

def split_image_into_up_and_down(im_ori_bgr):
    hei_half = round_i(float(im_ori_bgr.shape[0]) / 2.0) 
    return im_ori_bgr[: hei_half, :, :], im_ori_bgr[hei_half :, :, :]

def split_image_into_left_and_right_then_save(fn_ori, dir_save, ext):
    id_img = get_exact_file_name_from_path(fn_ori)
    fn_left = full_path_from_dir_id_extension(dir_save, id_img + '_left', ext)
    fn_right = full_path_from_dir_id_extension(dir_save, id_img + '_right', ext)
    im_ori_bgr = cv2.imread(fn_ori)
    im_l_bgr, im_r_bgr = split_image_into_left_and_right(im_ori_bgr);
    #cv2.imshow('im_l_bgr', im_l_bgr);   cv2.imshow('im_r_bgr', im_r_bgr);   cv2.waitKey(0)
    distutils.dir_util.mkpath(dir_save)
    cv2.imwrite(fn_left, im_l_bgr); cv2.imwrite(fn_right, im_r_bgr)
    #print('Left image size : ', im_l_bgr.shape);  print('Right image size : ', im_r_bgr.shape); print('Left image is saved at : ', fn_left);  print('Right image is saved at : ', fn_right); #exit()
    return

def split_image_into_up_and_down_then_save(fn_ori, dir_save, ext):
    id_img = get_exact_file_name_from_path(fn_ori)
    fn_above = full_path_from_dir_id_extension(dir_save, id_img + '_above', ext)
    fn_low = full_path_from_dir_id_extension(dir_save, id_img + '_low', ext)
    im_ori_bgr = cv2.imread(fn_ori);
    im_a_bgr, im_l_bgr = split_image_into_up_and_down(im_ori_bgr);
    #cv2.imshow('im_a_bgr', im_a_bgr);   cv2.imshow('im_l_bgr', im_l_bgr);   cv2.waitKey(0)
    distutils.dir_util.mkpath(dir_save)
    cv2.imwrite(fn_above, im_a_bgr); cv2.imwrite(fn_low, im_l_bgr)
    #print('Upper image is saved at : ', fn_above);  print('Lower image is saved at : ', fn_low)
    return
                          
                             
def xywh_2_ltrb(xywh):             
    #ltrb = xywh.new(xywh.shape)
    ltrb = copy.deepcopy(xywh)
    ltrb[..., 0] = xywh[..., 0] - xywh[..., 2] / 2.0
    ltrb[..., 1] = xywh[..., 1] - xywh[..., 3] / 2.0
    ltrb[..., 2] = xywh[..., 0] + xywh[..., 2] / 2.0
    ltrb[..., 3] = xywh[..., 1] + xywh[..., 3] / 2.0
    return ltrb

def xywh_2_ltwh(xywh):             
    #ltwh = xywh.copy()
    ltwh = copy.deepcopy(xywh)
    ltwh[..., 0] = xywh[..., 0] - xywh[..., 2] / 2.0
    ltwh[..., 1] = xywh[..., 1] - xywh[..., 3] / 2.0
    return ltwh

                             
                             
                             
                             
                             
                             
                             
                             
                             
                             
                             

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

    
                             
        
