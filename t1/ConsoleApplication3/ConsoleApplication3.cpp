//// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}
//
//void CRenderer::PostProcess()
//{
//	float dx = 0.5f / Width;
//	float dy = 0.5f / Height;
//	int loc;
//	//把texColor复制到imgBloom
//	ScaleCopy->ScaleCopyTextureImage(texColor, Width, Height, imgBloom);
//
//	MeasureLuminance(imgBloom); //计算imgBloom的平均亮度
//	lumAdapt += (lum - lumAdapt) * (1 - pow(0.98f, 30 * dTime)); //计算当前适应的亮度
//
//	// render bloom map
//	// progBloom由Bloom.vs和Bloom.fs组成。其代码在后面给出。这个Shader用于提取出
//	UseShaderProgram(progBloom);
//
//	//接下来，把texColor渲染到imgBloom里面，使用progBloom Shader程序提取出亮度较大的部分。
//	loc = gapi->Shader->GetUniformLocationARB(progBloom->ProgramID, "texColor");
//	glBindTexture(GL_TEXTURE_2D, texColor);
//
//	//设置渲染对象。
//	CRenderTarget tgt;
//	tgt.AddColorAttachment(imgBloom);
//	SetRenderTarget(tgt);
//
//	gapi->Shader->Uniform1iARB(loc, 0);
//	loc = gapi->Shader->GetUniformLocationARB(progBloom->ProgramID, "AveLum");
//	gapi->Shader->Uniform1fARB(loc, lumAdapt);
//	loc = gapi->Shader->GetUniformLocationARB(progBloom->ProgramID, "imgH");
//	gapi->Shader->Uniform1iARB(loc, Height);
//	loc = gapi->Shader->GetUniformLocationARB(progBloom->ProgramID, "imgW");
//	gapi->Shader->Uniform1iARB(loc, Width);
//
//
//	glBegin(GL_QUADS);
//	glTexCoord2f(dx, 1 - dy);
//	glVertex2i(0, 0);
//	glTexCoord2f(dx, dy);
//	glVertex2i(0, imgBloom->GetHeight());
//	glTexCoord2f(1 - dx, dy);
//	glVertex2i(imgBloom->GetWidth(), imgBloom->GetHeight());
//	glTexCoord2f(1 - dx, 1 - dy);
//	glVertex2i(imgBloom->GetWidth(), 0);
//	glEnd();
//	UseShaderProgram(0);
//	ResetRenderTarget();
//
//	// 下采样imgBloom到imgLumSample中。imgLumSample的大小为32*32。
//	tgt.ColorAttachCount = 0;
//	tgt.AddColorAttachment(imgLumSample);
//	SetRenderTarget(tgt);
//	UseShaderProgram(progDownSample8);
//	loc = gapi->Shader->GetUniformLocationARB(progDownSample8->ProgramID, "imgH");
//	gapi->Shader->Uniform1iARB(loc, imgBloom->GetHeight());
//	loc = gapi->Shader->GetUniformLocationARB(progDownSample8->ProgramID, "imgW");
//	gapi->Shader->Uniform1iARB(loc, imgBloom->GetWidth());
//	loc = gapi->Shader->GetUniformLocationARB(progDownSample8->ProgramID, "texColor");
//	glBindTexture(GL_TEXTURE_2D, imgBloom->GetID());
//	gapi->Shader->Uniform1iARB(loc, 0);
//	glBegin(GL_QUADS);
//	glTexCoord2f(dx, 1 - dy);
//	glVertex2i(0, 0);
//	glTexCoord2f(dx, dy);
//	glVertex2i(0, imgLumSample->GetHeight());
//	glTexCoord2f(1 - dx, dy);
//	glVertex2i(imgLumSample->GetWidth(), imgLumSample->GetHeight());
//	glTexCoord2f(1 - dx, 1 - dy);
//	glVertex2i(imgLumSample->GetWidth(), 0);
//	glEnd();
//
//	UseShaderProgram(0);
//	ResetRenderTarget();
//
//	// 模糊Bloom贴图。BlurFilter是一个类，在GPU上执行模糊操作。
//	BlurFilter->SetImage(imgLumSample);
//	BlurFilter->Blur();
//	imgLumSample = BlurFilter->GetImage();
//
//	// Tone Mapping
//	UseShaderProgram(progTone);
//	if (!progTone->Validate())
//		throw HException(progTone->Info);
//	gapi->BindTexture2D(texColor, 0);
//	loc = gapi->Shader->GetUniformLocationARB(progTone->ProgramID, "texSrc");
//	gapi->Shader->Uniform1iARB(loc, 0);
//	gapi->BindTexture2D(imgLumSample->GetID(), 1);
//	loc = gapi->Shader->GetUniformLocationARB(progTone->ProgramID, "texBloom");
//	gapi->Shader->Uniform1iARB(loc, 1);
//	loc = gapi->Shader->GetUniformLocationARB(progTone->ProgramID, "AveLum");
//	gapi->Shader->Uniform1fARB(loc, lumAdapt);
//	loc = gapi->Shader->GetUniformLocationARB(progTone->ProgramID, "Key");
//	gapi->Shader->Uniform1fARB(loc, HDRKey);
//
//	glColor4ub(255, 255, 255, 255);
//	gapi->FBO->BindFramebuffer(GL_FRAMEBUFFER_EXT, 0); //设置渲染对象为屏幕
//	glBegin(GL_QUADS);
//	glTexCoord2f(dx, 1 - dy);
//	glVertex2i(0, 0);
//	glTexCoord2f(dx, dy);
//	glVertex2i(0, Height);
//	glTexCoord2f(1 - dx, dy);
//	glVertex2i(Width, Height);
//	glTexCoord2f(1 - dx, 1 - dy);
//	glVertex2i(Width, 0);
//	glEnd();
//	UseShaderProgram(0);
//	gapi->BindTexture2D(0, 1);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//void CRenderer::MeasureLuminance(CGPUImage *img)
//{
//	// 把img渲染到imgLumSample,使用shader计算每个象素的对数值
//	CRenderTarget tgt;
//	tgt.AddColorAttachment(imgLumSample);
//	SetRenderTarget(tgt);
//	UseShaderProgram(progLogSample);
//	if (!progLogSample->Validate())
//		throw HException(progLogSample->Info);
//	gapi->MultiTexture->ActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, img->GetID());
//	int loc = gapi->Shader->GetUniformLocationARB(progLogSample->ProgramID, "texSrc");
//	gapi->Shader->Uniform1iARB(loc, 0);
//	glBegin(GL_QUADS);
//	glTexCoord2i(0, 1);
//	glVertex2i(0, 0);
//	glTexCoord2i(0, 0);
//	glVertex2i(0, SampleSize);
//	glTexCoord2i(1, 0);
//	glVertex2i(SampleSize, SampleSize);
//	glTexCoord2i(1, 1);
//	glVertex2i(SampleSize, 0);
//	glEnd();
//	UseShaderProgram(0);
//	ResetRenderTarget();
//
//	glBindTexture(GL_TEXTURE_2D, imgLumSample->GetID());
//	//回读到CPU计算亮度。
//	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, data);
//	lum = 0;
//
//	for (int i = 0; i < imgLumSample->GetHeight(); i++)
//		for (int j = 0; j < imgLumSample->GetWidth(); j++)
//			lum += data[i*imgLumSample->GetWidth() * 4 + j * 4];
//	lum /= imgLumSample->GetHeight()*imgLumSample->GetWidth();
//	lum = exp(lum);
//}