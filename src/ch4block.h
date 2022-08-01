/*
 * Copyright 2021 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <string>
#include <vector>
#include "iblock.h"
#include "mdf/ichannelhierarchy.h"

namespace mdf::detail {
class Hd4Block;

class Ch4Block : public IBlock, public IChannelHierarchy {
 public:
  using Ch4List = std::vector<std::unique_ptr<Ch4Block>>;
  using RefList = std::vector<int64_t>;

  Ch4Block();
  [[nodiscard]] int64_t Index() const override;

  [[nodiscard]] const std::string& Name() const override;
  void Name(const std::string &name) override;

  void Type(ChType type) override;
  [[nodiscard]] ChType Type() const override;

  [[nodiscard]] std::string Description() const override;
  void Description(const std::string &desc) override;

  IMetaData *MetaData() override;
  [[nodiscard]] const IMetaData *MetaData() const override;

  void AddElementLink(const ElementLink &element) override;
  [[nodiscard]] const std::vector<ElementLink> &ElementLinks() const override;

  [[nodiscard]] const Ch4List& Ch() const {
    return ch_list_;
  }

  [[nodiscard]] const IBlock* Find(fpos_t index) const override;

  void GetBlockProperty(BlockPropertyList& dest) const override;
  size_t Read(std::FILE *file) override;
  size_t Write(std::FILE *file) override;
  void FindReferencedBlocks(const Hd4Block &hd4);

  [[nodiscard]] IChannelHierarchy* CreateChannelHierarchy() override;
  [[nodiscard]] std::vector<IChannelHierarchy*> ChannelHierarchies() const override;
 private:
  uint32_t nof_elements_ = 0;
  uint8_t type_ = 0;
  std::string name_;

  Ch4List ch_list_;


  std::vector<ElementLink> element_list_;
};
}




