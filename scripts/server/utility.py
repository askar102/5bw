import os
import shutil
from pathlib import Path

def rm_extra_dirs(root: str) -> None:
    current = root
    chain = [root]

    while True:
        entries:list[str] = os.listdir(current)
        if len(entries) == 1:
            only_item = os.path.join(current, entries[0])
            if os.path.isdir(only_item):
                current = only_item
                chain.append(current)
                continue

        break

    print(1)

    if current == root:
        return

    for item in os.listdir(current):
        shutil.move(os.path.join(current, item), os.path.join(root, item))

    for folder in chain[:0:-1]: # (root, end]
        if folder != root:
            os.rmdir(folder)


def get_html_name(root: str) -> str:
    path = Path(root)

    for root, dirs, files in os.walk(path):
        for file in files:
            if file.endswith(".html"):
                return file