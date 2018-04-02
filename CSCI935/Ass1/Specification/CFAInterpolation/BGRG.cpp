void CFAInterpolation(unsigned char **cfaImage, PIX **rgbImage, int width, int height) {
	int row, col;
	unsigned char **rgbtemp = alloc2D(height + 2, width + 2);

	for (row = 0; row < height + 2; row++) {
		for (col = 0; col < width + 2; col++)
		{
			if (row == 0 && col == 0) rgbtemp[0][0] = cfaImage[1][1];
			else if (row == height + 1 && col == width + 1) rgbtemp[row][col] = cfaImage[height - 2][width - 2];
			else if (row == 0 && col != 0 && col != width + 1) rgbtemp[row][col] = cfaImage[1][col - 1];
			else if (row == height + 1 && col != 0 && col != width + 1) rgbtemp[row][col] = cfaImage[height - 2][width - 2];
			else if (row != 0 && row != height + 1 && col == 0) rgbtemp[row][0] = cfaImage[row - 1][1];
			else if (row != 0 && row != height + 1 && col == width + 1) rgbtemp[row][width + 1] = cfaImage[row - 1][width - 2];
			else if ((row > 0) && (col > 0) && (row < height + 1) && (col < width + 1))rgbtemp[row][col] = cfaImage[row - 1][col - 1];
		}
	}

	for (row = 0; row < height; row++)
		for (col = 0; col < width; col++) {
			int r = row + 1;
			int c = col + 1;
			if (row % 2 == 1) {				//odd row b & g
				if (col % 2 == 1) {				//odd col b
					rgbImage[row][col].r = (rgbtemp[r - 1][c] + rgbtemp[r - 1][c]) / 2;
					rgbImage[row][col].g = rgbtemp[r][c];
					rgbImage[row][col].b = (rgbtemp[r - 1][c - 1] + rgbtemp[r][c - 1] + rgbtemp[r + 1][c - 1] + rgbtemp[r - 1][c + 1] + rgbtemp[r][c + 1] + rgbtemp[r + 1][c + 1]) / 6;
				}
				else {							//even col g 
					rgbImage[row][col].r = (rgbtemp[r - 1][c - 1] + rgbtemp[r + 1][c - 1] + rgbtemp[r - 1][c + 1] + rgbtemp[r + 1][c + 1]) / 4;
					rgbImage[row][col].g = (rgbtemp[r - 1][c] + rgbtemp[r][c] + rgbtemp[r + 1][c]) / 3;
					rgbImage[row][col].b = (rgbtemp[r][c - 1] + rgbtemp[r][c + 1]) / 2;
				}
			}
			else {							//even row g & r
				if (col % 2 == 1) {				//odd col r
					rgbImage[row][col].r = rgbtemp[r][c];
					rgbImage[row][col].g = (rgbtemp[r - 1][c - 1] + rgbtemp[r][c - 1] + rgbtemp[r + 1][c - 1] + rgbtemp[r - 1][c + 1] + rgbtemp[r][c + 1] + rgbtemp[r + 1][c + 1]) / 6;
					rgbImage[row][col].b = (rgbtemp[r - 1][c] + rgbtemp[r + 1][c]) / 2;
				}
				else {							//even col g
					rgbImage[row][col].r = (rgbtemp[r][c - 1] + rgbtemp[r][c + 1]) / 2;
					rgbImage[row][col].g = (rgbtemp[r - 1][c] + rgbtemp[r][c] + rgbtemp[r + 1][c]) / 3;
					rgbImage[row][col].b = (rgbtemp[r - 1][c - 1] + rgbtemp[r + 1][c - 1] + rgbtemp[r - 1][c + 1] + rgbtemp[r + 1][c + 1]) / 4;
				}
			}
		}
	free2D(rgbtemp);
	//row 480
	//col 640
//rgbImage[row][col].r = 
//rgbImage[row][col].g = 
//rgbImage[row][col].b = 
//rgbtemp[r][c]
//(rgbtemp[r][c]+ rgbtemp[r][c])/2
//(rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c])/3
//(rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c])/4
//(rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c]+ rgbtemp[r][c])/6
}
