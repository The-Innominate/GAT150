#pragma once

namespace kda {
	template <typename T>
	class Singleton {
		public:
			Singleton(const Singleton& other) {}
			Singleton& operator = (const Singleton& other) {}

			static T& Instance() {
				static T instance;
				return instance;
			}

		protected:
			Singleton() = default;
	};
}