/*------------------------------------------------------
Student's Name:
Student's number: 
Student's email address:  
-------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma pack(push, 1)
/**** BMP file header structure ****/
typedef struct                       
{
    unsigned short bfType;           /* BM */
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
}FILEHEADER;
	
/**** BMP file info structure ****/
typedef struct                      
{
    unsigned int   biSize;           /* Size of info header */
    int            width;          /* Width of image */
    int            height;         /* Height of image */
    unsigned short planes;         /* Number of color planes */
    unsigned short bitPix;       	/* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
}INFOHEADER;
	
/**** Colormap pixel structure ****/
typedef struct                       
{
    unsigned char  b;         /* Blue value */
    unsigned char  g;         /* Green value */
    unsigned char  r;         /* Red value */
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
	PIX **rgbImage;           /* 2D array of RGB image pixels */
	
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
	
	
   /* allocate memory for cfaImage */
	cfaImage = alloc2D( info.height, info.width );
	if( cfaImage == NULL )
	{
	   fprintf( stderr, " Memory allocation error" );
	   return -1; 	  
	} 	
    
	fseek(inFile, header.bfOffBits, SEEK_SET);
	for(i=info.height-1; i>=0; i--)  /* from upside-down to raster */
	  if( fread( cfaImage[i], sizeof(unsigned char), info.width, inFile) != info.width)
      {
        fprintf(stderr, "Error reading Image data");
	    fclose( inFile );
        return -1;
      }

   /* allocate memory for an RGB Image */
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
	
	info.bitPix = 24;  /* change to 24 bit/pix */
	if( fwrite(&info, sizeof(INFOHEADER), 1, outFile) != 1)
    {
        fprintf(stderr, "Error writing Info Header");
	    fclose( outFile );
        return -1;
    }
	
	fseek(outFile, header.bfOffBits, SEEK_SET);
	for(i=info.height-1; i>=0; i--) /* from raster to upside-down */
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
   if( pp == NULL )  { free(p); return NULL; } 
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
   if( pp == NULL )  { free(p); return NULL; } 
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


/*============ Your code starts here ============*/
bool processCFAImage( unsigned char **cfaImage, PIX **rgbImage, int width, int height )
{
    int row, col;	 
	
	/* an example that shows how to access pixels and r,g,b components
	   stored in the standard raster scan order  */
	   
	for(row=0; row < height; row++)
	  for( col=0; col <width; col++)
	  {
		 rgbImage[row][col].r = cfaImage[row][col];
		 rgbImage[row][col].g = cfaImage[row][col];
	     rgbImage[row][col].b = cfaImage[row][col];
	  }

    return true;
}
