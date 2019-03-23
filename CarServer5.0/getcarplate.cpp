#include "getcarplate.h"
#include  <QDebug>
GetCarPlate::GetCarPlate()
{
    showSteps = false;
    saveRecognition = true;
}
vector<Plate> GetCarPlate::Contour(cv::Mat &input) {

            vector<Plate> output;
            // 阈值分割得到二值图像，所采用的阈值由Otsu算法得到
            //n图像转换为灰度图
            Mat grayImage;

            cvtColor(input, grayImage, CV_BGR2GRAY);

            blur(grayImage, grayImage, Size(5, 5));  // 对图像进行滤波，去除噪声

            // 通常车牌拥有显著的边缘特征，这里使用sobel算子检测边缘
            Mat sobelImage;
            Sobel(grayImage,       // 输入图像
                  sobelImage,      // 输出图像
                  CV_8U,           //输出图像的深度
                  1,               // x方向上的差分阶数
                  0,               // y方向上的差分阶数
                  3,               // 扩展Sobel核的大小，必须是1,3,5或7
                  1,               // 计算导数值时可选的缩放因子，默认值是1
                  0,               // 表示在结果存入目标图之前可选的delta值，默认值为0
                  BORDER_DEFAULT); // 边界模式，默认值为BORDER_DEFAULT
            if (showSteps)
                imshow("Sobel", sobelImage);
        Mat thresholdImage;
        // 输入一幅8位图像，自动得到优化的阈值
        threshold(sobelImage, thresholdImage, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
        if (showSteps)
            imshow("Threshold Image", thresholdImage);
        // 形态学之闭运算
            // 定义一个结构元素structuringElement，维度为17*3
            Mat structuringElement = getStructuringElement(MORPH_RECT, Size(17, 3));
            // 使用morphologyEx函数得到包含车牌的区域（但不包含车牌号）
            morphologyEx(thresholdImage, thresholdImage, CV_MOP_CLOSE, structuringElement);
            if (showSteps)
                imshow("Close", thresholdImage);
        // 找到可能的车牌的轮廓
        vector< vector< Point> > contours;
        findContours(thresholdImage,
                     contours, // 检测的轮廓数组，每一个轮廓用一个point类型的vector表示
                     CV_RETR_EXTERNAL, // 表示只检测外轮廓
                     CV_CHAIN_APPROX_NONE); // 轮廓的近似办法，这里存储所有的轮廓点

        // 对每个轮廓检测和提取最小区域的有界矩形区域
        vector<vector<Point> >::iterator itc = contours.begin();
        vector<RotatedRect> rects;
        // 若没有达到设定的宽高比要求，移去该区域
        while (itc != contours.end())
        {
            RotatedRect ROI = minAreaRect(Mat(*itc));
            if (!verifySizes(ROI)){
                itc = contours.erase(itc);
            }
            else{
                ++itc;
                rects.push_back(ROI);
            }
        }

        // 在白色的图上画出蓝色的轮廓
        cv::Mat result;
        input.copyTo(result);
        cv::drawContours(result,
                         contours,
                         -1,                    // 所有的轮廓都画出
                         cv::Scalar(255, 0, 0), // 颜色
                         1);                    // 线粗

        // 使用漫水填充算法裁剪车牌获取更清晰的轮廓
        for (int i = 0; i< rects.size(); i++){

            circle(result, rects[i].center, 3, Scalar(0, 255, 0), -1);
            // 得到宽度和高度中较小的值，得到车牌的最小尺寸
            float minSize = (rects[i].size.width < rects[i].size.height) ? rects[i].size.width : rects[i].size.height;
            minSize = minSize - minSize * 0.5;
            // 在块中心附近产生若干个随机种子
            srand(time(NULL));
            // 初始化漫水填充算法的参数
            Mat mask;
            mask.create(input.rows + 2, input.cols + 2, CV_8UC1);
            mask = Scalar::all(0);
            // loDiff表示当前观察像素值与其部件邻域像素值或者待加入
            // 该部件的种子像素之间的亮度或颜色之负差的最大值
            int loDiff = 30;
            // upDiff表示当前观察像素值与其部件邻域像素值或者待加入
            // 该部件的种子像素之间的亮度或颜色之正差的最大值
            int upDiff = 30;
            int connectivity = 4; // 用于控制算法的连通性，可取4或者8
            int newMaskVal = 255;
            int NumSeeds = 10;
            Rect ccomp;
            // 操作标志符分为几个部分
            int flags = connectivity + // 用于控制算法的连通性，可取4或者8
                        (newMaskVal << 8) +
                        CV_FLOODFILL_FIXED_RANGE + // 设置该标识符，会考虑当前像素与种子像素之间的差
                        CV_FLOODFILL_MASK_ONLY; // 函数不会去填充改变原始图像, 而是去填充掩模图像
            for (int j = 0; j < NumSeeds; j++){
                Point seed;
                seed.x = rects[i].center.x + rand() % (int)minSize - (minSize / 2);
                seed.y = rects[i].center.y + rand() % (int)minSize - (minSize / 2);
                circle(result, seed, 1, Scalar(0, 255, 255), -1);
                // 运用填充算法，参数已设置
                int area = floodFill(input,
                                     mask,
                                     seed,
                                     Scalar(255, 0, 0),
                                     &ccomp,
                                     Scalar(loDiff, loDiff, loDiff),
                                     Scalar(upDiff, upDiff, upDiff),
                                     flags);
            }
            if (showSteps)
                imshow("MASK", mask);

            // 得到裁剪掩码后，检查其有效尺寸
            // 对于每个掩码的白色像素，先得到其位置
            // 再使用minAreaRect函数获取最接近的裁剪区域
            vector<Point> pointsInterest;
            Mat_<uchar>::iterator itMask = mask.begin<uchar>();
            Mat_<uchar>::iterator end = mask.end<uchar>();
            for (; itMask != end; ++itMask)
                if (*itMask == 255)
                    pointsInterest.push_back(itMask.pos());

            RotatedRect minRect = minAreaRect(pointsInterest);

            if (verifySizes(minRect)){
                // 旋转矩形图
                Point2f rect_points[4]; minRect.points(rect_points);
                for (int j = 0; j < 4; j++)
                    line(result, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 0, 255), 1, 8);

                // 得到旋转图像区域的矩阵
                float r = (float)minRect.size.width / (float)minRect.size.height;
                float angle = minRect.angle;
                if (r<1)
                    angle = 90 + angle;
                Mat rotmat = getRotationMatrix2D(minRect.center, angle, 1);

                // 通过仿射变换旋转输入的图像
                Mat img_rotated;
                warpAffine(input, img_rotated, rotmat, input.size(), CV_INTER_CUBIC);

                // 最后裁剪图像
                Size rect_size = minRect.size;
                if (r < 1)
                    swap(rect_size.width, rect_size.height);
                Mat img_crop;
                getRectSubPix(img_rotated, rect_size, minRect.center, img_crop);

                Mat resultResized;
                resultResized.create(33, 144, CV_8UC3);
                cv::resize(img_crop, resultResized, resultResized.size(), 0, 0, INTER_CUBIC);
                // 为了消除光照影响，对裁剪图像使用直方图均衡化处理
                Mat grayResult;
                cvtColor(resultResized, grayResult, CV_BGR2GRAY);
                blur(grayResult, grayResult, Size(3, 3));
                grayResult = histeq(grayResult);
                if (saveRecognition){
                    stringstream ss(stringstream::in | stringstream::out);
                    //ss << "tmp/" << filename << "_" << i << ".jpg";
                    ss << "carplate/"<< filename<< "_" << i << ".jpg";
                    //qDebug()<<QString::fromStdString(filename);
                    imwrite(ss.str(), resultResized);
                    //qDebug()<<QString::fromStdString(ss.str());
                }
                output.push_back(Plate(grayResult, minRect.boundingRect()));
            }
        }
        if (showSteps)
            imshow("Contours", result);

        return output;
}
bool GetCarPlate::verifySizes(RotatedRect ROI)
{
    // 以下设置车牌默认参数，用于识别矩形区域内是否为目标车牌
        float error = 0.4;
        // 西班牙车牌宽高比: 520 / 110 = 4.7272
        float aspect = 4.7272;
        // 设定区域面积的最小/最大尺寸，不在此范围内的不被视为车牌
        int min = 15 * aspect * 15;    // 15个像素
        int max = 125 * aspect * 125;  // 125个像素
        float rmin = aspect - aspect*error;
        float rmax = aspect + aspect*error;

        int area = ROI.size.height * ROI.size.width;
        float r = (float)ROI.size.width / (float)ROI.size.height;
        if (r<1)
            r = (float)ROI.size.height / (float)ROI.size.width;

        // 判断是否符合以上参数
        if ((area < min || area > max) || (r < rmin || r > rmax))
            return false;
        else
            return true;
}
Mat GetCarPlate::histeq(Mat ima)
{
    Mat imt(ima.size(), ima.type());
        // 若输入图像为彩色，需要在HSV空间中做直方图均衡处理
        // 再转换回RGB格式
        if (ima.channels() == 3)
        {
            Mat hsv;
            vector<Mat> hsvSplit;
            cvtColor(ima, hsv, CV_BGR2HSV);
            split(hsv, hsvSplit);
            equalizeHist(hsvSplit[2], hsvSplit[2]);
            merge(hsvSplit, hsv);
            cvtColor(hsv, imt, CV_HSV2BGR);
        }
        // 若输入图像为灰度图，直接做直方图均衡处理
        else if (ima.channels() == 1){
            equalizeHist(ima, imt);
        }
        return imt;

}
