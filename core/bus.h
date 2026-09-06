// Copyright (C) 2026 No name software.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// This file is part of the 5BW Project.

#ifndef BUS_H
#define BUS_H

#include <functional>
#include <map>
#include <vector>
#include <any>
#include <typeindex>

class Bus {
public:
    /**
     * @brief Method for subscribing to events of a specific type.
     * @tparam EventType Specific event type.
     * @param callback A function that is activated upon receiving a message.
     */
    template<typename EventType>
    void subscribe(std::function<void(const EventType&)> callback);

    /**
     * @brief Method for publish events of a specific type with specified parameters.
     * @tparam EventType Specific event type.
     * @param msg Constructor of EventType.
     */
    template<typename EventType>
    void publish(const EventType& msg);

private:
    std::map<std::type_index, std::vector<std::function<void(std::any)>>> subscribers;
};

#endif