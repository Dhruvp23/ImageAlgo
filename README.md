# ImageAlgo (Software to detect impurity in image)



<p></p>

### Description: I build window base software to detect impurity in image, like any blur patch, mask or any sharp vertical or horizontal edges. I used Qt as front end to build UI and C++ in back end. I deployed in window operating system (ImageAlgo.exe) so Dr and Pathologist can simply use.

### Tech:
- QT Platform for window
- C++
- Raw sample images

### I come up with this during my work, where I see one of my co-worker was spending lots of time to check image quality. If there is lots of information present in image, then its time consuming to analysis image. Sometime bad images passed to AI model gives us incorrect results, so it utmost important to QC images before it feed to model.

<p></p>

### In my project I used QT and build executable for Windows. There are four main files, first is mainwindow.ui, it contains design of my software. The QT has built in features, where you can used button, labels, display views, checkbox to configure your software design and as well as style it. Second file mainwindow.h, its nothing just header file where you find all header files listed. In addition to that, when you build C++ based GUI Qt need main.cpp file by default.

<p></p>

### The main driver is forth file called mainwindow.cpp, where I wrote my C++ code to load image using UI and then performed edge detection on that image and display again result on UI when Detect button was clicked.

<p></p>

### C++ Logic
<p></p>
<img src="/workspaces/99158117/project/load image.jpg" alt="load image" title="Optional title">
<p></p>

### I set event on push button, when it is clicked it will execute above code to load image. Qstring filename is variable that store location of sample image. By using Qfiledialog we can choose different type of images like jpeg, png, tiff etc it also supports other file formats by the help of third party libraries. I passed sample image to Qimage, it will load to display window of UI, I scaled image in height and width using in built function and used smoothtransformation function to smooth transition. The Qpixmap is built in function to paint sample image to UI.

<p></p>

```C
QMatrix3x3 kernel;
        kernel(0, 0) = -1; kernel(0, 1) = -1; kernel(0, 2) = -1;
        kernel(1, 0) = -1; kernel(1, 1) = 8; kernel(1, 2) = -1;
        kernel(2, 0) = -1; kernel(2, 1) = -1; kernel(2, 2) = -1;
```
<p></p>

### I used 3x3 kernel to rollover sample image to calculate pixel value, 2D convolutions like 3x3 convolutions on pix, a 3x3 convolution filter, in preferred will always have a third dimension in length. This filter relies upon on (and is identical to) the quantity of channels of the input image. So, I observe a 3x3x1 convolution filter out on gray-scale pictures (the number of channels = 1) while we practice a 3x3x3 convolution filter out on a colored picture (the number of channels = 3).

<p></p>

```C
// Compute kernel convolution
                float v = kernel(0, 0) * qGray(topLeft) +
                          kernel(0, 1) * qGray(top) +
                          kernel(0, 2) * qGray(topRight) +
                          kernel(1, 0) * qGray(left) +
                          kernel(1, 1) * qGray(center) +
                          kernel(1, 2) * qGray(right) +
                          kernel(2, 0) * qGray(bottomLeft) +
                          kernel(2, 1) * qGray(bottom) +
                          kernel(2, 2) * qGray(bottomRight);
```

<p></p>

### I performed convolution on original image, to covert RGB pix to Greyscale pix using loop. Once image is computed it is passed to UI using edgeSetpixcel.

<p></p>

### This is my actual code; you need QT for window to run it. I do have ImageAlgo.exe that can run on any window OS, let me know if anyone need it, I am happy to share it.

<p></p>

### you can save this file to your local storage, install QT creator for window on machine.
- Open all file in QT creator
- Once environment is setup, execute Run and build command
- Browse sample image
- it will display on view
- once it loads then execute Detect

### ImageAlgo.exe
- Run ImageAlgo.exe and Browse image
- Click Detect to performed detection

<p></p>

### Future version:
- In next version, user will able to select different algorithm for detection (example : Laplacian, frequency, sobel etc.) from drop-down menu
- On top of this user will also be able to save output result into different file format, and with more advance option for control like threshold, size, kernel size and colour channel
