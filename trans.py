import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

# 数据输入
frequency = np.array([750, 775, 800, 840, 960, 900, 940, 950, 960, 970,
                     980, 990, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700])
voltage = np.array([1, 1, 1.2, 1.6, 2, 3.2, 4.6, 4.8, 4.9, 5,
                    4.8, 4.2, 4, 1.6, 1, 1, 1, 1, 1, 1])

# 使用样条插值创建平滑曲线
spl = make_interp_spline(frequency, voltage, k=3)  # k=3表示三次样条插值
frequency_new = np.linspace(frequency.min(), frequency.max(), 500)
voltage_new = spl(frequency_new)

# 绘图
plt.figure(figsize=(8, 6))
plt.plot(frequency_new, voltage_new, label="平滑曲线", color='b')
plt.scatter(frequency, voltage, color='r', zorder=5, label="原始数据点")  # 原始数据点
plt.title("DDS输出信号频率与输出电压幅值关系图")
plt.xlabel("频率 (KHz)")
plt.ylabel("输出电压幅值 (V)")
plt.legend()
plt.grid(True)
plt.show()
