#pragma once

template <T>
class EventObserver
{
    virtual void field_changed(
        T &source,
        const std::string &field_name) = 0;
};