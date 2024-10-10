#include <iostream>
#include <fstream>
#include "dbstorage.h"

    void DbFile::ensureClosed(){
        if (dbFile.is_open()){
            dbFile.close();
        }
    }

    // ctor/dtor
    DbFile::DbFile(std::string name) {
        this->name = name;
        dbFile = std::fstream(name, std::ios::out | std::ios::binary);
        fileSize = 0;
    }

    DbFile::~DbFile(){
        ensureClosed();
    }

    /**
     * Create the file.
     */
    void DbFile::create()
    {
    }

    /**
     * Remove the file.
     */
    void DbFile::drop()
    {
        ensureClosed();
        // TODO: Library function to remove from dir
    }

    /**
     * Open the file.
     */
    void DbFile::open()
    {
        if (!dbFile.is_open())
        {
            dbFile.open(name, std::ios::in | std::ios::binary);
            // Get file size
        }
    }

    /**
     * Close the file.
     */
    void DbFile::close()
    {
        ensureClosed();
    }

    /**
     * Add a new block for this file.
     * @returns  the newly appended block
     */
    DbBlock* DbFile::get_new()
    {
        BlockID nBlocks = fileSize / BLOCK_SZ;
        DbBlock* emptyBlock =new DbBlock(nBlocks);
        std::streampos pos(BLOCK_SZ * nBlocks);
        dbFile.seekg(pos);
        dbFile.write(reinterpret_cast<char*>(emptyBlock), sizeof(DbBlock));
        fileSize += BLOCK_SZ;
        return emptyBlock;
    }

    /**
     * Get a specific block in this file.
     * @param block_id  which block to get
     * @returns         pointer to the DbBlock (freed by caller)
     */
    DbBlock* DbFile::get(BlockID block_id)
    {
        DbBlock* readBlock=new DbBlock(block_id);
        std::streampos pos(BLOCK_SZ * block_id);
        dbFile.seekg(pos);
        dbFile.read(reinterpret_cast<char*>(&readBlock), sizeof(DbBlock));
        return readBlock;
    }

    /**
     * Write a block to this file (the block knows its BlockID)
     * @param block  block to write (overwrites existing block on disk)
     */
    void DbFile::put(DbBlock* block)
    {
        std::streampos pos(BLOCK_SZ * block->get_block_id());
        dbFile.seekg(pos);
        dbFile.write(reinterpret_cast<char*>(block->get_data()), sizeof(DbBlock));
    }

    // TODO: Redefine
//    BlockIDs* DbFile::block_ids() { return nullptr; };

