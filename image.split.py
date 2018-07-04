import os

import sys

extract_all_frame_cmd_format = "ffmpeg -ss 00:03:05 -t 00:00:02 -i mda-hjqstskhxd3d32kq.mp4 -vcodec copy -acodec copy output.mp4"

extract_key_frame_cmd_format = \
    "ffprobe -select_streams v -show_frames -show_entries frame=pict_type -of csv {} | grep -n I | cut -d ':' -f 1"

if __name__ == "__main__":
    input_image = sys.argv[1]
    output_dir = sys.argv[2]

    image_name = input_image.replace(".mp4", "")
    base_dir = "{}/{}".format(output_dir, image_name)
    if not os.path.exists(base_dir):
        os.makedirs(base_dir)

    cmd = extract_all_frame_cmd_format.format(input_image, output_dir, image_name)
    print(os.popen(cmd).readlines())

    cmd = extract_key_frame_cmd_format.format(input_image)
    key_frames = os.popen(cmd).readlines()

    for i in range(len(key_frames)):
        key_frame_index = key_frames[i].replace("\n", "")
        print ("seq=%s, frame=%s" % (i + 1, key_frame_index))
        sub_dir = "{}/{}_{}/input4/".format(output_dir, image_name, key_frame_index)

        if not os.path.exists(sub_dir):
            os.makedirs(sub_dir)

        for index in range(int(key_frame_index), int(key_frame_index) + 100):
            cmd = ("cp -f {}/frame-{}.png {}".format(base_dir, index, sub_dir))
            print(cmd)
            os.system(cmd)
