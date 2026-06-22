import subprocess
import time
import os
from tkinter import BooleanVar

try: from tqdm import tqdm
except ImportError: 
    subprocess.run(['pip', 'install', 'tqdm'], check=True, capture_output=True, text=True)
    from tqdm import tqdm

stages = [
    "Configuring project...",
    "Building target...",
    "Trying to run your fucking game...",
    "Finished successfully!",
    "Finished with error!"
]

with tqdm(total=4, bar_format="{l_bar}{bar:10}{r_bar}{bar:-10b}") as pbar:
    error = False;

    pbar.set_description("Building project...")
    for i, stage_text in enumerate(stages):
        time.sleep(0.1)
        
        if i == 1: 
            pbar.set_description(stage_text)
            try:
                subprocess.run(['cmake', '-S', '.', '-B', 'build'], check=True, capture_output=True, text=True)
            except subprocess.CalledProcessError as e:
                tqdm.write(f"CMake configuration failed:\nCode: {e.returncode}\nError: {e.stderr}")
                break

            except FileNotFoundError:
                tqdm.write("Error: 'cmake' command not found in your PATH.")
                break

        if i == 2:
            pbar.set_description(stage_text)
            try:
                subprocess.run(['cmake', '--build', 'build'], check=True, capture_output=True, text=True)
            except subprocess.CalledProcessError as e:
                pbar.set_description(f"CMake build failed. Running build.bat for more details..")
                error = True
                subprocess.run([os.path.join(".", "build.bat") ])

        if i == 3:
            pbar.set_description(stage_text)
            exe_path = os.path.join("build", "5bw12.exe") 
            
            try:
                subprocess.run([exe_path], check=True)
            except subprocess.CalledProcessError as e:
                tqdm.write(f"Failed to run game. Code: {e.returncode}")
            except FileNotFoundError:
                tqdm.write(f"Error: Executable not found at {exe_path}")

        if i == 4:
            if (error): ++i
            pbar.set_description(stage_text)

        if i == 5:
            pbar.set_description(stage_text)

        pbar.update(1)
