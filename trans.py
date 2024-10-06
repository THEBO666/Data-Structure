from PIL import Image

def convert_image_to_pixels(image_path):
    # 打开图像
    img = Image.open(image_path)
    # 调整图像大小
    img = img.resize((800, 600))
    # 将图像转换为RGB格式
    img = img.convert('RGB')
    # 获取图像的所有像素值
    pixels = list(img.getdata())
    # 将RGB格式转换为BGR格式
    pixels = [(b, g, r) for (r, g, b) in pixels]
    return pixels

def save_pixels_to_c_header(pixels, header_path):
    # 开始写入C头文件
    with open(header_path, 'w') as f:
        f.write('const unsigned char gImage_pic_800_600[] = {\n')
        for pixel in pixels:
            # 将每个像素的BGR值转换为无符号字符，并写入文件
            f.write('{}, {}, {},\n'.format(pixel[0], pixel[1], pixel[2]))
        f.write('};\n')

# 使用函数
pixels = convert_image_to_pixels('3.jpg')
save_pixels_to_c_header(pixels, 'gImage_my_pic.h')