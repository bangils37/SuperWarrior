
#include "DragonObject.h"

DragonObject::DragonObject()
{
    frame_=0;
    x_pos_=0;
    y_pos_=0;
    x_val_=0;
    y_val_=0;
    width_frame_=0;
    height_frame_=0;
    map_x_=0;
    map_y_=0;
    isDeath=true;
    isDying=false;
}

DragonObject::~DragonObject()
{

}

bool DragonObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if(ret==TRUE)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }

    return ret;
}

void DragonObject::set_clip()
{
    if(width_frame_>0 && height_frame_>0)
    {
        for(int i=0;i<8;i++)
        {
            frame_clip_[i].x=width_frame_ * i;
            frame_clip_[i].y=0;
            frame_clip_[i].w=width_frame_;
            frame_clip_[i].h=height_frame_;
        }
    }
}

void DragonObject::Show(SDL_Renderer* des)
{
    if(x_pos_ >= x_target_)
    {
        LoadImg("img/dragon_left_main.png", des);
    }
    else
    {
        LoadImg("img/dragon_right_main.png", des);
    }


    frame_++;

    if(frame_>=8)
        frame_=0;

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip_ = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip_, &renderQuad);
}

void DragonObject::Move()
{
    float d = sqrt((x_pos_-x_target_)*(x_pos_-x_target_) + (y_pos_-y_target_)*(y_pos_-y_target_));
    x_val_ = ((x_target_-x_pos_)*DRAGON_SPEED)/d;
    y_val_ = ((y_target_-y_pos_)*DRAGON_SPEED)/d;

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(isDeath)
    {
        x_pos_ = map_x_ + SCREEN_WIDTH + 10;
        y_pos_ = -100;
    }
}

void DragonObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

void DragonObject::ShowDying(SDL_Renderer* des)
{
    LoadImg("img/dragon_death_main.png", des);

    frame_++;

    if(frame_>=8)
        frame_=0;

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip_ = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip_, &renderQuad);
}

void DragonObject::MoveDying()
{
    y_val_ = DRAGON_FALLING;
    y_pos_ += y_val_;

    if(y_pos_ > SCREEN_HEIGHT)
    {
        isDeath = true;
        isDying = false;
        x_pos_ = map_x_ + SCREEN_WIDTH + 10;
        y_pos_ = -100;
    }
}

