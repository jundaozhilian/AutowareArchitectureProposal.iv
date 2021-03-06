/*
 * Copyright 2020 TierIV. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "TrtNet.h"
#include "cluster2d.h"
#include "feature_generator.h"
#include "lidar_apollo_instance_segmentation/node.h"

#include <tf2_ros/transform_listener.h>
#include <tf2_eigen/tf2_eigen.h>
#include <pcl_ros/transforms.h>
#include <memory>

class LidarApolloInstanceSegmentation : public LidarInstanceSegmentationInterface
{
public:
  LidarApolloInstanceSegmentation();
  ~LidarApolloInstanceSegmentation(){};
  bool detectDynamicObjects(
    const sensor_msgs::PointCloud2 & input,
    autoware_perception_msgs::DynamicObjectWithFeatureArray & output) override;

private:
  bool transformCloud(
    const sensor_msgs::PointCloud2 & input,
    sensor_msgs::PointCloud2& transformed_cloud,
    float z_offset);

  ros::NodeHandle nh_;
  ros::NodeHandle pnh_;

  std::unique_ptr<Tn::trtNet> net_ptr_;
  std::shared_ptr<Cluster2D> cluster2d_;
  std::shared_ptr<FeatureGenerator> feature_generator_;
  float score_threshold_;

  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
  std::string target_frame_;
  float z_offset_;
};
