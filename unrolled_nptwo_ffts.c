static av_always_inline void fft7(FFTComplex *out, FFTComplex *in,
                                  ptrdiff_t stride)
{
    FFTComplex t[6], z[3];
    const FFTComplex *tab = TX_NAME(ff_cos_7);

    BF(t[1].re, t[0].re, in[1].re, in[6].re);
    BF(t[1].im, t[0].im, in[1].im, in[6].im);
    BF(t[3].re, t[2].re, in[2].re, in[5].re);
    BF(t[3].im, t[2].im, in[2].im, in[5].im);
    BF(t[5].re, t[4].re, in[3].re, in[4].re);
    BF(t[5].im, t[4].im, in[3].im, in[4].im);

    out[0*stride].re = in[0].re + t[0].re + t[2].re + t[4].re;
    out[0*stride].im = in[0].im + t[0].im + t[2].im + t[4].im;

    z[0].re = tab[0].re*t[0].re - tab[2].re*t[4].re - tab[1].re*t[2].re;
    z[1].re = tab[0].re*t[4].re - tab[1].re*t[0].re + tab[2].re*t[2].re;
    z[2].re = tab[0].re*t[2].re - tab[2].re*t[0].re - tab[1].re*t[4].re;
    z[0].im = tab[0].re*t[0].im - tab[1].re*t[2].im - tab[2].re*t[4].im;
    z[1].im = tab[0].re*t[4].im - tab[1].re*t[0].im - tab[2].re*t[2].im;
    z[2].im = tab[0].re*t[2].im - tab[2].re*t[0].im - tab[1].re*t[4].im;

    t[0].re = tab[2].im*t[1].im + tab[1].im*t[5].im - tab[0].im*t[3].im;
    t[2].re = tab[0].im*t[5].im + tab[2].im*t[3].im - tab[1].im*t[1].im;
    t[4].re = tab[2].im*t[5].im + tab[1].im*t[3].im + tab[0].im*t[1].im;
    t[0].im = tab[0].im*t[1].re + tab[1].im*t[3].re + tab[2].im*t[5].re;
    t[2].im = tab[2].im*t[3].re + tab[0].im*t[5].re - tab[1].im*t[1].re;
    t[4].im = tab[2].im*t[1].re + tab[1].im*t[5].re - tab[0].im*t[3].re;

    BF(t[1].re, z[0].re, z[0].re, t[4].re);
    BF(t[3].re, z[1].re, z[1].re, t[2].re);
    BF(t[5].re, z[2].re, z[2].re, t[0].re);

    BF(t[1].im, z[0].im, z[0].im, t[0].im);
    BF(t[3].im, z[1].im, z[1].im, t[2].im);
    BF(t[5].im, z[2].im, z[2].im, t[4].im);

    out[1*stride].re = in[0].re + z[0].re;
    out[1*stride].im = in[0].im + t[1].im;
    out[2*stride].re = in[0].re + t[3].re;
    out[2*stride].im = in[0].im + z[1].im;
    out[3*stride].re = in[0].re + z[2].re;
    out[3*stride].im = in[0].im + t[5].im;
    out[4*stride].re = in[0].re + t[5].re;
    out[4*stride].im = in[0].im + z[2].im;
    out[5*stride].re = in[0].re + z[1].re;
    out[5*stride].im = in[0].im + t[3].im;
    out[6*stride].re = in[0].re + t[1].re;
    out[6*stride].im = in[0].im + z[0].im;
}
