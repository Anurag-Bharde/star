#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
    // Load an image
    cv::Mat image = cv::imread("sample_image.jpg");

    if (image.empty())
    {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    // Split the image into its RGB channels
    std::vector<cv::Mat> bgrChannels;
    cv::split(image, bgrChannels);

    // Calculate histograms for each channel
    int histSize = 256; // Number of bins
    float range[] = {0, 256};
    const float *histRange = {range};
    bool accumulate = false;
    cv::Mat bHist, gHist, rHist;
    cv::calcHist(&bgrChannels[0], 1, 0, cv::Mat(), bHist, 1, &histSize, &histRange, accumulate);
    cv::calcHist(&bgrChannels[1], 1, 0, cv::Mat(), gHist, 1, &histSize, &histRange, accumulate);
    cv::calcHist(&bgrChannels[2], 1, 0, cv::Mat(), rHist, 1, &histSize, &histRange, accumulate);

    // Create an image to display the histograms
    int histWidth = 512;
    int histHeight = 400;
    cv::Mat histImage(histHeight, histWidth, CV_8UC3, cv::Scalar(255, 255, 255));

    // Normalize the histograms to fit the image
    cv::normalize(bHist, bHist, 0, histImage.rows, cv::NORM_MINMAX);
    cv::normalize(gHist, gHist, 0, histImage.rows, cv::NORM_MINMAX);
    cv::normalize(rHist, rHist, 0, histImage.rows, cv::NORM_MINMAX);

    int binWidth = cvRound(static_cast<double>(histWidth) / histSize);

    for (int i = 1; i < histSize; i++)
    {
        line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(bHist.at<float>(i - 1))),
             cv::Point(binWidth * (i), histHeight - cvRound(bHist.at<float>(i))),
             cv::Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(gHist.at<float>(i - 1))),
             cv::Point(binWidth * (i), histHeight - cvRound(gHist.at<float>(i))),
             cv::Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(rHist.at<float>(i - 1))),
             cv::Point(binWidth * (i), histHeight - cvRound(rHist.at<float>(i))),
             cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    // Display the image and histograms
    cv::imshow("Image", image);
    cv::imshow("Histogram", histImage);
    cv::waitKey(0);

    return 0;
}
