/*
 * Copyright (C) 2018 GreenWaves Technologies
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

#ifndef __PMSIS_DRIVERS_I2S_H__
#define __PMSIS_DRIVERS_I2S_H__

#include <stdint.h>


/**
 * @ingroup groupDrivers
 *
 * @defgroup I2S I2S Interface
 *
 * \brief I2S (Inter-IC Sound) Interface
 *
 * The I2S API provides support for the I2S interface.
 *
 * @addtogroup I2S
 * @{
 */

/*
 * The following #defines are used to configure the I2S controller.
 */

typedef uint8_t pi_i2s_fmt_t;

/** Data Format bit field position. */
#define PI_I2S_FMT_DATA_FORMAT_SHIFT       0
/** Data Format bit field mask. */
#define PI_I2S_FMT_DATA_FORMAT_MASK        (0x7 << PI_I2S_FMT_DATA_FORMAT_SHIFT)

/**
 * \brief Standard I2S Data Format.
 *
 * Serial data is transmitted in two's complement with the MSB first. Both
 * Word Select (WS) and Serial Data (SD) signals are sampled on the rising edge
 * of the clock signal (SCK). The MSB is always sent one clock period after the
 * WS changes. Left channel data are sent first indicated by WS = 0, followed
 * by right channel data indicated by WS = 1.
 *
 *        -. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-.
 *     SCK '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '
 *        -.                               .-------------------------------.
 *     WS  '-------------------------------'                               '----
 *        -.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.
 *     SD  |   |MSB|   |...|   |LSB| x |...| x |MSB|   |...|   |LSB| x |...| x |
 *        -'---'---'---'---'---'---'---'---'---'---'---'---'---'---'---'---'---'
 *             | Left channel                  | Right channel                 |
 */
#define PI_I2S_FMT_DATA_FORMAT_I2S          (0 << PI_I2S_FMT_DATA_FORMAT_SHIFT)

/**
 * \brief Pulse-Density Modulation Format.
 *
 * Serial data is transmitted using the pulse-density modulation. Each sample
 * is a one bit pulse, where the density of the pulses gives the amplitude of
 * the signal. The driver will filter the input signals so that classic PCM
 * samples are stored in the buffers. In single channel mode, the bits are
 * transmitted on clock signal (CLK) rising edges. In dual channel mode, left
 * chanel is transmitted on SCK rising edges and right channel on SCK falling
 * edges. Word Select (WS) is ignored.
 */
#define PI_I2S_FMT_DATA_FORMAT_PDM           (1 << PI_I2S_FMT_DATA_FORMAT_SHIFT)


typedef uint8_t pi_i2s_opt_t;

/** @brief Mem slab mode
 *
 * In mem slab mode TX output or RX sampling will keep alternating between a 
 * a set of buffers given by the user.
 * Memory slab pointed to by the mem_slab field has to be defined and
 * initialized by the user. For I2S driver to function correctly number of
 * memory blocks in a slab has to be at least 2 per queue. Size of the memory
 * block should be multiple of frame_size where frame_size = (channels *
 * word_size_bytes). As an example 16 bit word will occupy 2 bytes, 24 or 32
 * bit word will occupy 4 bytes.
 */

#define PI_I2S_OPT_MEM_SLAB                (1 << 0)

/** @brief Ping pong mode
 *
 * In ping pong mode TX output or RX sampling will keep alternating between a
 * ping buffer and a pong buffer.
 * This is normally used in audio streams when one buffer
 * is being populated while the other is being played (DMAed) and vice versa.
 * So, in this mode, 2 sets of buffers fixed in size are used. These 2 buffers
 * must be given in the configuration when the driver is opened and kept alive
 * until the driver is closed.
 */
#define PI_I2S_OPT_PINGPONG                (0 << 0)

/** @brief TDM mode
 *
 * In TDM mode, the same interface is time-multiplexed to transmit data
 * for multiple channels where each channel can have a specific
 * configuration.
 */
#define PI_I2S_OPT_TDM                     (1 << 1)

typedef uint8_t pi_i2s_ch_fmt_t;

/** Data order bit field position. */
#define PI_I2S_CH_FMT_DATA_ORDER_SHIFT       0
/** Data order bit field mask. */
#define PI_I2S_CH_FMT_DATA_ORDER_MASK        (1 << 0)

/** Data align bit field position. */
#define PI_I2S_CH_FMT_DATA_ALIGN_SHIFT       1
/** Data align bit field mask. */
#define PI_I2S_CH_FMT_DATA_ALIGN_MASK        (1 << 1)

/** Data align bit field position. */
#define PI_I2S_CH_FMT_DATA_SIGN_SHIFT       2
/** Data align bit field mask. */
#define PI_I2S_CH_FMT_DATA_SIGN_MASK        (1 << 2)

/** Send MSB first */
#define PI_I2S_CH_FMT_DATA_ORDER_MSB              (0 << 0)
/** Send LSB first */
#define PI_I2S_CH_FMT_DATA_ORDER_LSB              (1 << 0)
/** Left Justified Data Format. */
#define PI_I2S_CH_FMT_DATA_ALIGN_LEFT             (0 << 1)
/** Right Justified Data Format. */
#define PI_I2S_CH_FMT_DATA_ALIGN_RIGHT            (1 << 1)
/** No sign extension. */
#define PI_I2S_CH_FMT_DATA_SIGN_NO_EXTEND         (0 << 2)
/** Sign extension. */
#define PI_I2S_CH_FMT_DATA_SIGN_EXTEND            (1 << 2)

typedef uint8_t pi_i2s_ch_opt_t;

/** @brief Mem slab mode
 *
 * In mem slab mode TX output or RX sampling will keep alternating between a 
 * a set of buffers given by the user.
 * Memory slab pointed to by the mem_slab field has to be defined and
 * initialized by the user. For I2S driver to function correctly number of
 * memory blocks in a slab has to be at least 2 per queue. Size of the memory
 * block should be multiple of frame_size where frame_size = (channels *
 * word_size_bytes). As an example 16 bit word will occupy 2 bytes, 24 or 32
 * bit word will occupy 4 bytes.
 */

#define PI_I2S_CH_OPT_MEM_SLAB                (1 << 0)

/** @brief Ping pong mode
 *
 * In ping pong mode TX output or RX sampling will keep alternating between a
 * ping buffer and a pong buffer.
 * This is normally used in audio streams when one buffer
 * is being populated while the other is being played (DMAed) and vice versa.
 * So, in this mode, 2 sets of buffers fixed in size are used. These 2 buffers
 * must be given in the configuration when the driver is opened and kept alive
 * until the driver is closed.
 */
#define PI_I2S_CH_OPT_PINGPONG                (0 << 0)

/** IOCTL command */
enum pi_i2s_ioctl_cmd
{
    /** @brief Start the transmission / reception of data.
     *
     * This command can be used when the interface has been opened or stopped
     * to start sampling.
     */
    PI_I2S_IOCTL_START,

    /** @brief Stop the transmission / reception of data.
     *
     * Stop the transmission / reception of data at the end of the current
     * memory block. This command can be used when the interface is sampling and
     * is stopping the interface. When the current TX /
     * RX block is transmitted / received the interface is stopped.
     * Subsequent START command will resume transmission / reception where
     * it stopped.
     */
    PI_I2S_IOCTL_STOP,

    /** @brief Configure a channel in TDM mode.
     *
     * In TDM mode, the same interface is time-multiplexed to transmit data
     * for multiple channels, and each channel can have a specific
     * configuration. This command can be used to give the configuration
     * of one channel. The argument must be a pointer to a structure of type
     * struct pi_i2s_ch_conf containing the channel configuration.
     */
    PI_I2S_IOCTL_CH_CONF_SET,

    /** @brief Get the current configuration of a channel in TDM mode.
     *
     * In TDM mode, the same interface is time-multiplexed to transmit data
     * for multiple channels, and each channel can have a specific
     * configuration. This command can be used to get the current configuration
     * of one channel. The argument must be a pointer to a structure of type
     * struct pi_i2s_ch_conf where the current channel configuration will be
     * stored.
     */
    PI_I2S_IOCTL_CH_CONF_GET,
};

/**
 * \struct pi_i2s_conf
 *
 * \brief Interface configuration options.
 */
struct pi_i2s_conf
{
    uint8_t word_size;          /*!< Number of bits representing one data word. */
    uint8_t channels;           /*!< Number of words per frame. */
    uint8_t itf;                /*!< I2S device ID. */
    pi_i2s_fmt_t format;        /*!< Data stream format as defined by PI_I2S_FMT_* constants. */
    pi_i2s_opt_t options;       /*!< Configuration options as defined by PI_I2S_OPT_* constants. */
    uint32_t frame_clk_freq;    /*!< Frame clock (WS) frequency, this is sampling rate. */
    size_t block_size;          /*!< Size of one RX/TX memory block (buffer) in bytes. On some chips, this size may have to be set under a maximum size, check the chip-specific section. */
    pi_mem_slab_t *mem_slab;    /*!< memory slab to store RX/TX data. */
    void *pingpong_buffers[2];  /*!< Pair of buffers used in double-buffering mode to
                                  capture the incoming samples.  */
    uint16_t pdm_decimation;    /*!< In PDM mode, this gives the decimation factor to be used,
                                  e.g. the number of bits on which the filter is applied.
                                  This factor is usually in the range between 48 and 128.

                                  PDM_freq = sampling_rate * pdm_decimation.
                                  - PDM_freq is the clock frequency of the microphone.
                                  - sampling_rate is the audio sampling rate(22050kHz, 44100kHZ, 48000kHZ,...).
                                  - pdm_decimation is the decimation factor to apply. */
    int8_t pdm_shift;           /*!< In PDM mode, the shift value to shift data when applying filter. */
    uint8_t pdm_filter_ena;     /*!< When using PDM mode, enable PDM filter. */
};

/**
 * \struct pi_i2s_ch_conf
 *
 * \brief Channel configuration options.
 */
struct pi_i2s_ch_conf
{
    uint8_t id;                 /*!< Channel ID, from 0 to the number of channels minus 1. */
    uint8_t word_size;          /*!< Number of bits representing one data word. */
    pi_i2s_ch_fmt_t format;     /*!< Data stream format as defined by PI_I2S_CH_FMT_* constants. */
    pi_i2s_ch_opt_t options;    /*!< Channel configuration options as defined by PI_I2S_CH_OPT_* constants. */
    size_t block_size;          /*!< Size of one RX/TX memory block (buffer) in bytes. On some chips, this size may have to be set under a maximum size, check the chip-specific section. */
    pi_mem_slab_t *mem_slab;    /*!< memory slab to store RX/TX data. */
    void *pingpong_buffers[2];  /*!< Pair of buffers used in double-buffering mode to
                                  capture the incoming samples.  */
    uint8_t enabled;            /*!< 1 if channel is enabled. */
};

/** \brief Setup specific I2S aspects.
 *
 * This function can be called to set specific I2S properties such as the
 * number of clock generator. This is typically used by the BSP to give
 * board specific information.
 *
 * \param flags  A bitfield of chip-dependant properties.
 */
void pi_i2s_setup(uint32_t flags);

/** \brief Initialize an I2S configuration with default values.
 *
 * This function can be called to get default values for all parameters before
 * setting some of them.
 * The structure containing the configuration must be kept alive until the I2S
 * device is opened.
 *
 * \param conf A pointer to the I2S configuration.
 */
void pi_i2s_conf_init(struct pi_i2s_conf *conf);

/** \brief Open an I2S device.
 *
 * This function must be called before the I2S device can be used.
 * It will do all the needed configuration to make it usable and initialize
 * the handle used to refer to this opened device when calling other functions.
 * The caller is blocked until the operation is finished.
 *
 * \param device    A pointer to the device structure of the device to open.
 *   This structure is allocated by the caller and must be kept alive until the
 *   device is closed.
 * \return          0 if the operation is successfull, -1 if there was an error.
 */
int pi_i2s_open(struct pi_device *device);

/** \brief Close an opened I2S device.
 *
 * This function can be called to close an opened I2S device once it is not
 * needed anymore, in order to free all allocated resources. Once this function
 * is called, the device is not accessible anymore and must be opened
 * again before being used.
 * The caller is blocked until the operation is finished.
 *
 * \param device  A pointer to the structure describing the device.
 */
void pi_i2s_close(struct pi_device *device);

/** \brief Dynamically change the device configuration.
 *
 * This function can be called to change part of the device configuration after
 * it has been opened or to control it.
 *
 * \param device  A pointer to the structure describing the device.
 * \param cmd      The command which specifies which parameters of the driver
 *   to modify and for some of them also their values. The command must be one
 *   of those defined in pi_spi_ioctl_e.
 * \param arg       An additional value which is required for some parameters
 *   when they are set.
 */
int pi_i2s_ioctl(struct pi_device *device, uint32_t cmd, void *arg);

/**
 * @brief Read data from the RX queue.
 *
 * Data received by the I2S interface is stored in the RX queue consisting
 * of two memory blocks preallocated by the user and given to the driver in
 * the configuration. Calling this function will return the next available
 * buffer to the caller, which has to use it before the sampling for this buffer
 * starts again.
 *
 * The data is read in chunks equal to the size of the memory block.
 *
 * When using several channels, the organization of the samples for each channel
 * in the buffer, is chip-dependent, check the chip-specific documentation
 * to get more information.
 *
 * If there is no data in the RX queue the function will block waiting for
 * the next RX memory block to fill in.
 *
 * Due to hardware constraints, the address of the buffer must be aligned on
 * 4 bytes.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param mem_block Pointer to the variable storing the address of the RX memory
 *   block containing received data.
 * @param size Pointer to the variable storing the number of bytes read.
 *
 * @retval 0 If successful, -1 if not.
 */
int pi_i2s_read(struct pi_device *dev, void **mem_block, size_t *size);

/**
 * @brief Read data asynchronously from the RX queue.
 *
 * Data received by the I2S interface is stored in the RX queue consisting
 * of two memory blocks preallocated by the user and given to the driver in
 * the configuration. Calling this function will return the next available
 * buffer to the caller, which has to use it before the sampling for this buffer
 * starts again.
 *
 * The data is read in chunks equal to the size of the memory block.
 *
 * When using several channels, the organization of the samples for each channel
 * in the buffer, is chip-dependent, check the chip-specific documentation
 * to get more information.
 *
 * The specified task will be pushed as soon as data is ready in the RX queue,
 * and the information about the memory block and the size will be available
 * in the task.
 *
 * Due to hardware constraints, the address of the buffer must be aligned on
 * 4 bytes.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param task        The task used to notify the end of transfer.
 *
 * @retval 0 If successful, -1 if not.
 */
int pi_i2s_read_async(struct pi_device *dev, pi_task_t *task);

/**
 * @brief Read data from the RX queue of a channel in TDM mode.
 *
 * Data received by the I2S interface is stored in the RX queue consisting
 * of two memory blocks preallocated by the user and given to the driver in
 * the configuration. Calling this function will return the next available
 * buffer to the caller, which has to use it before the sampling for this buffer
 * starts again.
 *
 * The data is read in chunks equal to the size of the memory block.
 *
 * This will return data for the specified channel and must only be used in
 * TDM mode.
 *
 * If there is no data in the RX queue the function will block waiting for
 * the next RX memory block to fill in.
 *
 * Due to hardware constraints, the address of the buffer must be aligned on
 * 4 bytes.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param channel ID of the channel, from 0 to the number of channels minus 1.
 * @param mem_block Pointer to the variable storing the address of the RX memory
 *   block containing received data.
 * @param size Pointer to the variable storing the number of bytes read.
 *
 * @retval 0 If successful, -1 if not.
 */
int pi_i2s_channel_read(struct pi_device *dev, int channel, void **mem_block,
    size_t *size);

/**
 * @brief Read data asynchronously from the RX queue of a channel in TDM mode.
 *
 * Data received by the I2S interface is stored in the RX queue consisting
 * of two memory blocks preallocated by the user and given to the driver in
 * the configuration. Calling this function will return the next available
 * buffer to the caller, which has to use it before the sampling for this buffer
 * starts again.
 *
 * The data is read in chunks equal to the size of the memory block.
 *
 * This will return data for the specified channel and must only be used in
 * TDM mode.
 *
 * The specified task will be pushed as soon as data is ready in the RX queue,
 * and the information about the memory block and the size will be available
 * in the task.
 *
 * Due to hardware constraints, the address of the buffer must be aligned on
 * 4 bytes.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param channel ID of the channel, from 0 to the number of channels minus 1.
 * @param task        The task used to notify the end of transfer.
 *
 * @retval 0 If successful, -1 if not.
 */
int pi_i2s_channel_read_async(struct pi_device *dev, int channel,
    pi_task_t *task);

/**
 * @brief Read the status of an asynchronous read.
 *
 * After pi_i2s_read_async is called to be notified when a read buffer is
 * available, and the notification is received, the output information can
 * be retrieved by calling this function.
 *
 * @param task The task used for notification.
 * @param mem_block Pointer to the variable storing the address of the RX memory
 *   block containing received data.
 * @param size Pointer to the variable storing the number of bytes read.
 *
 * @retval 0 If successful, -1 if not.
 */
int pi_i2s_read_status(pi_task_t *task, void **mem_block, size_t *size);

/**
 * @}
 */



/// @cond IMPLEM

#define PI_I2S_SETUP_SINGLE_CLOCK (1<<0)


/// @endcond

#endif
