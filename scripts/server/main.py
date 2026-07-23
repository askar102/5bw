import os
import uvicorn
import shutil
import time
import mimetypes
from zipfile import ZipFile
from fastapi import FastAPI, HTTPException, UploadFile, Form
from fastapi.responses import FileResponse, RedirectResponse
from fastapi.staticfiles import StaticFiles
from utility import rm_extra_dirs, get_html_name
from typing import Optional

mimetypes.add_type("application/wasm", ".wasm")

app = FastAPI()

UPLOAD_FOLDER = 'uploads/'
PORT = 8989

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.post("/upload_test")
async def upload_file(file: UploadFile, extra_data: Optional[str] = Form(None)):
    if not file.filename.endswith('.zip'):
        raise HTTPException(status_code=400, detail="Invalid file type. Only ZIP files are allowed.")

    curr_time = str(int(time.time()))
    file_location = os.path.join(UPLOAD_FOLDER, curr_time + ".zip")
    with open(file_location, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    host = "host.docker.internal" if extra_data == "docker" else "127.0.0.1"

    return {
                "info": f"File '{file.filename}' uploaded successfully",
                "url": f"http://{host}:{PORT}/get_test/{curr_time}"
            }


@app.get("/view/{timestamp}/{file_path:path}")
async def get_view(timestamp: int, file_path: str):
    full_path = os.path.join("view", str(timestamp), file_path)
    if not os.path.exists(full_path):
        raise HTTPException(status_code=404, detail="Not found.")
    return FileResponse(full_path)
    

@app.get("/get_test/{timestamp}")
async def get_test(timestamp: int):
    file_location = os.path.join(UPLOAD_FOLDER, f"{timestamp}.zip")
    view_location = os.path.join("view", str(timestamp))

    if os.path.exists(view_location):
        return RedirectResponse(url=f"/view/{timestamp}/{get_html_name(view_location)}")

    if not os.path.exists(file_location):
        raise HTTPException(status_code=404, detail="Not found.")

    with ZipFile(file_location, "r") as zip:
            zip.extractall(path=view_location)
            rm_extra_dirs(view_location)

    return RedirectResponse(url=f"/view/{timestamp}/{get_html_name(view_location)}")
    
    

if __name__ == "__main__":
    uvicorn.run(app=app, port=PORT)
