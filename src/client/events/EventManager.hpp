/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** EventManager
*/

#pragma once

#include <string>
#include <tuple>
#include <memory>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <algorithm>

class BaseEvent {
};

class Receiver {
};

class ClassTypeId {
	public:
	using TypeId = size_t;

	/*
	 * Templating will create one function per type used in the code
	 */
	template<typename T>
	static TypeId getTypeId() noexcept {
		/*
		 * Each function will increment the static member {_nexTypeId } only once
		 * due to the static declaration inside this function
		 */
		static const TypeId id = _nextTypeId++;
		return id;
	}

	private:
	static TypeId _nextTypeId;
};

/*
 * CallBack Wrapper
 */
class BaseCallbackWrapper {
	public:
	virtual ~BaseCallbackWrapper() noexcept = default;
	virtual void operator()(const BaseEvent *event) const noexcept = 0;
};

template<typename EventType>
class callbackWrapper : public BaseCallbackWrapper {
	public:
	explicit callbackWrapper(
		const std::function<void(const EventType &)> &callBack
	) noexcept : _callback{std::move(callBack)} {
	}

	void operator()(const BaseEvent *event) const noexcept override {
		_callback(*(static_cast<const EventType *>(event)));
	}

	private:
	std::function<void(const EventType &)> _callback;
};

/*
 * EventManager
 */
class EventManager {
	public:
	/*
	 * This function is used to subscribe a receiver to a certain type of event
	 * All those who have subscribed to this event will receive it
	 */
	template<typename EventType, typename Receiver>
	void subscribe(Receiver &receiver) noexcept {
		static_assert(std::is_base_of<BaseEvent, EventType>(),
			"Template parameter is not based of BaseEvent");
		const ClassTypeId::TypeId eventType = ClassTypeId::getTypeId<EventType>();
		const Receiver &baseReceiver = receiver;
		/*
		 * Lambda calls the receiver.receive(<ev>) member function.
		 * The function must be impemented to the current receiver
		 */
		auto receiverCallback = [&receiver](const auto &ev) noexcept {
			receiver.receive(ev);
		};
		auto callbackPtr = std::make_unique<callbackWrapper<EventType>>(
			receiverCallback);
		_receiversList.emplace(eventType,
			ReceiverInfo{&baseReceiver, std::move(callbackPtr)});
	}

	/*
	 * This function is used to unsubscribe a receiver to a certain type of event
	 */
	template<typename EventType, typename Receiver>
	void unsubscribe(Receiver &receiver) noexcept {
		static_assert(std::is_base_of<BaseEvent, EventType>(),
			"Template parameter is not based of BaseEvent");
		auto &&receivers = _receiversList.equal_range(
			ClassTypeId::getTypeId<EventType>());
		for (auto &it = receivers.first; it != receivers.second;) {
			if (it->second.receiver == &receiver)
				it = _receiversList.erase(it);
			else
				it++;
		}
	};

	/*
	 * This function must be called when the receiver is deleted
	 */
	template<typename Receiver>
	void unsubscribeAll(Receiver &receiver) noexcept {
		for (auto it = _receiversList.begin(); it != _receiversList.end();) {
			if (it->second.receiver == &receiver)
				it = _receiversList.erase(it);
			else
				it++;
		}
	};

	/*
	 * This function is used to emit a certain type of event
	 */
	template<typename EventType, typename ... Params>
	void emit(Params &&... params) noexcept {
		static_assert(std::is_base_of<BaseEvent, EventType>(),
			"Template parameter is not based of BaseEvent");
		EventType event{std::forward<Params>(params)...};
		const ClassTypeId::TypeId eventType = ClassTypeId::getTypeId<EventType>();
		/*
		 * std::unordered_multimap::equal_range()
		 * return range of elements matching a specific key
		 */
		auto &&receivers = _receiversList.equal_range(eventType);
		/*
		 * Call each receiver.receive(<ev>) member function via the lambda
		 * See above : BaseCallbackWrapper::operator()(const BaseEvent *event)
		 */
		std::for_each(receivers.first, receivers.second,
			[&event](const auto &receiverInfo) noexcept {
				(*receiverInfo.second.callbackPtr)(&event);
			});
	};
	private:
	/*
	 * It sucks using std::pair
	 */
	struct ReceiverInfo {
		const Receiver *receiver;
		std::unique_ptr<BaseCallbackWrapper> callbackPtr;
	};
	/*
	 * It will have multiple keys
	 */
	std::unordered_multimap<ClassTypeId::TypeId, ReceiverInfo> _receiversList;
};

