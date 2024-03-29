#include <stdio.h>
#include <math.h>
//exo ilipoiisei kai ta 7 modes
#define MODE 7
long hex_to_dec(int,int);
void putchar_mode_4_5(long,long,long,long,long,long,long,long,long);
void dec_to_hex(long,int);
void mysound(int, int, double, double, double, double);
int main(void)                                 
{
    if (MODE != 7)
    {
        long byte,pl_bytes=0,pl_data=0,size_of_file_num,format_num,typeofwaveformat_num,
        stereo_num,SampleRate_num,BytesPerSec_num,Block_align_num,BitsPerSample_num,Size_of_data_num,left=0,right=0;                 
        byte = getchar();                                                     //RIFF
        if (MODE >= 2 && MODE <= 6) putchar(byte);
        if (byte != 'R')                                    
        {
            fprintf(stderr,"Error! 'RIFF' not found \n");
            return 1;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 6) putchar(byte);
        if (byte != 'I') 
        {
            fprintf(stderr,"Error! 'RIFF' not found \n");
            return 1;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 6) putchar(byte);
        if (byte != 'F') 
        {
        fprintf(stderr,"Error! 'RIFF' not found \n");
            return 1;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 6) putchar(byte);
        if (byte != 'F') 
        {
            fprintf(stderr,"Error! 'RIFF' not found \n");
            return 1;                       
        }                                                                 //End of RIFF     
        if (MODE != 4 && MODE !=5) size_of_file_num = hex_to_dec(4,1);                //Size of file     
        if (MODE == 4 ||MODE == 5) size_of_file_num = hex_to_dec(4,4);           
        fprintf(stderr,"size of file: %ld\n",size_of_file_num);           //End of size of file
        byte = getchar();                                                 //WAVE
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);                                           
        pl_bytes++;                                      
        if (byte != 'W')                                     
        {
            fprintf(stderr,"Error! 'WAVE' not found \n");
            return 2;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'A') 
        {
            fprintf(stderr,"Error! 'WAVE' not found \n");
            return 2;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'V') 
        {
        fprintf(stderr,"Error! 'WAVE' not found \n");
            return 2;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'E') 
        {
            fprintf(stderr,"Error! 'WAVE' not found \n");
            return 2;                       
        }                                                                 //End of WAVE
        byte = getchar();                                               //fmt
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'f')                                              
        {
            fprintf(stderr,"Error! 'fmt ' not found \n");
            return 3;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'm') 
        {
            fprintf(stderr,"Error! 'fmt ' not found \n");
            return 3;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 't') 
        {
        fprintf(stderr,"Error! 'fmt ' not found \n");
            return 3;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != ' ')
        {
            fprintf(stderr,"Error! 'fmt ' not found \n");
            return 3;                       
        }                                                                 //End of fmt                                                       
        if (MODE !=4 && MODE !=5) format_num = hex_to_dec(4,1);                                       //format
        if (MODE == 4 || MODE == 5) format_num = hex_to_dec(4,4);
        pl_bytes+=4;
        fprintf(stderr,"size of format chunck: %ld\n",format_num);  
        if (format_num != 16)     
        {
            fprintf(stderr,"Error!  size of format chunck should be 16\n");  
            return 4;  
        }                                                                        //End of format                                                     
        if (MODE !=4 && MODE !=5) typeofwaveformat_num = hex_to_dec(2,1);                                   //type of wave_format
        if (MODE == 4 || MODE == 5) typeofwaveformat_num = hex_to_dec(2,4);
        pl_bytes+=2;
        fprintf(stderr,"WAVE type format: %ld\n",typeofwaveformat_num);
        if(typeofwaveformat_num != 1) 
        {
            fprintf(stderr,"Error! WAVE type format should be 1\n");
            return 5; 
        }                                                                          //end of type of wave_format
        if (MODE != 4 && MODE != 5) stereo_num = hex_to_dec(2,1);                                                   //stereo
        if (MODE == 4 || MODE == 5) 
        {
            stereo_num = hex_to_dec(2,4);
        }
        pl_bytes+=2;
        fprintf(stderr,"mono/stereo: %ld\n",stereo_num);                                                           
        if (stereo_num!=1 && stereo_num!=2)  
        {
            fprintf(stderr,"Error! mono/stereo should be 1 or 2\n");
            return 6;
        }                                                                         //end of stereo
        if (MODE == 1 || MODE == 6) SampleRate_num = hex_to_dec(4,1);                                    //SampleRate
        if (MODE == 2) SampleRate_num = hex_to_dec(4,2);                             //Ypodiplasiasmeno Sample_rate
        if (MODE == 3) SampleRate_num = hex_to_dec(4,3);                            //Diplasiasmeno Sample_rate
        if (MODE == 4 || MODE == 5) SampleRate_num = hex_to_dec(4,4);                            
        pl_bytes+=4;
        fprintf(stderr,"sample rate: %ld\n",SampleRate_num);             //end of SampleRate
        if (MODE == 1 || MODE == 6) BytesPerSec_num = hex_to_dec(4,1);                                 //BytesPerSec   
        if (MODE == 2) BytesPerSec_num = hex_to_dec(4,2);                           //Ypodiplasiasmeno Bytes_per_sec    
        if (MODE == 3) BytesPerSec_num = hex_to_dec(4,3);                           //Diplasiasmeno Bytes_per_sec
        if (MODE == 4 || MODE == 5) BytesPerSec_num = hex_to_dec(4,4);   
        pl_bytes+=4;
        fprintf(stderr,"bytes/sec: %ld\n",BytesPerSec_num);             //end of BytesPerSec
        if (MODE != 4 && MODE != 5) Block_align_num = hex_to_dec(2,1);                                 //Block align  
        if (MODE == 4 || MODE == 5) Block_align_num = hex_to_dec(2,4);                                     
        pl_bytes+=2;
        fprintf(stderr,"block alignment: %ld\n",Block_align_num);
        if(BytesPerSec_num != SampleRate_num * Block_align_num)
        {
            fprintf(stderr,"Error! bytes/second should be sample rate x block alignment\n");
            return 7;
        }                                                                   //end of Block align
        if (MODE != 4 && MODE != 5) BitsPerSample_num = hex_to_dec(2,1);                                  //BitsPerSample
        if (MODE == 4 || MODE == 5) BitsPerSample_num = hex_to_dec(2,4);
        pl_bytes+=2;
        fprintf(stderr,"bits/sample: %ld\n",BitsPerSample_num);
        if (BitsPerSample_num != 8 && BitsPerSample_num !=16)
        {
            fprintf(stderr,"Error! bits/sample should be 8 or 16\n");
            return 8;
        }
        if(Block_align_num != BitsPerSample_num / 8 * stereo_num)
        {
            fprintf(stderr,"Error! block alignment should be bits per sample / 8 x mono/stereo\n");
            return 9;
        }
        byte = getchar();                                                     //Data
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'd')                                    
        {
            fprintf(stderr,"Error! 'data' not found \n");
            return 10;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'a') 
        {
            fprintf(stderr,"Error! 'data' not found \n");
            return 10;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 't') 
        {
        fprintf(stderr,"Error! 'data' not found \n");
            return 10;
        }
        byte = getchar();
        if (MODE >= 2 && MODE <= 3 || MODE == 6) putchar(byte);
        pl_bytes++;
        if (byte != 'a') 
        {
            fprintf(stderr,"Error! 'data' not found \n");
            return 10;                       
        }                                                                 //End of Data
        if (MODE != 4 && MODE != 5) Size_of_data_num = hex_to_dec(4,1);                                 //Size of data
        if (MODE == 4 || MODE == 5) Size_of_data_num = hex_to_dec(4,4);
        pl_bytes+=4;
        fprintf(stderr,"size of data chunk: %ld\n",Size_of_data_num);     //End of Size of data   
        if (MODE == 4 || MODE == 5) putchar_mode_4_5(size_of_file_num,format_num,typeofwaveformat_num,stereo_num,
        SampleRate_num,BytesPerSec_num,Block_align_num,BitsPerSample_num,Size_of_data_num);
        byte = getchar();                                                    //insufficient error and bad file size error
        pl_data++;
        while(byte !=EOF)                                      
        {
            if (MODE >= 2 && MODE <= 3) putchar(byte);
            if (MODE == 6) putchar(byte/8);
            if (MODE == 4 && stereo_num == 2 && pl_data <= Size_of_data_num)
            {
                if (left < Block_align_num/2)
                {
                    putchar(byte);
                    left++;
                }
                else if(left < Block_align_num-1) left++;
                else left = 0;
            }
            if (MODE == 5 && stereo_num == 2 && pl_data <= Size_of_data_num)
            {
                if (right < Block_align_num/2) right++;
                else if (right < Block_align_num)
                {
                    putchar(byte);
                    right++;
                }
                else right = 1;
                
            }
            if((MODE == 4 || MODE == 5) && stereo_num == 2 && pl_data > Size_of_data_num) putchar(byte);
            if ((MODE == 4 || MODE == 5) && stereo_num == 1) putchar(byte);
            pl_bytes++;      
            byte = getchar(); 
            pl_data++;
        }
        if(pl_data<Size_of_data_num)
        {
            fprintf(stderr,"Error! insufficient data\n");
            return 11;
        }                                                               //End of insufficient error and bad file size error
        if(size_of_file_num != pl_bytes)
        {
            fprintf(stderr,"Error! bad file size\n");
            return 12;
        }
    }
    else mysound(3,44100,2.0,1500.0,100.0,30000.0);                                                           //mode7
    return 0;
}

long hex_to_dec(int bytes_num, int mode)
{
    long i,byte,int_num=0,temp;
    if (mode == 1)
    {
        if (bytes_num == 2)
            {
                for (i=1;i<=256;i*=256)                   
                {
                    byte = getchar();
                    if(MODE >= 2 && MODE <=4 || MODE == 6) putchar(byte);
                    int_num += i*byte ;
                }
            }
            if(bytes_num == 4)
            {
                for (i=1;i<=16777216;i*=256)  // 16777216=256*256*256   
                {
                    byte = getchar();
                    if(MODE >= 2 && MODE <=4 || MODE == 6) putchar(byte);
                    int_num += i*byte ;
                }               
            }
            return int_num;
    }
    if (mode == 2)
    {
        for (i=1;i<=16777216;i*=256)  // 16777216=256*256*256   
            {
                byte = getchar();
                int_num += i*byte;
            }               
        temp = int_num;                    //to int_num tha epistrafei sto telos opote den to tropopoioume
        temp/=2;                        //ypodiplasasmos toy int_num
        for (i=1;i<=4;i++)
        {
            putchar(temp%256);
            temp /= 256;
        }
        return int_num;
    } 
    if (mode == 3)
    { 
        for (i=1;i<=16777216;i*=256)  // 16777216=256*256*256   
            {
                byte = getchar();
                int_num += i*byte;
            }               
        temp = int_num;                    //to int_num tha epistrafei sto telos opote den to tropopoioume
        temp*=2;                        //diplasiasmos toy int_num
        for (i=1;i<=4;i++)
        {
            putchar(temp%256);
            temp /= 256;
        }
        return int_num;
    }
    if (mode == 4)
    {
        if (bytes_num == 2)
            {
                for (i=1;i<=256;i*=256)                   
                {
                    byte = getchar();
                    int_num += i*byte ;
                }
            }
            if(bytes_num == 4)
            {
                for (i=1;i<=16777216;i*=256)  // 16777216=256*256*256   
                {
                    byte = getchar();
                    int_num += i*byte ;
                }               
            }
            return int_num;
    }
}



void putchar_mode_4_5(long size_of_file_num,long format_num,long typeofwaveformat_num,long stereo_num,
long SampleRate_num,long BytesPerSec_num,long Block_align_num,long BitsPerSample_num,long Size_of_data_num)
{
    if (stereo_num == 1) dec_to_hex(size_of_file_num,4);
    else
    {
        size_of_file_num = (Size_of_data_num/2) + size_of_file_num - Size_of_data_num;
        dec_to_hex(size_of_file_num,4);
    }
    putchar('W');putchar('A');putchar('V');putchar('E');
    putchar('f');putchar('m');putchar('t');putchar(' ');
    dec_to_hex(format_num,4);
    dec_to_hex(typeofwaveformat_num,2);
    dec_to_hex(1,2);                                  //stereo_num panta 1 
    dec_to_hex(SampleRate_num,4);
    if (stereo_num == 1) 
    {
        dec_to_hex(BytesPerSec_num,4);
        dec_to_hex(Block_align_num,2);
        dec_to_hex(BitsPerSample_num,2);
        putchar('d');putchar('a');putchar('t');putchar('a');
        dec_to_hex(Size_of_data_num,4);
    }
    else 
    {
        Block_align_num = BitsPerSample_num/8;    
        dec_to_hex(SampleRate_num*Block_align_num,4);\
        dec_to_hex(Block_align_num,2);
        dec_to_hex(BitsPerSample_num,2);
        putchar('d');putchar('a');putchar('t');putchar('a');
        dec_to_hex(Size_of_data_num/2,4);
    }
        
}

void dec_to_hex(long number,int bytes)
{
    int i;
    for (i=1;i<=bytes;i++)
        {
            putchar(number % 256);
            number /= 256;
        }
}

void mysound(int dur, int sr, double fm, double fc, double mi, double mv)               //MODE 7
{
    long size_of_data,size_of_file,bytes_per_sec,data_byte,number;
    double t;
    putchar('R');putchar('I');putchar('F');putchar('F');         //bytes_per_sec = block_align*saple_rate and block_align = Bits_per_sample/8 * Mono_stereo = 2 always
    bytes_per_sec = 2*sr;                                                                          //because Bits_per_sample = 16 and mono stereo = 1 always
    size_of_data = dur*bytes_per_sec;       
    size_of_file = size_of_data + 36;                                    //36 bytes from RIFF to size_of_data       
    dec_to_hex(size_of_file,4);  
    putchar('W');putchar('A');putchar('V');putchar('E');        //WAVE
    putchar('f');putchar('m');putchar('t');putchar(' ');        //fmt 
    dec_to_hex(16,4);                                          //format = 16 
    dec_to_hex(1,2);                                          //type_of_wave_format = 1
    dec_to_hex(1,2);                                          //mono_stereo = 1 always
    dec_to_hex(sr,4);                                       //sample_rate
    dec_to_hex(bytes_per_sec,4);                                 //bytes_per_sec
    dec_to_hex(2,2);                                               //block_align = 2 always
    dec_to_hex(16,2);                                                  //bits_per_sample = 16 always
    putchar('d');putchar('a');putchar('t');putchar('a');                    //data
    dec_to_hex(size_of_data,4);                                         //size_of_data
    for(data_byte = 1;data_byte <=size_of_data;data_byte++)               //data
    {
        t = (double)(data_byte) / bytes_per_sec;                          
        number = mv * sin(2*M_PI*fc*t - mi *sin(2*M_PI*fm*t));
        putchar(number/256);
    }
}