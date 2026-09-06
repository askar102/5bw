// Copyright (C) 2026 No name software.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file is part of the 5BW Project.

#include "bus.h"

template<typename EventType>
void Bus::subscribe(std::function<void(const EventType&)> callback)
{
    subscribers[typeid(EventType)].push_back([callback](std::any msg) {
        callback(std::any_cast<const EventType&>(msg));
    });
}

template<typename EventType>
void Bus::publish(const EventType& msg)
{
    auto it = subscribers.find(typeid(EventType));
    if (it != subscribers.end()) {
        for (const auto& callback : it->second) {
            callback(msg);
        }
    }
}