#pragma once

#include <mutex>

#include "generic_message.h"
#include "generated/image_generated.h"
#include "header.h"
#include "pose.h"

namespace simple_msgs
{
template <typename T>
class Image : public GenericMessage
{
public:
  Image()
    : GenericMessage()
  {
  }

  Image(const std::string& encoding)
    : GenericMessage()
    , encoding_(encoding)
  {
  }

  Image(const uint8_t* data)
    : GenericMessage()
  {
    auto image_data = GetImageFbs(data);

    // Set Header.
    header_ = image_data->header()->data();
    // Set Origin.
    origin_ = image_data->origin()->data();
    // Set Image Resolution.
    resX_ = image_data->resX();
    resY_ = image_data->resY();
    resZ_ = image_data->resZ();
    // Set Image Dimensions.
    width_ = image_data->width();
    height_ = image_data->height();
    depth_ = image_data->depth();
    // Set Encoding.
    encoding_ = image_data->enconding();
    // Set the Image data according to the right date type.
    auto type = image_data->image_type();
    switch (type)
    {
      case simple_msgs::data_uint8_type:
        data_ = static_cast<const T*>(image_data->image())->raw()->data();
        break;
      case simple_msgs::data_int16_type:
        data_ = static_cast<const T*>(image_data->image())->raw()->data();
        break;
      case simple_msgs::data_float_type:
        data_ = static_cast<const T*>(image_data->image())->raw()->data();
        break;
      case simple_msgs::data_double_type:
        data_ = static_cast<const T*>(image_data->image())->raw()->data();
        break;
      default:
        break;
    }
  }

  Image(const Image& other)
    : GenericMessage()
    , header_(other.header_)
    , origin_(other.origin_)
    , encoding_(encoding_)
    , resX_(other.resX_)
    , resY_(other.resY_)
    , resZ_(other.resZ_)
    , width_(other.width_)
    , height_(other.height_)
    , depth_(other.depth_)
    , data_(other.data_)
    , data_size_(other.data_size_)
  {
  }

  Image(Image&& other)
    : GenericMessage()
    , header_(std::move(other.header_))
    , origin_(std::move(other.origin_))
    , encoding_(std::move(encoding_))
    , resX_(std::move(other.resX_))
    , resY_(std::move(other.resY_))
    , resZ_(std::move(other.resZ_))
    , width_(std::move(other.width_))
    , height_(std::move(other.height_))
    , depth_(std::move(other.depth_))
    , data_(std::move(other.data_))
    , data_size_(std::move(other.data_size_))
  {
  }

  Image& operator=(const Image& other)
  {
    if (this != std::addressof(other))
    {
      std::lock_guard<std::mutex> lock(mutex_);
      header_ = other, header_;
      origin_ = other.origin_;
      encoding_ = other.encoding_;
      resX_ = other.resX_;
      resY_ = other.resY_;
      resZ_ = other.resZ_;
      width_ = other.width_;
      height_ = other.height_;
      depth_ = other.depth_;
      data_ = other.data_;
      data_size_ = other.data_size_;
      modified_ = true;
    }
    return *this;
  }
  Image& operator=(Image&& other)
  {
    if (this != std::addressof(other))
    {
      std::lock_guard<std::mutex> lock(mutex_);
      header_ = std::move(other, header_);
      origin_ = std::move(other.origin_);
      encoding_ = std::move(other.encoding_);
      resX_ = std::move(other.resX_);
      resY_ = std::move(other.resY_);
      resZ_ = std::move(other.resZ_);
      width_ = std::move(other.width_);
      height_ = std::move(other.height_);
      depth_ = std::move(other.depth_);
      data_ = std::move(other.data_);
      data_size_ = std::move(other.data_size_);
      modified_ = true;
    }
    return *this;
  }

  Image& operator=(const uint8_t* data)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    auto image_data = GetImageFbs(data);

    // Set Header.
    header_ = image_data->header()->data();
    // Set Origin.
    // origin_ = static_cast<const uint8_t*>(image_data->origin()->data());
    // Set Image Resolution.
    resX_ = image_data->resX();
    resY_ = image_data->resY();
    resZ_ = image_data->resZ();
    // Set Image Dimensions.
    width_ = image_data->width();
    height_ = image_data->height();
    depth_ = image_data->depth();
    // Set Encoding.
    encoding_ = image_data->enconding()->c_str();
    // Set the Image data according to the right date type.
    auto type = image_data->image_type();

    //    switch (type)
    //    {
    //      case simple_msgs::data_uint8_type:
    //        data_ = reinterpret_cast<const T*>(image_data->image())->raw()->data();
    //        break;
    //      case simple_msgs::data_int16_type:
    //        data_ = reinterpret_cast<T*>(image_data->image())->raw()->data();
    //        break;
    //      case simple_msgs::data_float_type:
    //        data_ = reinterpret_cast<T*>(image_data->image())->raw()->data();
    //        break;
    //      case simple_msgs::data_double_type:
    //        data_ = reinterpret_cast<T*>(image_data->image())->raw()->data();
    //        break;
    //      default:
    //        break;
    //    }
    modified_ = true;
    return *this;
  }

  bool operator==(const Image& rhs) const
  {
    return ((header_ == rhs, header_) && (origin_ == rhs.origin_) && (encoding_ == rhs.encoding_) &&
            (resX_ == rhs.resX_) && (resY_ == rhs.resY_) && (resZ_ == rhs.resZ_) && (width_ == rhs.width_) &&
            (height_ == rhs.height_) && (depth_ == rhs.depth_) && (data_ == rhs.data_) &&
            (data_size_ == rhs.data_size_));
  }
  bool operator!=(const Image& rhs) const { return !(*this == rhs); }
  /**
   * @brief getBufferData
   * @return
   */
  uint8_t* getBufferData() const
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (modified_)
    {
      builder_->Clear();
      auto encoding_data = builder_->CreateString(encoding_);
      auto header_data = builder_->CreateVector(header_.getBufferData(), header_.getBufferSize());
      auto origin_data = builder_->CreateVector(origin_.getBufferData(), origin_.getBufferSize());
      auto type = getDataUnionType();
      auto elem = getDataUnionElem();
      ImageFbsBuilder tmp_builder(*builder_);
      // add the information
      tmp_builder.add_enconding(encoding_data);
      tmp_builder.add_header(header_data);
      tmp_builder.add_origin(origin_data);
      tmp_builder.add_image(elem);
      tmp_builder.add_image_type(type);
      tmp_builder.add_resX(resX_);
      tmp_builder.add_resY(resY_);
      tmp_builder.add_resZ(resZ_);
      tmp_builder.add_height(height_);
      tmp_builder.add_width(width_);
      tmp_builder.add_depth(depth_);
      FinishImageFbsBuffer(*builder_, tmp_builder.Finish());
      modified_ = false;
    }
    return Image::builder_->GetBufferPointer();
  }

  std::array<int, 3> getResolution() const { return std::array<int, 3>{resX_, resY_, resZ_}; }
  std::array<double, 3> getImageDimensions() const { return std::array<double, 3>{width_, height_, depth_}; }
  T* getImageData() const { return *data_; }
  int getImageSize() const { return data_size_; }
  Header getHeader() const { return header_; }
  Pose getImageOrigin() const { return origin_; }
  std::string getImageEncoding() const { return encoding_; }
  void setImageEncoding(const std::string& encoding)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    encoding_ = encoding;
    modified_ = true;
  }

  void setImageResolution(int resX, int resY, int resZ)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    resX_ = resX;
    resY_ = resY;
    resZ_ = resZ;
    modified_ = true;
  }

  void setImageDimensions(double width, double height, double depth)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    width_ = width;
    height_ = height;
    depth_ = depth;
    modified_ = true;
  }

  void setHeader(const Header& header)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    header_ = header;
    modified_ = true;
  }

  void setOrigin(const Pose& origin_pose)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    origin_ = origin_pose;
    modified_ = true;
  }

  void setImageData(T* data, int data_size)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    data_ = data;
    data_size_ = data_size;
    modified_ = true;
  }

  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return ImageFbsIdentifier(); }
private:
  simple_msgs::data getDataUnionType() const;
  flatbuffers::Offset<void> getDataUnionElem() const;

  simple_msgs::Header header_;
  simple_msgs::Pose origin_;
  std::string encoding_{""};

  double resX_{0.0}, resY_{0.0}, resZ_{0.0};
  int width_{0}, height_{0}, depth_{0};

  T* data_{nullptr};
  int data_size_{0};
};
}  // Namespace simple_msgs.