// convolution of 3x3 using neon based instructions.
//ran on mobile device 

#include<iostream>
#include<arm_neon.h>




inline float32x4x3_t load_input( float *in)
{
    const float32x4x3_t vin =
    {
        {
            vld1q_f32(in),
            vld1q_f32(in + 4),
            vld1q_f32(in + 8)
        }
    };
    return vin;
}

void conv3x3(float **in[], float *conv, float *out,unsigned int r)
{

    float32x4x3_t cov1=
{
   { 
       vld1q_dup_f32(conv),
       vld1q_dup_f32(conv+1), 
       vld1q_dup_f32(conv+2)
}};

 

 float32x4x3_t cov2=
{
   {

       vld1q_dup_f32(conv+3),
       vld1q_dup_f32(conv+4),
       vld1q_dup_f32(conv+5)
}};
 float32x4x3_t cov3=
{
   {
       vld1q_dup_f32(conv+6),
       vld1q_dup_f32(conv+7),
       vld1q_dup_f32(conv+8)
}};
  
 
   for(unsigned int i=0;i<3;i=i+3)
{
  
  float32x4_t out1,out2;
 
  const float32x4x3_t ptr0 = load_input(*in[0]);
  const float32x4x3_t ptr1 = load_input(*in[1]);
  const float32x4x3_t ptr2 = load_input(*in[2]);

  out1 = vmulq_f32(ptr0.val[0], cov1.val[0]);
  out1 = vmlaq_f32(out1, ptr1.val[0], cov2.val[0]);
  out1 = vmlaq_f32(out1, ptr2.val[0], cov3.val[0]);

  out2 = vmulq_f32(ptr0.val[1], cov1.val[0]);
  out2 = vmlaq_f32(out2, ptr1.val[1], cov2.val[0]);
  out2 = vmlaq_f32(out2, ptr2.val[1], cov3.val[0]);

  out1 = vmlaq_f32(out1, vextq_f32(ptr0.val[0], ptr0.val[1], 1), cov1.val[1]);
  out1 = vmlaq_f32(out1, vextq_f32(ptr1.val[0], ptr1.val[1], 1), cov2.val[1]);
  out1 = vmlaq_f32(out1, vextq_f32(ptr2.val[0], ptr2.val[1], 1), cov3.val[1]); 

  out2 = vmlaq_f32(out2, vextq_f32(ptr0.val[1], ptr0.val[2], 1), cov1.val[1]);
  out2 = vmlaq_f32(out2, vextq_f32(ptr1.val[1], ptr1.val[2], 1), cov2.val[1]);
  out2 = vmlaq_f32(out2, vextq_f32(ptr2.val[1], ptr2.val[2], 1), cov3.val[1]); 

  out1 = vmlaq_f32(out1, vextq_f32(ptr0.val[0], ptr0.val[1], 2), cov1.val[2]);
  out1 = vmlaq_f32(out1, vextq_f32(ptr1.val[0], ptr1.val[1], 2), cov2.val[2]);
  out1 = vmlaq_f32(out1, vextq_f32(ptr2.val[0], ptr2.val[1], 2), cov3.val[2]); 

  out2 = vmlaq_f32(out2, vextq_f32(ptr0.val[1], ptr0.val[2], 2), cov1.val[2]);
  out2 = vmlaq_f32(out2, vextq_f32(ptr1.val[1], ptr1.val[2], 2), cov2.val[2]);
  out2 = vmlaq_f32(out2, vextq_f32(ptr2.val[1], ptr2.val[2], 2), cov3.val[2]); 
  
  vst1q_f32(out, out1);
  vst1q_f32(out+4, out2);
}
}


int main()
{
  unsigned int w=11,h=3,i,r;
 
  float inp[30]={1,2,3,4,5,6,7,8,9,10,10,9,8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8,9,10};
  float *ptr1,*ptr2,*ptr3;
  ptr1=ptr2=ptr3=inp;
  ptr2 +=10;
  ptr3 +=(2*10);
  float **in[3];
  in[0]=&ptr1;
  in[1]=&ptr2;
  in[2]=&ptr3;
  float out[(w-2)*(h-2)];
  float conv[]={1,2,3,4,5,6,7,8,9};
  r=3;
  conv3x3(in,conv,out,r);

  for(i=0;i<8;i++)
{
  std::cout<<*(out+i)<<"\n";

}
return(0);
}  

