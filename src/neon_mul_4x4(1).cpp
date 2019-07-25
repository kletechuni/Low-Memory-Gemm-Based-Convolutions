// simple 4x4 matrix multiplication using neon operands

#include<iostream>
#include<arm_neon.h>



void mul4x4(const float *matrixA, const float *matrixB, float *matrixR)
{
float32x4_t a0,a1,a2,a3,b, r;
a0=vld1q_f32(matrixA);
a1=vld1q_f32(matrixA +4);
a2=vld1q_f32(matrixA +8);
a3=vld1q_f32(matrixA +12);


b = vld1q_f32(matrixB);
r = vmulq_lane_f32(a0, vget_low_f32(b), 0);
r = vmlaq_lane_f32(r, a1, vget_low_f32(b), 1);
r = vmlaq_lane_f32(r, a2, vget_high_f32(b), 0);
r = vmlaq_lane_f32(r, a3, vget_high_f32(b), 1);
vst1q_f32(matrixR, r);

b = vld1q_f32(matrixB + 4);
r = vmulq_lane_f32(a0, vget_low_f32(b), 0);
r = vmlaq_lane_f32(r, a1, vget_low_f32(b), 1);
r = vmlaq_lane_f32(r, a2, vget_high_f32(b), 0);
r = vmlaq_lane_f32(r, a3, vget_high_f32(b), 1);
vst1q_f32(matrixR + 4, r);

b = vld1q_f32(matrixB + 8); 
r = vmulq_lane_f32(a0, vget_low_f32(b), 0);
r = vmlaq_lane_f32(r, a1, vget_low_f32(b), 1);
r = vmlaq_lane_f32(r, a2, vget_high_f32(b), 0);
r = vmlaq_lane_f32(r, a3, vget_high_f32(b), 1);
vst1q_f32(matrixR + 8, r);

b = vld1q_f32(matrixB + 12);
r = vmulq_lane_f32(a0, vget_low_f32(b), 0);
r = vmlaq_lane_f32(r, a1, vget_low_f32(b), 1);
r = vmlaq_lane_f32(r, a2, vget_high_f32(b), 0);
r = vmlaq_lane_f32(r, a3, vget_high_f32(b), 1);
vst1q_f32(matrixR + 12, r);
}

int main()
{
   unsigned int i;
   float A[ ]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
   float B[ ]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
   float C[16];
   mul4x4(A,B,C);
   std::cout<<"end";
   for(i=0;i<16;i++)
{
   std::cout<<C[i]<<"\t";
}

   return(0);
}
   

