#include "Renderer.h"

void Renderer::ClearBuffers() {
    rlClearScreenBuffers();
}

void Renderer::ClearBackground(Color color) {
    rlClearColor(color.r, color.g, color.b, color.a);
    rlClearScreenBuffers();
}

void Renderer::Draw() {
    rlglDraw();
}

void Renderer::DrawLine(Vector2 startPos, Vector2 endPos, Color color)
{
    rlBegin(RL_LINES);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlVertex2f(startPos.x, startPos.y);
    rlVertex2f(endPos.x, endPos.y);
    rlEnd();
}

// Draw a triangle
void Renderer::DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color)
{
    rlEnableTexture(GetTextureDefault().id); // Default white texture

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlVertex2f(v1.x, v1.y);
    rlVertex2f(v2.x, v2.y);
    rlVertex2f(v2.x, v2.y);
    rlVertex2f(v3.x, v3.y);
    rlEnd();

    rlDisableTexture();
}

// Draw color-filled rectangle
void Renderer::DrawRectangle(int posX, int posY, int width, int height, Color color)
{
#define TRIS_RECTANGLE
#if defined(TRIS_RECTANGLE)
    // NOTE: We use rlgl OpenGL 1.1 style vertex definition
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlVertex2i(posX, posY);
    rlVertex2i(posX, posY + height);
    rlVertex2i(posX + width, posY + height);

    rlVertex2i(posX, posY);
    rlVertex2i(posX + width, posY + height);
    rlVertex2i(posX + width, posY);
    rlEnd();
#else   // QUADS_RECTANGLE
    // NOTE: Alternative implementation using RL_QUADS
    rlEnableTexture(GetDefaultTexture().id);    // Default white texture
    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlNormal3f(0.0f, 0.0f, 1.0f);

    rlTexCoord2f(0.0f, 0.0f);
    rlVertex2f(position.x, position.y);

    rlTexCoord2f(0.0f, 1.0f);
    rlVertex2f(position.x, position.y + size.y);

    rlTexCoord2f(1.0f, 1.0f);
    rlVertex2f(position.x + size.x, position.y + size.y);

    rlTexCoord2f(1.0f, 0.0f);
    rlVertex2f(position.x + size.x, position.y);
    rlEnd();
    rlDisableTexture();
#endif
}

// Draw a color-filled rectangle
void Renderer::DrawRectangleRec(Rectangle rec, Color color)
{
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, color);
}

void Renderer::DrawTexture(Texture2D texture, int posX, int posY, Color tint)
{
    Renderer::DrawTextureEx(texture, Vector2{ (float)posX, (float)posY }, 0, 1.0f, tint);
}

// Draw a Texture2D with extended parameters
void Renderer::DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
{
    Rectangle sourceRec = { 0, 0, texture.width, texture.height };
    Rectangle destRec = { (int)position.x, (int)position.y, texture.width * scale, texture.height * scale };
    Vector2 origin = { 0, 0 };

    Renderer::DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
}

// Draw a part of a texture (defined by a rectangle)
void Renderer::DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint)
{
    Rectangle destRec = { (int)position.x, (int)position.y, abs(sourceRec.width), abs(sourceRec.height) };
    Vector2 origin = { 0, 0 };

    Renderer::DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
}

// Draw a part of a texture (defined by a rectangle) with 'pro' parameters
// NOTE: origin is relative to destination rectangle size
void Renderer::DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint)
{
    // Check if texture is valid
    if (texture.id != 0)
    {
        if (sourceRec.width < 0) sourceRec.x -= sourceRec.width;
        if (sourceRec.height < 0) sourceRec.y -= sourceRec.height;

        rlEnableTexture(texture.id);

        rlPushMatrix();
        rlTranslatef((float)destRec.x, (float)destRec.y, 0);
        rlRotatef(rotation, 0, 0, 1);
        rlTranslatef(-origin.x, -origin.y, 0);

        rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);
        rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer

        // Bottom-left corner for texture and quad
        rlTexCoord2f((float)sourceRec.x / texture.width, (float)sourceRec.y / texture.height);
        rlVertex2f(0.0f, 0.0f);

        // Bottom-right corner for texture and quad
        rlTexCoord2f((float)sourceRec.x / texture.width, (float)(sourceRec.y + sourceRec.height) / texture.height);
        rlVertex2f(0.0f, (float)destRec.height);

        // Top-right corner for texture and quad
        rlTexCoord2f((float)(sourceRec.x + sourceRec.width) / texture.width, (float)(sourceRec.y + sourceRec.height) / texture.height);
        rlVertex2f((float)destRec.width, (float)destRec.height);

        // Top-left corner for texture and quad
        rlTexCoord2f((float)(sourceRec.x + sourceRec.width) / texture.width, (float)sourceRec.y / texture.height);
        rlVertex2f((float)destRec.width, 0.0f);
        rlEnd();
        rlPopMatrix();

        rlDisableTexture();
    }
}

void Renderer::Close() {
    rlglClose();
}