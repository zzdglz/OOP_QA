# This page lists the useful opensource projects in C++, along with a description of the project's purpose. 

## [OpenCV](https://opencv.org/opencv-4-3-0/)

​	OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library. The library has more than 2500 optimized algorithms, which includes a comprehensive set of both classic and state-of-the-art computer vision and machine learning algorithms. These algorithms can be used to detect and recognize faces, identify objects, classify human actions in videos, track camera movements, track moving objects, extract 3D models of objects, produce 3D point clouds from stereo cameras, stitch images together to produce a high resolution image of an entire scene, find similar images from an image database, etc.

```c++
// example
void Visualization::draw_single_line(cv::Mat& img, cv::Point2d start,
                                     cv::Point2d end, cv::Scalar scalar) {
  // width of line
  int thickness = 1;
  int lineType = cv::LineTypes::LINE_8;
  // draw the line between start and end
  cv::line(img, start, end, scalar, thickness, lineType);
}
```

### 