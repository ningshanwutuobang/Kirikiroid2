#ifndef __CC_EMOTE_H__
#define __CC_EMOTE_H__

#include "cocos2d.h"
#define M2COCOS2DX
#include <iemote.h>

USING_NS_CC;

class CCEmote : public Node
{
public:
  CCEmote(const emote_uint8_t *data, emote_uint32_t size);
  virtual ~CCEmote(void);

  static CCEmote *create(const std::string& filename);
  static CCEmote *create(const emote_uint8_t *data, emote_uint32_t size);

  virtual void update(float delta) override;
#if (COCOS2D_VERSION >> 8) <= 0x000301
  virtual void draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated) override;
#else
  virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
#endif
  virtual void updateColor() override;

  void progress(float delta);
  IEmotePlayer *player(void) const;

protected:
  void drawEmote(const Mat4& transform);

private:
	IEmotePlayer *mEmotePlayer;
  CustomCommand  mCustomDrawCommand;
  Mat4 mTransform;
  static IEmoteDevice *sEmoteDevice;
};


#endif
