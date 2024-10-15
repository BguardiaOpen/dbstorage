/**
 * @file db_storage.h - Header file for storage layer
 * DbBlock
 * DbFile
 *
 * @author Bruno Guardia - adapted from prior Kevin Lundeen's class
 * @see "Seattle University, CPSC5300, Fall 2024"
 */
#pragma once

#include <exception>
#include <map>
#include <utility>
#include <vector>
#include <fstream>
#include <cstdint>

/*
 * Convenient aliases for types
 */
typedef u_int32_t BlockID;

/**
 * @class DbBlock - abstract base class for blocks in our database files
 * (DbBlock's belong to DbFile's.)
 *
 * Methods for putting/getting records in blocks:
 * Accessors:
 * 	get_data()
 * 	get_block_id()
 */
static const uint BLOCK_SZ = 8192;

class DbBlock {
public:
    /**
     * our blocks are 8kB
     */

    /**
     * ctor/dtor (subclasses should handle the big-5)
     */
    DbBlock(BlockID block);

    ~DbBlock();

    /**
     * Access the whole block's memory
     * @returns  Raw byte stream of this block
     */
    void* get_data();

    /**
     * Get this block's BlockID within its DbFile.
     * @returns this block's id
     */
    BlockID get_block_id();

protected:
    BlockID block_id;
    uint8_t data[BLOCK_SZ];
};

// convenience type alias
typedef std::vector<BlockID> BlockIDs;  // FIXME: will need to turn this into an iterator at some point

/**
 * @class DbFile - abstract base class which represents a disk-based collection of DbBlocks
 * 	create()
 * 	drop()
 * 	open()
 * 	close()
 * 	get_new()
 *	get(block_id)
 *	put(block)
 *	block_ids()
 */
class DbFile {
public:
    // ctor/dtor -- subclasses should handle big-5
    DbFile(std::string name);

    ~DbFile();

    /**
     * Create the file.
     */
    void create();

    /**
     * Remove the file.
     */
    void drop();

    /**
     * Open the file.
     */
    void open();

    /**
     * Close the file.
     */
    void close();

    /**
     * Add a new block for this file.
     * @returns  the newly appended block
     */
    DbBlock* get_new();

    /**
     * Get a specific block in this file.
     * @param block_id  which block to get
     * @returns         pointer to the DbBlock (freed by caller)
     */
    DbBlock* get(BlockID block_id);

    /**
     * Write a block to this file (the block knows its BlockID)
     * @param block  block to write (overwrites existing block on disk)
     */
    void put(DbBlock* block);

    /**
     * Get a list of all the valid BlockID's in the file
     * FIXME - not a good long-term approach, but we'll do this until we put in iterators
     * @returns  a pointer to vector of BlockIDs (freed by caller)
     */
    BlockIDs* block_ids() { return nullptr; };

protected:
    std::string name;  // filename (or part of it)
    std::fstream dbFile;
    u_int32_t fileSize = 0; // limited to 4Gb for now
    void ensureClosed();
};
