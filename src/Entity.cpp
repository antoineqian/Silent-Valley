// Helper function to get the bounding box of a sprite
sf::FloatRect entity::getBoundingBox() const noexcept
{
    return sprite.getGlobalBounds();
}

// Helper function to get the centre of a sprite
sf::Vector2f entity::getCentre() const noexcept
{
    auto box = getBoundingBox();
    return {box.width / 2.0f, box.height / 2.0f};
}
