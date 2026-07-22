import os
import uvicorn
import shutil
from zipfile import ZipFile
from fastapi import FastAPI, HTTPException, UploadFile

app = FastAPI()

UPLOAD_FOLDER = 'uploads/'

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.post("/upload_test")
async def upload_file(file: UploadFile):
    if not file.filename.endswith('.zip'):
        raise HTTPException(status_code=400, detail="Invalid file type. Only ZIP files are allowed.")
    
    file_location = os.path.join(UPLOAD_FOLDER, file.filename)
    with open(file_location, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    with ZipFile("uploads/build.zip", "r") as zip:
        # for root, dirs, files in os.walk(file_location):
        #     for file in files:
        #         print(file.filename)

        zip.extractall(path="uploads_test")

    return {"info": f"File '{file.filename}' uploaded successfully"}


if __name__ == "__main__":
    uvicorn.run(app=app, port=8989)
