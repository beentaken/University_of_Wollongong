/*------------------------------------------------------
Student's Name: Yixiang Fan
Student's number: 5083898
Student's email address: yf874@uowmail.edu.au
-------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#pragma pack(push, 1)

/**** BMP file header structure ****/
typedef struct 
{
	unsigned short bfType; /* BM */
	unsigned int bfSize; /* Size of file */
	 unsigned short bfReserved1; /* Reserved */
	 unsigned short bfReserved2; /* ... */
	 unsigned int bfOffBits; /* Offset to bitmap data */
}FILEHEADER;
	
/**** BMP file info structure ****/
typedef struct 
{
	 unsigned int biSize; /* Size of info header */
	 int width; /* Width of image */
	 int height; /* Height of image */
	 unsigned short planes; /* Number of color planes */
	 unsigned short bitPix; 	/* Number of bits per pixel */
	 unsigned int biCompression; /* Type of compression to use */
	 unsigned int biSizeImage; /* Size of image data */
	 int biXPelsPerMeter; /* X pixels per meter */
	 int biYPelsPerMeter; /* Y pixels per meter */
	 unsigned int biClrUsed; /* Number of colors used */
	 unsigned int biClrImportant; /* Number of important colors */
}INFOHEADER;
	
/**** Colormap pixel structure ****/
typedef struct 
{
	 unsigned char b; /* Blue value */
	 unsigned char g; /* Green value */
	 unsigned char r; /* Red value */
}PIX;
	
#pragma pop

/*-- Function prototypes --*/
unsigned char **alloc2D( int height, int width );
PIX **alloc2Drgb( int height, int width );
void free2D( unsigned char **mar );
void free2Drgb( PIX **mar );
bool processCFAImage( unsigned char **cfaImage, PIX **rgbImage, int width, int height );


int main( void )
{
	unsigned char **cfaImage; /* 2D array of CFA image pixels */
	PIX **rgbImage; /* 2D array of RGB image pixels */
	
	char fileName[20];
	FILEHEADER header;
	INFOHEADER info;
	FILE *inFile, *outFile;
	bool errCode;
	int i;
	
	printf("Input CFA file name:");
	scanf("%s", fileName);
	
	/*-- Open the BMP file with CFA samples --*/
	if((inFile = fopen(fileName, "rb")) == NULL)
	{ 
		fprintf(stderr, "Error Opening BMP File");
		return -1;
	}

	/*-- read the file header --*/
	if( fread(&header, sizeof(FILEHEADER), 1, inFile) != 1)
	{
		fprintf(stderr, "Error reading File Header");
		fclose( inFile );
		return -1;
	 }
	
	/*-- Check BM marker --*/
	if (header.bfType != 0x4D42)	 
	{
		fprintf(stderr, "Unsupported file format");
		fclose(inFile);
		return -1;
	}
	/*-- read info --*/
	if( fread(&info, sizeof(INFOHEADER), 1, inFile) != 1)
	{
		fprintf(stderr, "Error reading Info Header");
		fclose( inFile );
		return -1;
	}
	
	
	/* allocate memory for cfaImage, 1 byte per pixel */
	cfaImage = alloc2D( info.height, info.width );
	if( cfaImage == NULL )
	{
		fprintf( stderr, " Memory allocation error" );
		return -1; 	 
	} 	
 
	fseek(inFile, header.bfOffBits, SEEK_SET);
	for(i=0; i<info.height; i++)
	if( fread( cfaImage[i], sizeof(unsigned char), info.width, inFile) != info.width)
	{
		fprintf(stderr, "Error reading Image data");
		fclose( inFile );
		return -1;
	}

	/* allocate memory for an RGB Image, 3 bytes per pixel */
	rgbImage = alloc2Drgb( info.height, info.width );
	if( rgbImage == NULL )
	{
		fprintf( stderr, " Memory allocation error" );
		return -1; 	 
	} 	

	/*----- produce an RGB image from a CFA image ----*/
	errCode = processCFAImage( cfaImage, rgbImage, info.width, info.height );
	if( errCode == false )
	{
		printf("Data processing error \n");
		return -1;	 
	}
		

	/*-------- Save RGB file --------*/
	printf("RGB file name:");
	scanf("%s", fileName);	 
	/*-- Open the BMP file --*/
	if((outFile = fopen(fileName, "wb")) == NULL)	
	{ 
		fprintf(stderr, "Error Opening output BMP File");
		return -1; 
	}
	/*-- write the file header --*/
	if( fwrite(&header, sizeof(FILEHEADER), 1, outFile) != 1)
	{
		fprintf(stderr, "Error writing File Header");
		fclose( outFile );
		return -1;
	}	 
	
	info.bitPix = 24; /* change to 24 bit/pix for true colour images*/
	/*-- write the info header --*/
	if( fwrite(&info, sizeof(INFOHEADER), 1, outFile) != 1)
	{
		fprintf(stderr, "Error writing Info Header");
		fclose( outFile );
		return -1;
	}
	
	/*-- write pixel data --*/
	fseek(outFile, header.bfOffBits, SEEK_SET);
	for(i=0; i<info.height; i++)
	if( fwrite( rgbImage[i], sizeof(PIX), info.width, outFile) != info.width)
	{
		fprintf(stderr, "Error writing RGB Image data");
		fclose( outFile );
		return -1;
	}	 
	 
	free2D( cfaImage );
	free2Drgb( rgbImage );
	fclose(inFile);
	fclose(outFile);
	
	//system("pause");
	return 0;	 
}


unsigned char **alloc2D( int height, int width )
{
	int i;
	unsigned int nelem;
	unsigned char *p, **pp;
	 
	nelem = height * width;
	p = (unsigned char*)calloc( nelem, 1 );
	if( p == NULL ) return NULL;
	pp = (unsigned char**)calloc( height, sizeof(unsigned char*) );
	if( pp == NULL ) { free(p); return NULL; } 
	for ( i=0; i<height; i++ )
		pp[i] = p + i*width;
		 
	return pp;
}

void free2D( unsigned char **mar )
{
	if( mar != NULL ) free( (unsigned char*) *mar );
	free((unsigned char**) mar); 
	return;
}

PIX **alloc2Drgb( int height, int width )
{
	int i;
	unsigned int nelem;
	PIX *p, **pp;
	 
	nelem = height * width;
	p = (PIX*)calloc( nelem, 3 );
	if( p == NULL ) return NULL;
	pp = (PIX**)calloc( height, sizeof(PIX*) );
	if( pp == NULL ) { free(p); return NULL; } 
	for ( i=0; i<height; i++ )
		pp[i] = p + i*width;
		 
	return pp;
}

void free2Drgb( PIX **mar )
{
	if( mar != NULL ) free( (PIX*) *mar );
	free((PIX**) mar);
	 
	return;
}

/*================ Your code starts here ========================*/
unsigned char GammaMatrix[] = {
	15,22,27,31,35,38,41,44,47,50,52,54,57,59,61,63,
	65,67,69,71,72,74,76,77,79,81,82,84,85,87,88,90,
	91,92,94,95,96,98,99,100,101,103,104,105,106,108,109,110,
	111,112,113,114,115,117,118,119,120,121,122,123,124,125,126,127,
	128,129,130,131,132,133,134,135,136,137,138,138,139,140,141,142,
	143,144,145,146,147,147,148,149,150,151,152,152,153,154,155,156,
	157,157,158,159,160,161,161,162,163,164,165,165,166,167,168,168,
	169,170,171,171,172,173,174,174,175,176,176,177,178,179,179,180,
	181,181,182,183,184,184,185,186,186,187,188,188,189,190,190,191,
	192,192,193,194,194,195,196,196,197,198,198,199,199,200,201,201,
	202,203,203,204,205,205,206,206,207,208,208,209,209,210,211,211,
	212,212,213,214,214,215,215,216,217,217,218,218,219,220,220,221,
	221,222,222,223,224,224,225,225,226,226,227,228,228,229,229,230,
	230,231,231,232,233,233,234,234,235,235,236,236,237,237,238,238,
	239,240,240,241,241,242,242,243,243,244,244,245,245,246,246,247,
	247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255,
};


void CFAInterpolation(unsigned char **cfaImage, PIX **rgbImage, int width, int height) {
	int row, col;
	unsigned char **rgbtemp = alloc2D(height + 2, width + 2);

	for (row = 0; row < height + 2; row++) {
		for (col = 0; col < width + 2; col++)
		{
			if (row == 0 && col == 0) rgbtemp[0][0] = cfaImage[1][1];																	//top left
			else if (row == 0 && col == width + 1) rgbtemp[row][col] = cfaImage[1][width - 2];											//top right
			else if (row == height + 1 && col == 0) rgbtemp[row][col] = cfaImage[height - 2][1];										//bottom left
			else if (row == height + 1 && col == width + 1) rgbtemp[row][col] = cfaImage[height - 2][width - 2];						//bottom right
			else if (row == 0 && col != 0 && col != width + 1) rgbtemp[row][col] = cfaImage[1][col - 1];								//top mid
			else if (row == height + 1 && col != 0 && col != width + 1) rgbtemp[row][col] = cfaImage[height - 2][col - 1];				//bottom mid
			else if (row != 0 && row != height + 1 && col == 0) rgbtemp[row][col] = cfaImage[row - 1][1];								//left mid
			else if (row != 0 && row != height + 1 && col == width + 1) rgbtemp[row][col] = cfaImage[row - 1][width - 2];				//right mid
			else if ((row > 0) && (col > 0) && (row < height + 1) && (col < width + 1)) rgbtemp[row][col] = cfaImage[row - 1][col - 1];	//other
		}
	}

	for (row = 0; row < height; row++)
		for (col = 0; col < width; col++) {
			int r = row + 1;
			int c = col + 1;
			if (row % 2 == 1) {				//odd row r g
				if (col % 2 == 1) {				//odd col r
					rgbImage[row][col].r = rgbtemp[r][c];
					rgbImage[row][col].g = (rgbtemp[r][c - 1] + rgbtemp[r][c + 1] + rgbtemp[r - 1][c] + rgbtemp[r + 1][c]) / 4;
					rgbImage[row][col].b = (rgbtemp[r - 1][c - 1] + rgbtemp[r - 1][c + 1] + rgbtemp[r + 1][c - 1] + rgbtemp[r + 1][c + 1]) / 4;
				}
				else {							//even col g 
					rgbImage[row][col].r = (rgbtemp[r][c - 1] + rgbtemp[r][c + 1]) / 2;
					rgbImage[row][col].g = rgbtemp[r][c];
					rgbImage[row][col].b = (rgbtemp[r - 1][c] + rgbtemp[r + 1][c]) / 2;
				}
			}
			else {							//even row b g
				if (col % 2 == 1) {				//odd col b
					rgbImage[row][col].r = (rgbtemp[r - 1][c] + rgbtemp[r + 1][c]) / 2;
					rgbImage[row][col].g = rgbtemp[r][c];
					rgbImage[row][col].b = (rgbtemp[r][c - 1] + rgbtemp[r][c + 1]) / 2;
				}
				else {							//even col g
					rgbImage[row][col].r = (rgbtemp[r - 1][c - 1] + rgbtemp[r - 1][c + 1] + rgbtemp[r + 1][c - 1] + rgbtemp[r + 1][c + 1]) / 4;
					rgbImage[row][col].g = (rgbtemp[r][c - 1] + rgbtemp[r][c + 1] + rgbtemp[r - 1][c] + rgbtemp[r + 1][c]) / 4;
					rgbImage[row][col].b = rgbtemp[r][c];
				}
			}
		}
	free2D(rgbtemp);
}

void ColourCorrection(PIX **rgbImage, int width, int height) {
	int row, col;
	int temp = 0;
	for (row = 0; row < height; row++)
		for (col = 0; col < width; col++) {
			temp = (int)(rgbImage[row][col].r * 1.18 - rgbImage[row][col].g * 0.09 - rgbImage[row][col].b * 0.13);
			if (temp > 255) rgbImage[row][col].r = 255;
			else if (temp < 0) rgbImage[row][col].r = 0;
			else rgbImage[row][col].r = temp;
			temp = (int)(-rgbImage[row][col].r * 0.24 + rgbImage[row][col].g * 1.29 - rgbImage[row][col].b * 0.05);
			if (temp > 255) rgbImage[row][col].g = 255;
			else if (temp < 0) rgbImage[row][col].g = 0;
			else rgbImage[row][col].g = temp;
			temp = (int)(-rgbImage[row][col].r * 0.18 - rgbImage[row][col].g * 0.44 + rgbImage[row][col].b * 1.71);
			if (temp > 255) rgbImage[row][col].b = 255;
			else if (temp < 0) rgbImage[row][col].b = 0;
			else rgbImage[row][col].b = temp;
		}
}

void GammaCorrection(PIX **rgbImage, int width, int height) {
	int row, col;
	for (row = 0; row < height; row++)
		for (col = 0; col < width; col++) {
			rgbImage[row][col].r = GammaMatrix[rgbImage[row][col].r];
			rgbImage[row][col].g = GammaMatrix[rgbImage[row][col].g];
			rgbImage[row][col].b = GammaMatrix[rgbImage[row][col].b];
		}
}

bool processCFAImage( unsigned char **cfaImage, PIX **rgbImage, int width, int height )
{
	/* an example that shows how to access pixels and r,g,b components */
	CFAInterpolation(cfaImage, rgbImage, width, height);
	ColourCorrection(rgbImage, width, height);
	GammaCorrection(rgbImage, width, height);

	return true;
}

