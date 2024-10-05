#include "cocos2d.h"
#include <CCEmote.h>

USING_NS_CC;

//------------------------------------------------
IEmoteDevice *CCEmote::sEmoteDevice;

//------------------------------------------------
CCEmote *CCEmote::create(const std::string& filename)
{
  auto fileUtils = FileUtils::getInstance();
  std::string path = fileUtils->fullPathForFilename(filename);
  ssize_t size;
  unsigned char *data = fileUtils->getFileData(path, "rb", &size);
  if (!data){
    return nullptr;
  }
  CCEmote *emote = create(data, size);
  delete[] data;
  return emote;
}


CCEmote *CCEmote::create(const emote_uint8_t *data, emote_uint32_t size)
{
  CCEmote * ret = new CCEmote(data, size);
  if (ret){
    ret->autorelease();
    return ret;
  }
  CC_SAFE_DELETE(ret);
  return nullptr;
}

//------------------------------------------------
CCEmote::CCEmote(const emote_uint8_t *data, emote_uint32_t size)
{
  if (!sEmoteDevice){
    IEmoteDevice::InitParam param = { 0 };
    sEmoteDevice = EmoteCreate(param);

    // change mask mode to alpha mask
    sEmoteDevice->SetMaskMode(IEmoteDevice::MASK_MODE_ALPHA);
  }
  sEmoteDevice->CreatePlayer(data, size, &mEmotePlayer);
  mEmotePlayer->Show();

  scheduleUpdate();
}

CCEmote::~CCEmote(void)
{
  mEmotePlayer->Release();
}

void CCEmote::update(float delta)
{
  this->progress(delta);
}


void CCEmote::progress(float delta)
{
  Vec2 pos = this->getPosition();
  mEmotePlayer->SetCoord(pos.x, pos.y);
  mEmotePlayer->SetRot(this->getRotation() * M_PI / 180.0f);

  mEmotePlayer->Progress(delta * 60.0f);
}


IEmotePlayer *CCEmote::player(void) const
{
  return mEmotePlayer;
}


#if (COCOS2D_VERSION >> 8) <= 0x000301
void CCEmote::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated)
#else
void CCEmote::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
#endif
{
  mCustomDrawCommand.init(_globalZOrder);
  mCustomDrawCommand.func = CC_CALLBACK_0(CCEmote::drawEmote, this, transform);
  renderer->addCommand(&mCustomDrawCommand);
}


void CCEmote::updateColor()
{
  auto color = this->getColor();
  int r = color.r * 128 / 255;
  int g = color.g * 128 / 255;
  int b = color.b * 128 / 255;
  mEmotePlayer->SetColor((r << 24) + (g << 16) + (b << 8) + this->getOpacity());
}


void CCEmote::drawEmote(const Mat4& transform)
{
  Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
  Director::getInstance()->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

  GLint viewport[4];
  glGetIntegerv (GL_VIEWPORT, viewport);
  int w = viewport[2];
  int h = viewport[3];
  GLint framebufferId;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebufferId);
  GLint renderbufferId;
  glGetIntegerv(GL_RENDERBUFFER_BINDING, &renderbufferId);
  if (framebufferId == renderbufferId) {
    auto framesize = Director::getInstance()->getOpenGLView()->getFrameSize();
    w = framesize.width;
    h = framesize.height;
  }
  sEmoteDevice->ChangeFrameBufferSize(w, h);

  Mat4 mat;
  Mat4::createTranslation(-viewport[2] / 2.0f, -viewport[3] / 2.0f, 0, &mat);

  Mat4 scale;
  Mat4::createScale(1.0f, -((double)viewport[2]/viewport[3])/((double)w/h), 1.0f, &scale);

  Mat4 rot;
  Mat4::createRotationZ(-mEmotePlayer->GetRot(), &rot);

  auto pos = this->getPosition();
  Mat4 trans;
  Mat4::createTranslation(-pos.x, -pos.y, 0, &trans);

  mTransform = transform * scale * trans * rot;

  mat *= mTransform;
  sEmoteDevice->SetViewMatrix(mat.m);

  Mat4 adhocScale;
  Mat4::createScale(2.0f / w, 2.0f / h, 1, &adhocScale);
  sEmoteDevice->SetProjMatrix(adhocScale.m);

  sEmoteDevice->SetModelMatrix(Mat4::IDENTITY.m);

  mEmotePlayer->Render();

  GL::useProgram(0);
  GL::bindTexture2D((GLuint)0);
  glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

  Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}




