from PIL import Image

# 加载图片，并确保图片大小与FPGA显示分辨率相符（例如640x480）
img = Image.open("3.jpg")
img = img.resize((640, 480))  # 假设目标分辨率是640x480

# 将图片转换为RGB格式
img = img.convert("RGB")

# 打开一个Verilog文件，用于存储生成的ROM数据
with open("image_rom.v", "w") as f:
    f.write("module image_rom (\n")
    f.write("    input wire [18:0] addr,\n")
    f.write("    output reg [23:0] data\n")
    f.write(");\n\n")
    f.write("always @(*) begin\n")
    f.write("    case (addr)\n")

    addr = 0
    for y in range(480):
        for x in range(640):
            r, g, b = img.getpixel((x, y))
            rgb_value = (r << 16) | (g << 8) | b
            f.write(f"        19'd{addr}: data = 24'h{rgb_value:06X}; // Pixel ({x}, {y})\n")
            addr += 1

    f.write("        default: data = 24'h000000;\n")
    f.write("    endcase\n")
    f.write("end\n\n")
    f.write("endmodule\n")

print("ROM Verilog file generated: image_rom.v")
