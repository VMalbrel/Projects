import cv2
import numpy as np
import pandas as pd


# Constants
file_path = 'C:\\Users\\Malbr\\Desktop\\Image_Processing\\SW\\Circular\\'
filename_video = file_path + 'Videos\\Circular - 1-4 by 1-2 - Straight & 1-4 by 1-2 - Straight - Diagonal.avi'
filename_excel = file_path + 'Data\\Circular - 1-4 by 1-2 - Straight & 1-4 by 1-2 - Straight - Diagonal.csv'

# Get video
cap = cv2.VideoCapture(filename_video, 0) # Get video from camera

# Video Specific Data Gathering
total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
fps = int(cap.get(cv2.CAP_PROP_FPS))
total_time = round(total_frames / fps)
total_res = [int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))]

# Initialization
frame_num = 0
escaped = False
cropped = False

# Crop Coordinates
if cropped == True:
    # Calibrated for 25% 1000x1000 pixels 
    x_top = int(.25*total_res[0])+2
    y_top = int(.25*total_res[1])+2
    x_bottom = int(.75*total_res[0])-2
    y_bottom = int(.75*total_res[1])-2
else:
    x_top = total_res[0]
    y_top = total_res[1]
    x_bottom = total_res[0]
    y_bottom = total_res[1]
top_left = (x_top, y_top)
bottom_right = (x_bottom, y_bottom)

# Array Creation
light_array = ([])
angle_array = np.linspace(0, 360, total_frames)
time_array = list(np.linspace(0, total_time, total_frames))
    
# Crop Image
def crop_tool(frame, top_left, bottom_right):
    if cropped == True:
        top_left = list(top_left) # Convert to list
        bottom_right = list(bottom_right) # Convert to list
        crop = frame[top_left[1]:bottom_right[1], top_left[0]:bottom_right[0]] # Crop Image
        top_left = tuple(top_left) # Convert to tuple
        bottom_right = tuple(bottom_right) # Convert to tuple
    else:
        crop = frame # No Crop
    return crop  

# Create Light Array
def light_arrays(crop, light_array):
    light = np.mean(crop) # Calculate average light value in cropped area
    light_array = np.append(light_array, light) # Add instaneous light value to light array
    return light_array

# Display Original
def display_original(frame, top_left, bottom_right):
    rect_color = (255, 255, 255) # Create Rectangle
    cv2.rectangle(frame, top_left, bottom_right, rect_color, 3) # Cropping rectangle added to frame
    cv2.imshow('video', cv2.resize(frame, (500,500))) # Show resized display image

# Display Crop
def display_crop(frame, top_left, bottom_right):
    crop = crop_tool(frame, top_left, bottom_right) # Crop to area of interest
    cv2.imshow('Crop', cv2.resize(crop, (500,500))) # Cropped video feed

while frame_num < total_frames: 
    # Read individual frames
    ret, frame = cap.read() 
    if cap.read == False:
        break
    
    # Convert frame to binary
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)  
    ret, frame = cv2.threshold(frame, 127, 255, cv2.THRESH_BINARY)

    # Mask
    # mask = np.full((int(total_res[0]), int(total_res[1])), 0, dtype="uint8")
    # cv2.circle(mask, (int(total_res[0]/2), int(total_res[1]/2)), int(total_res[0]/2)-1, 0,-1)
    # frame = np.add(frame,mask)
    
    # Croping
    crop = crop_tool(frame, top_left, bottom_right) # Crop to area of interest

    # Light and Time Arrays
    light_array = light_arrays(crop, light_array) # Get back time and light data
    
    # Displays
    # display_crop(frame, top_left, bottom_right) # Display cropped view
    display_original(frame, top_left, bottom_right) # Display current view

    if cv2.waitKey(1) & 0xFF == ord('\x1b'):
        escaped = True
        break

    # Frame Counter
    frame_num+=1

# End
cap.release()
cv2.destroyAllWindows()

# Open Area Conversion
open_area_array = (light_array / 255) * 100

# Create CSV Document
if escaped == False:
    # Send to Excel
    dict = {'time': time_array[0:len(open_area_array)], 'angle': angle_array[0:len(open_area_array)], 'open area': open_area_array}
    dataframe = pd.DataFrame(dict)
    dataframe.to_csv(filename_excel)
    print("Excel File Succesfuly Created")
else:
    print("Escaped Pre-emptively")
