#pragma once

#include "Types/Pointers.h"

#include "Proc/Interfaces/IEffectOne.h"

#include "Proc/Settings/SettingsFilter.h"

using namespace Proc::Interfaces;

namespace Proc {

class EffectFilter : virtual public IEffectOne
{
public:
	explicit EffectFilter(const SettingsFilter & settings = SettingsFilter());
	~EffectFilter() = default;

	void SetBaseSettings(const BaseSettings & settings) override;
	const BaseSettings & GetBaseSettings() const override;

	void Apply(const cv::Mat & src, cv::Mat & dst) override;

private:
	class Impl
	{
		class Base
		{
		public:
			virtual ~Base() = default;
			virtual void Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings) = 0;
		};

	public:
		class Clarendon : public Base {
			void Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings) override;
		};

		class Kelvin : public Base {
			void Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings) override;
		};

		class XProII : public Base {
			void Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings) override;
		};

		class Cartoon : public Base {
			void Apply(const cv::Mat & src, cv::Mat & dst, const SettingsFilter& settings) override;
		};

	typedef UniquePtr<Base> Ptr;
	};

private:
	Impl::Ptr m_impl;

	SettingsFilter m_settings;
};

}
