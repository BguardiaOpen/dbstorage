#include <iostream>
#include <fstream>
#include "dbstorage.h"

    // TODO: Equality operators for comparing blocks
    // ctor/dtor
    DbBlock::DbBlock(BlockID block) : block_id(block) {}

    BlockID DbBlock::get_block_id(){
        return this->block_id;
    }

    void* DbBlock::get_data() {
        return &data;
    }

