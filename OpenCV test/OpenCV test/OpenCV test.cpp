// OpenCV test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Headers.h"
#include "Ship.h"
#include "Asteroid.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Initialize object tracking
	VideoCapture cap(1);
	// Error check
	if(!cap.isOpened())
	{
		cout << "ERROR: Can't open webcam device (1)\n";
		exit(-1);
	}
	// Initialize object tracking window
	string tempName = "Step 1) Tracking - Move the sliders until your object is isolated in white in window Tracking2";
	namedWindow(tempName, CV_WINDOW_AUTOSIZE);
	// Initialize trackbars
	int lowH = 79;
	int highH = 92;
	int lowS = 116;
	int highS = 215;
	int lowV = 109;
	int highV = 255;
	createTrackbar("lowH", tempName, &lowH, 179);
	createTrackbar("highH", tempName, &highH, 179);
	createTrackbar("lowS", tempName, &lowS, 255);
	createTrackbar("highS", tempName, &highS, 255);
	createTrackbar("lowV", tempName, &lowV, 255);
	createTrackbar("highV", tempName, &highV, 255);

	// Initialize window
	RenderWindow window(VideoMode(800, 600, 32), "Step 2) OpenCV test - Press G to play", Style::Close);
	window.setVerticalSyncEnabled(true);
	// Initialize game objects
	Ship ship;
	Asteroid *currAsteroid = new Asteroid();
	bool go = false;

	while(window.isOpen())
	{
		// Update tracking
		Mat imageOriginal;
		bool success = cap.read(imageOriginal);
		// Error check
		if(!success)
		{
			cout << "ERROR: Can't stream images from the webcam\n";
			exit(-1);
		}
		// Convert BGR to HSV
		Mat imageHSV;
		cvtColor(imageOriginal, imageHSV, CV_BGR2HSV);
		// Threshold
		Mat imageThresholded;
		inRange(imageHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imageThresholded);
		// Remove small objects in the foreground/morphological opening
		erode(imageThresholded, imageHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imageThresholded, imageHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		// Remove small holes in the foreground/morphological closing
		dilate(imageThresholded, imageHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imageThresholded, imageHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		// Use the spatial moments to track the objects position
		Moments moment = moments(imageThresholded);
		int area = moment.m00;
		int m10 = moment.m10;
		int m01 = moment.m01;
		// Anything less then 10000 pixels is expected to be noise e.g. relative to this application of tracking a small green object
		if(go && area > 10000)
		{
			int x = m10 / area;
			ship.setPosition(x % 736);
		}

		// Update
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				window.close();
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::G)
			{
				go = true;
			}
		}

		if(go && currAsteroid->update(ship))
		{
			cout << "Game over!\n";
			window.close();
		}
		if(go && currAsteroid->getPosition() > 472)
		{
			delete currAsteroid;
			currAsteroid = 0;
			currAsteroid = new Asteroid();
		}

		// Draw tracking
		imshow("Tracking1", imageOriginal);
		imshow("Tracking2", imageThresholded);
		if(waitKey(30) == 27)
		{
			// SFML is already handling quit/ESC, but waitKey is needed to alow imshow time to render the images
		}

		// Draw
		window.clear();
		ship.draw(window);
		currAsteroid->draw(window);
		window.display();
	}

	// Cleanup
	delete currAsteroid;

	return 0;
}

