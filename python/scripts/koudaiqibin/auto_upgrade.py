import pyautogui
import time

# 设置执行速度和失败安全措施
pyautogui.PAUSE = 0.1  # 每次PyAutoGUI调用后暂停0.1秒
pyautogui.FAILSAFE = True  # 启用鼠标移到屏幕左上角退出

# 定义坐标位置 (根据你的实际位置修改这些值)
COORD_build = (2970, 1940)    # 建造按钮
COORD_arsenal = (3200, 1940)  # 兵工厂按钮
run_times  = 140  # 点击次数



COORD_some_arsenal = (1442, 823)  # 具体兵工厂，需要长按的坐标
COORD_delete = (1506, 753)  # 删除
COORD_blank = (1506, 600)  # 最后点击的坐标


def main():
    print("脚本将在 1 秒后开始，请将鼠标移到左上角终止程序...")
    time.sleep(0.1)

    # 第一部分：点击坐标A 72次，每次间隔0.5秒
    # 点击建造
    pyautogui.click(COORD_build[0], COORD_build[1])
    time.sleep(0.2)
    print(f"开始在坐标 {COORD_arsenal} 点击140次...")
    for i in range(run_times):
        pyautogui.click(COORD_arsenal[0], COORD_arsenal[1])
        print(f"已完成 {i + 1}/140 次点击")
        time.sleep(0.03)  # 0.5秒间隔

    # # 第二部分：长按坐标B 1秒
    # print(f"在坐标 {COORD_some_arsenal} 长按2秒...")
    # pyautogui.mouseDown(COORD_some_arsenal[0], COORD_some_arsenal[1])
    # time.sleep(2)
    # pyautogui.mouseUp()
    #
    # # 第三部分：点击坐标C
    # print(f"点击坐标 {COORD_delete}")
    # pyautogui.click(COORD_delete[0], COORD_delete[1])
    # time.sleep(0.5)
    #
    # print(f"点击空白位置 {COORD_blank}")
    # pyautogui.click(COORD_blank[0], COORD_blank[1])
    # time.sleep(0.5)

    print("脚本执行完成！")


if __name__ == "__main__":
    main()