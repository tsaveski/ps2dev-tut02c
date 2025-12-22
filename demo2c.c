//---------------------------------------------------------------------------
// File:	demo2c.c
// Author:	Tony Saveski, t_saveski@yahoo.com
//---------------------------------------------------------------------------
#include "g2.h"
#include "gs.h"

extern uint32 hover_w;
extern uint32 hover_h;
extern uint32 hover[];
extern uint32 message_w;
extern uint32 message_h;
extern uint32 message[];

static uint16 maxx, maxy;

//---------------------------------------------------------------------------
void flip_buffers(void)
{
	g2_wait_vsync();
	g2_set_visible_frame(1 - g2_get_visible_frame());
	g2_set_active_frame(1 - g2_get_active_frame());
}

//---------------------------------------------------------------------------
void scroll_background(void)
{
int y, i;

	for(y=-hover_h; y<=0; y+=2)
	{
		g2_put_image(0, y, hover_w, hover_h, hover);
		flip_buffers();
	}
	for(i=0; i<0x1FFFFFF; i++) {} // delay
}

//---------------------------------------------------------------------------
void scroll_message(void)
{
uint32 i;
uint16 x, y;

	g2_put_image(0, 0, hover_w, hover_h, hover);
	g2_put_image(10, 10, message_w, message_h, message);
	flip_buffers();
	for(i=0; i<0x4FFFFFF; i++) {} // delay

	// Go Left to Right
	for(x=10; x<maxx-message_w-10; x+=4)
	{
		g2_put_image(0, 0, hover_w, hover_h, hover);
		g2_put_image(x, 10, message_w, message_h, message);
		flip_buffers();
	}


	// Go Top to Bottom
	for(y=10; y<maxy-message_h-10; y+=2)
	{
		g2_put_image(0, 0, hover_w, hover_h, hover);
		g2_put_image(x, y, message_w, message_h, message);
		flip_buffers();
	}


	// Go Right to Left
	for(; x>10; x-=4)
	{
		g2_put_image(0, 0, hover_w, hover_h, hover);
		g2_put_image(x, y, message_w, message_h, message);
		flip_buffers();
	}


	// Go Bottom to Top
	for(; y>10; y-=2)
	{
		g2_put_image(0, 0, hover_w, hover_h, hover);
		g2_put_image(x, y, message_w, message_h, message);
		flip_buffers();
	}

	for(i=0; i<0x4FFFFFF; i++) {} // delay

	g2_put_image(0, 0, hover_w, hover_h, hover);
	flip_buffers();
	g2_put_image(0, 0, hover_w, hover_h, hover);
	flip_buffers();
}

//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
	argc=argc;
	argv=argv;

	if(gs_is_ntsc())
		g2_init(NTSC_512_224_32);
	else
		g2_init(PAL_512_256_32);

	// You'd be STUPID if you put this before the g2_init(), right? :-)
	maxx = g2_get_max_x();
	maxy = g2_get_max_y();

	// clear the screen
	g2_set_fill_color(0, 0, 0);
	g2_fill_rect(0, 0, maxx, maxy);

	// draw next frame to hidden buffer
	g2_set_active_frame(1);
	g2_set_fill_color(0, 0, 0);
	g2_fill_rect(0, 0, maxx, maxy);

	while(1)
	{
		scroll_background();
		scroll_message();
	}

	// ok...it will never get here...
	g2_end();
	return(0);
}
