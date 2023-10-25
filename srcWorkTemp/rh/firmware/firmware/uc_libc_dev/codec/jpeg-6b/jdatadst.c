//
// jdatadst.c
//
// Copyright (C) 1994-1996, Thomas G. Lane.
// This file is part of the Independent JPEG Group's software.
// For conditions of distribution and use, see the accompanying README file.
//
// This file contains compression data destination routines for the case of
// emitting JPEG data to a file (or any stdio stream).  While these routines
// are sufficient for most applications, some will want to use a different
// destination manager.
// IMPORTANT: we assume that fwrite() will correctly transcribe an array of
// JOCTETs into 8-bit-wide elements on external storage.  If char is wider
// than 8 bits on your machine, you may need to do some tweaking.
 

// this is not a core library module, so it doesn't define JPEG_INTERNALS 
#include "jinclude.h"
#include "jpeglib.h"
#include "jerror.h"

// Expanded data destination object for stdio output 

typedef struct {
	struct jpeg_destination_mgr pub; 	// public fields 

	#ifdef NOT_USE_FILES
		JOCTET * buffer_out;  			// Ponteiro para buffer que vai conter a imagem compactada
  		JDIMENSION buffer_out_index;	// Indece do buffer
  		size_t buffer_out_size;			// Guarda o tamanho da imagem 
  	#else
  		FILE * outfile;					// target stream 
  	#endif
 
  	JOCTET * buffer;					// Ponteiro do buffer de trabalho
} my_destination_mgr;

typedef my_destination_mgr * my_dest_ptr;

#define OUTPUT_BUF_SIZE  4096	// choose an efficiently fwrite'able size 

//
// Initialize destination --- called by jpeg_start_compress
// before any data is actually written.
METHODDEF(void)	init_destination (j_compress_ptr cinfo) {
  	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

  	// Allocate the output buffer --- it will be released when done with image 
  	dest->buffer = (JOCTET *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  OUTPUT_BUF_SIZE * SIZEOF(JOCTET));

  	dest->pub.next_output_byte = dest->buffer;
  	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
  	
	#ifdef NOT_USE_FILES
		dest->buffer_out_index = 0;
		dest->buffer_out_size = 0;
	#endif
}


//
// Empty the output buffer --- called whenever buffer fills up.
//
// In typical applications, this should write the entire output buffer
// (ignoring the current state of next_output_byte & free_in_buffer),
// reset the pointer & count to the start of the buffer, and return TRUE
// indicating that the buffer has been dumped.
//
// In applications that need to be able to suspend compression due to output
// overrun, a FALSE return indicates that the buffer cannot be emptied now.
// In this situation, the compressor will return to its caller (possibly with
// an indication that it has not accepted all the supplied scanlines).  The
// application should resume compression after it has made more room in the
// output buffer.  Note that there are substantial restrictions on the use of
// suspension --- see the documentation.
//
// When suspending, the compressor will back up to a convenient restart point
// (typically the start of the current MCU). next_output_byte & free_in_buffer
// indicate where the restart point will be if the current call returns FALSE.
// Data beyond this point will be regenerated after resumption, so do not
// write it out when emptying the buffer externally.
 

METHODDEF(boolean) empty_output_buffer (j_compress_ptr cinfo) {
  	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;

  	#ifdef NOT_USE_FILES
  		memcpy(dest->buffer_out+dest->buffer_out_index, dest->buffer, OUTPUT_BUF_SIZE); // Gravar para o buffer de saida o conte�do do buffer de trabalho
		dest->buffer_out_index+=OUTPUT_BUF_SIZE;	// Calcula o pr�ximo indece do buffer out
  	#else
  		if (JFWRITE(dest->outfile, dest->buffer, OUTPUT_BUF_SIZE) != (size_t) OUTPUT_BUF_SIZE)
    		ERREXIT(cinfo, JERR_FILE_WRITE);
    #endif

  	dest->pub.next_output_byte = dest->buffer;	// Sinaliza ao codec o inicio do buffer de trabalho.
  	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE; // Sinaliza que o buffer de trabalho est� vazio

  	return TRUE;
}


//
// Terminate destination --- called by jpeg_finish_compress
// after all data has been written.  Usually needs to flush buffer.
//
// NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
// application must deal with any cleanup that should happen even
// for error exit.
 

METHODDEF(void) term_destination (j_compress_ptr cinfo) {
  	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
  	size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

  	#ifdef NOT_USE_FILES
  	  	// CHECA SE AINDA EXISTEM DADOS NO BUFFER DE TRABALHO
  		if (datacount > 0) {
  			memcpy(dest->buffer_out+dest->buffer_out_index, dest->buffer, datacount);
  			dest->buffer_out_index+=datacount;
  		}
  		
  		dest->buffer_out_size = dest->buffer_out_index;
  	#else
  		// Write any data remaining in the buffer 
  		if (datacount > 0) {
    		if (JFWRITE(dest->outfile, dest->buffer, datacount) != datacount)
      			ERREXIT(cinfo, JERR_FILE_WRITE);
  		}
  	
  		fflush(dest->outfile);
  		// Make sure we wrote the output file OK 
  		if (ferror(dest->outfile))
    		ERREXIT(cinfo, JERR_FILE_WRITE);
    #endif
}


//
// Prepare for output to a stdio stream.
// The caller must have already opened the stream, and is responsible
// for closing it after finishing compression.
 

#ifdef NOT_USE_FILES
GLOBAL(void) jpeg_stdio_dest (j_compress_ptr cinfo, JOCTET * buffer_out) {
#else
GLOBAL(void) jpeg_stdio_dest (j_compress_ptr cinfo, FILE * outfile) {
#endif
  	my_dest_ptr dest;

  	// The destination object is made permanent so that multiple JPEG images
  	// can be written to the same file without re-executing jpeg_stdio_dest.
  	// This makes it dangerous to use this manager and a different destination
  	// manager serially with the same JPEG object, because their private object
  	// sizes may be different.  Caveat programmer.
   
  	if (cinfo->dest == NULL) {	// first time for this JPEG object? 
    	cinfo->dest = 	(struct jpeg_destination_mgr *)
      					(*cinfo->mem->alloc_small) 
      					((j_common_ptr) cinfo, JPOOL_PERMANENT, SIZEOF(my_destination_mgr));
  	}

  	dest = (my_dest_ptr) cinfo->dest;					// Especifico onde est� alocado a estrutura de destino
  	dest->pub.init_destination = init_destination;		// Ponteiro da fun��o que inicializa o tratamento de grava��o jpeg
  	dest->pub.empty_output_buffer = empty_output_buffer;// Ponteiro da fun��o que grava o buffer de trabalho para o buffer de saida jpeg
  	dest->pub.term_destination = term_destination;		// Ponteiro da fun��o que  finaliza o tratamento de grava��o jpeg
  	
  	#ifdef NOT_USE_FILES
  		dest->buffer_out = buffer_out;					// Aponta o buffer de saida
  	#else
  		dest->outfile = outfile;
  	#endif
}

#ifdef NOT_USE_FILES
// RETORNA COM O TAMANHO DA IMAGEM NO BUFFER OUT
GLOBAL(size_t) jpeg_stdio_get_size (j_compress_ptr cinfo) {
  	my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
  	return dest->buffer_out_size;	
}
#endif
