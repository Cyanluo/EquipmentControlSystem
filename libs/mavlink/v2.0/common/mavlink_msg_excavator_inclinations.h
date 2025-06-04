#pragma once
// MESSAGE EXCAVATOR_INCLINATIONS PACKING

#define MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS 603


typedef struct __mavlink_excavator_inclinations_t {
 float roll_deg_x; /*< [deg] roll angle of the boom*/
 float roll_deg_y; /*< [deg] roll angle of the forearm*/
 float roll_deg_z; /*< [deg] roll angle of the bucket*/
 float pitch_deg_x; /*< [deg] pitch angle of the boom*/
 float pitch_deg_y; /*< [deg] pitch angle of the forearm*/
 float pitch_deg_z; /*< [deg] pitch angle of the bucket*/
 float yaw_deg_x; /*< [deg] yaw angle of the boom*/
 float yaw_deg_y; /*< [deg] yaw angle of the forearm*/
 float yaw_deg_z; /*< [deg] yaw angle of the bucket*/
 float roll_acc_x; /*< [rad/s] roll angle acceleration of the boom*/
 float roll_acc_y; /*< [rad/s] roll angle acceleration of the forearm*/
 float roll_acc_z; /*< [rad/s] roll angle acceleration of the bucket*/
 float pitch_acc_x; /*< [rad/s] pitch angle acceleration of the boom*/
 float pitch_acc_y; /*< [rad/s] pitch angle acceleration of the forearm*/
 float pitch_acc_z; /*< [rad/s] pitch angle acceleration of the bucket*/
 float yaw_acc_x; /*< [rad/s] yaw angle acceleration of the boom*/
 float yaw_acc_y; /*< [rad/s] yaw angle acceleration of the forearm*/
 float yaw_acc_z; /*< [rad/s] yaw angle acceleration of the bucket*/
} mavlink_excavator_inclinations_t;

#define MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN 72
#define MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN 72
#define MAVLINK_MSG_ID_603_LEN 72
#define MAVLINK_MSG_ID_603_MIN_LEN 72

#define MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC 55
#define MAVLINK_MSG_ID_603_CRC 55



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_EXCAVATOR_INCLINATIONS { \
    603, \
    "EXCAVATOR_INCLINATIONS", \
    18, \
    {  { "roll_deg_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_excavator_inclinations_t, roll_deg_x) }, \
         { "roll_deg_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_excavator_inclinations_t, roll_deg_y) }, \
         { "roll_deg_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_excavator_inclinations_t, roll_deg_z) }, \
         { "pitch_deg_x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_excavator_inclinations_t, pitch_deg_x) }, \
         { "pitch_deg_y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_excavator_inclinations_t, pitch_deg_y) }, \
         { "pitch_deg_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_excavator_inclinations_t, pitch_deg_z) }, \
         { "yaw_deg_x", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_excavator_inclinations_t, yaw_deg_x) }, \
         { "yaw_deg_y", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_excavator_inclinations_t, yaw_deg_y) }, \
         { "yaw_deg_z", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_excavator_inclinations_t, yaw_deg_z) }, \
         { "roll_acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_excavator_inclinations_t, roll_acc_x) }, \
         { "roll_acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_excavator_inclinations_t, roll_acc_y) }, \
         { "roll_acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_excavator_inclinations_t, roll_acc_z) }, \
         { "pitch_acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_excavator_inclinations_t, pitch_acc_x) }, \
         { "pitch_acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_excavator_inclinations_t, pitch_acc_y) }, \
         { "pitch_acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_excavator_inclinations_t, pitch_acc_z) }, \
         { "yaw_acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_excavator_inclinations_t, yaw_acc_x) }, \
         { "yaw_acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_excavator_inclinations_t, yaw_acc_y) }, \
         { "yaw_acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_excavator_inclinations_t, yaw_acc_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_EXCAVATOR_INCLINATIONS { \
    "EXCAVATOR_INCLINATIONS", \
    18, \
    {  { "roll_deg_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_excavator_inclinations_t, roll_deg_x) }, \
         { "roll_deg_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_excavator_inclinations_t, roll_deg_y) }, \
         { "roll_deg_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_excavator_inclinations_t, roll_deg_z) }, \
         { "pitch_deg_x", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_excavator_inclinations_t, pitch_deg_x) }, \
         { "pitch_deg_y", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_excavator_inclinations_t, pitch_deg_y) }, \
         { "pitch_deg_z", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_excavator_inclinations_t, pitch_deg_z) }, \
         { "yaw_deg_x", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_excavator_inclinations_t, yaw_deg_x) }, \
         { "yaw_deg_y", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_excavator_inclinations_t, yaw_deg_y) }, \
         { "yaw_deg_z", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_excavator_inclinations_t, yaw_deg_z) }, \
         { "roll_acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_excavator_inclinations_t, roll_acc_x) }, \
         { "roll_acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_excavator_inclinations_t, roll_acc_y) }, \
         { "roll_acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_excavator_inclinations_t, roll_acc_z) }, \
         { "pitch_acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_excavator_inclinations_t, pitch_acc_x) }, \
         { "pitch_acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_excavator_inclinations_t, pitch_acc_y) }, \
         { "pitch_acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_excavator_inclinations_t, pitch_acc_z) }, \
         { "yaw_acc_x", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_excavator_inclinations_t, yaw_acc_x) }, \
         { "yaw_acc_y", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_excavator_inclinations_t, yaw_acc_y) }, \
         { "yaw_acc_z", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_excavator_inclinations_t, yaw_acc_z) }, \
         } \
}
#endif

/**
 * @brief Pack a excavator_inclinations message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll_deg_x [deg] roll angle of the boom
 * @param roll_deg_y [deg] roll angle of the forearm
 * @param roll_deg_z [deg] roll angle of the bucket
 * @param pitch_deg_x [deg] pitch angle of the boom
 * @param pitch_deg_y [deg] pitch angle of the forearm
 * @param pitch_deg_z [deg] pitch angle of the bucket
 * @param yaw_deg_x [deg] yaw angle of the boom
 * @param yaw_deg_y [deg] yaw angle of the forearm
 * @param yaw_deg_z [deg] yaw angle of the bucket
 * @param roll_acc_x [rad/s] roll angle acceleration of the boom
 * @param roll_acc_y [rad/s] roll angle acceleration of the forearm
 * @param roll_acc_z [rad/s] roll angle acceleration of the bucket
 * @param pitch_acc_x [rad/s] pitch angle acceleration of the boom
 * @param pitch_acc_y [rad/s] pitch angle acceleration of the forearm
 * @param pitch_acc_z [rad/s] pitch angle acceleration of the bucket
 * @param yaw_acc_x [rad/s] yaw angle acceleration of the boom
 * @param yaw_acc_y [rad/s] yaw angle acceleration of the forearm
 * @param yaw_acc_z [rad/s] yaw angle acceleration of the bucket
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_excavator_inclinations_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll_deg_x, float roll_deg_y, float roll_deg_z, float pitch_deg_x, float pitch_deg_y, float pitch_deg_z, float yaw_deg_x, float yaw_deg_y, float yaw_deg_z, float roll_acc_x, float roll_acc_y, float roll_acc_z, float pitch_acc_x, float pitch_acc_y, float pitch_acc_z, float yaw_acc_x, float yaw_acc_y, float yaw_acc_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN];
    _mav_put_float(buf, 0, roll_deg_x);
    _mav_put_float(buf, 4, roll_deg_y);
    _mav_put_float(buf, 8, roll_deg_z);
    _mav_put_float(buf, 12, pitch_deg_x);
    _mav_put_float(buf, 16, pitch_deg_y);
    _mav_put_float(buf, 20, pitch_deg_z);
    _mav_put_float(buf, 24, yaw_deg_x);
    _mav_put_float(buf, 28, yaw_deg_y);
    _mav_put_float(buf, 32, yaw_deg_z);
    _mav_put_float(buf, 36, roll_acc_x);
    _mav_put_float(buf, 40, roll_acc_y);
    _mav_put_float(buf, 44, roll_acc_z);
    _mav_put_float(buf, 48, pitch_acc_x);
    _mav_put_float(buf, 52, pitch_acc_y);
    _mav_put_float(buf, 56, pitch_acc_z);
    _mav_put_float(buf, 60, yaw_acc_x);
    _mav_put_float(buf, 64, yaw_acc_y);
    _mav_put_float(buf, 68, yaw_acc_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN);
#else
    mavlink_excavator_inclinations_t packet;
    packet.roll_deg_x = roll_deg_x;
    packet.roll_deg_y = roll_deg_y;
    packet.roll_deg_z = roll_deg_z;
    packet.pitch_deg_x = pitch_deg_x;
    packet.pitch_deg_y = pitch_deg_y;
    packet.pitch_deg_z = pitch_deg_z;
    packet.yaw_deg_x = yaw_deg_x;
    packet.yaw_deg_y = yaw_deg_y;
    packet.yaw_deg_z = yaw_deg_z;
    packet.roll_acc_x = roll_acc_x;
    packet.roll_acc_y = roll_acc_y;
    packet.roll_acc_z = roll_acc_z;
    packet.pitch_acc_x = pitch_acc_x;
    packet.pitch_acc_y = pitch_acc_y;
    packet.pitch_acc_z = pitch_acc_z;
    packet.yaw_acc_x = yaw_acc_x;
    packet.yaw_acc_y = yaw_acc_y;
    packet.yaw_acc_z = yaw_acc_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
}

/**
 * @brief Pack a excavator_inclinations message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll_deg_x [deg] roll angle of the boom
 * @param roll_deg_y [deg] roll angle of the forearm
 * @param roll_deg_z [deg] roll angle of the bucket
 * @param pitch_deg_x [deg] pitch angle of the boom
 * @param pitch_deg_y [deg] pitch angle of the forearm
 * @param pitch_deg_z [deg] pitch angle of the bucket
 * @param yaw_deg_x [deg] yaw angle of the boom
 * @param yaw_deg_y [deg] yaw angle of the forearm
 * @param yaw_deg_z [deg] yaw angle of the bucket
 * @param roll_acc_x [rad/s] roll angle acceleration of the boom
 * @param roll_acc_y [rad/s] roll angle acceleration of the forearm
 * @param roll_acc_z [rad/s] roll angle acceleration of the bucket
 * @param pitch_acc_x [rad/s] pitch angle acceleration of the boom
 * @param pitch_acc_y [rad/s] pitch angle acceleration of the forearm
 * @param pitch_acc_z [rad/s] pitch angle acceleration of the bucket
 * @param yaw_acc_x [rad/s] yaw angle acceleration of the boom
 * @param yaw_acc_y [rad/s] yaw angle acceleration of the forearm
 * @param yaw_acc_z [rad/s] yaw angle acceleration of the bucket
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_excavator_inclinations_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll_deg_x,float roll_deg_y,float roll_deg_z,float pitch_deg_x,float pitch_deg_y,float pitch_deg_z,float yaw_deg_x,float yaw_deg_y,float yaw_deg_z,float roll_acc_x,float roll_acc_y,float roll_acc_z,float pitch_acc_x,float pitch_acc_y,float pitch_acc_z,float yaw_acc_x,float yaw_acc_y,float yaw_acc_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN];
    _mav_put_float(buf, 0, roll_deg_x);
    _mav_put_float(buf, 4, roll_deg_y);
    _mav_put_float(buf, 8, roll_deg_z);
    _mav_put_float(buf, 12, pitch_deg_x);
    _mav_put_float(buf, 16, pitch_deg_y);
    _mav_put_float(buf, 20, pitch_deg_z);
    _mav_put_float(buf, 24, yaw_deg_x);
    _mav_put_float(buf, 28, yaw_deg_y);
    _mav_put_float(buf, 32, yaw_deg_z);
    _mav_put_float(buf, 36, roll_acc_x);
    _mav_put_float(buf, 40, roll_acc_y);
    _mav_put_float(buf, 44, roll_acc_z);
    _mav_put_float(buf, 48, pitch_acc_x);
    _mav_put_float(buf, 52, pitch_acc_y);
    _mav_put_float(buf, 56, pitch_acc_z);
    _mav_put_float(buf, 60, yaw_acc_x);
    _mav_put_float(buf, 64, yaw_acc_y);
    _mav_put_float(buf, 68, yaw_acc_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN);
#else
    mavlink_excavator_inclinations_t packet;
    packet.roll_deg_x = roll_deg_x;
    packet.roll_deg_y = roll_deg_y;
    packet.roll_deg_z = roll_deg_z;
    packet.pitch_deg_x = pitch_deg_x;
    packet.pitch_deg_y = pitch_deg_y;
    packet.pitch_deg_z = pitch_deg_z;
    packet.yaw_deg_x = yaw_deg_x;
    packet.yaw_deg_y = yaw_deg_y;
    packet.yaw_deg_z = yaw_deg_z;
    packet.roll_acc_x = roll_acc_x;
    packet.roll_acc_y = roll_acc_y;
    packet.roll_acc_z = roll_acc_z;
    packet.pitch_acc_x = pitch_acc_x;
    packet.pitch_acc_y = pitch_acc_y;
    packet.pitch_acc_z = pitch_acc_z;
    packet.yaw_acc_x = yaw_acc_x;
    packet.yaw_acc_y = yaw_acc_y;
    packet.yaw_acc_z = yaw_acc_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
}

/**
 * @brief Encode a excavator_inclinations struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param excavator_inclinations C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_excavator_inclinations_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_excavator_inclinations_t* excavator_inclinations)
{
    return mavlink_msg_excavator_inclinations_pack(system_id, component_id, msg, excavator_inclinations->roll_deg_x, excavator_inclinations->roll_deg_y, excavator_inclinations->roll_deg_z, excavator_inclinations->pitch_deg_x, excavator_inclinations->pitch_deg_y, excavator_inclinations->pitch_deg_z, excavator_inclinations->yaw_deg_x, excavator_inclinations->yaw_deg_y, excavator_inclinations->yaw_deg_z, excavator_inclinations->roll_acc_x, excavator_inclinations->roll_acc_y, excavator_inclinations->roll_acc_z, excavator_inclinations->pitch_acc_x, excavator_inclinations->pitch_acc_y, excavator_inclinations->pitch_acc_z, excavator_inclinations->yaw_acc_x, excavator_inclinations->yaw_acc_y, excavator_inclinations->yaw_acc_z);
}

/**
 * @brief Encode a excavator_inclinations struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param excavator_inclinations C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_excavator_inclinations_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_excavator_inclinations_t* excavator_inclinations)
{
    return mavlink_msg_excavator_inclinations_pack_chan(system_id, component_id, chan, msg, excavator_inclinations->roll_deg_x, excavator_inclinations->roll_deg_y, excavator_inclinations->roll_deg_z, excavator_inclinations->pitch_deg_x, excavator_inclinations->pitch_deg_y, excavator_inclinations->pitch_deg_z, excavator_inclinations->yaw_deg_x, excavator_inclinations->yaw_deg_y, excavator_inclinations->yaw_deg_z, excavator_inclinations->roll_acc_x, excavator_inclinations->roll_acc_y, excavator_inclinations->roll_acc_z, excavator_inclinations->pitch_acc_x, excavator_inclinations->pitch_acc_y, excavator_inclinations->pitch_acc_z, excavator_inclinations->yaw_acc_x, excavator_inclinations->yaw_acc_y, excavator_inclinations->yaw_acc_z);
}

/**
 * @brief Send a excavator_inclinations message
 * @param chan MAVLink channel to send the message
 *
 * @param roll_deg_x [deg] roll angle of the boom
 * @param roll_deg_y [deg] roll angle of the forearm
 * @param roll_deg_z [deg] roll angle of the bucket
 * @param pitch_deg_x [deg] pitch angle of the boom
 * @param pitch_deg_y [deg] pitch angle of the forearm
 * @param pitch_deg_z [deg] pitch angle of the bucket
 * @param yaw_deg_x [deg] yaw angle of the boom
 * @param yaw_deg_y [deg] yaw angle of the forearm
 * @param yaw_deg_z [deg] yaw angle of the bucket
 * @param roll_acc_x [rad/s] roll angle acceleration of the boom
 * @param roll_acc_y [rad/s] roll angle acceleration of the forearm
 * @param roll_acc_z [rad/s] roll angle acceleration of the bucket
 * @param pitch_acc_x [rad/s] pitch angle acceleration of the boom
 * @param pitch_acc_y [rad/s] pitch angle acceleration of the forearm
 * @param pitch_acc_z [rad/s] pitch angle acceleration of the bucket
 * @param yaw_acc_x [rad/s] yaw angle acceleration of the boom
 * @param yaw_acc_y [rad/s] yaw angle acceleration of the forearm
 * @param yaw_acc_z [rad/s] yaw angle acceleration of the bucket
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_excavator_inclinations_send(mavlink_channel_t chan, float roll_deg_x, float roll_deg_y, float roll_deg_z, float pitch_deg_x, float pitch_deg_y, float pitch_deg_z, float yaw_deg_x, float yaw_deg_y, float yaw_deg_z, float roll_acc_x, float roll_acc_y, float roll_acc_z, float pitch_acc_x, float pitch_acc_y, float pitch_acc_z, float yaw_acc_x, float yaw_acc_y, float yaw_acc_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN];
    _mav_put_float(buf, 0, roll_deg_x);
    _mav_put_float(buf, 4, roll_deg_y);
    _mav_put_float(buf, 8, roll_deg_z);
    _mav_put_float(buf, 12, pitch_deg_x);
    _mav_put_float(buf, 16, pitch_deg_y);
    _mav_put_float(buf, 20, pitch_deg_z);
    _mav_put_float(buf, 24, yaw_deg_x);
    _mav_put_float(buf, 28, yaw_deg_y);
    _mav_put_float(buf, 32, yaw_deg_z);
    _mav_put_float(buf, 36, roll_acc_x);
    _mav_put_float(buf, 40, roll_acc_y);
    _mav_put_float(buf, 44, roll_acc_z);
    _mav_put_float(buf, 48, pitch_acc_x);
    _mav_put_float(buf, 52, pitch_acc_y);
    _mav_put_float(buf, 56, pitch_acc_z);
    _mav_put_float(buf, 60, yaw_acc_x);
    _mav_put_float(buf, 64, yaw_acc_y);
    _mav_put_float(buf, 68, yaw_acc_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS, buf, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
#else
    mavlink_excavator_inclinations_t packet;
    packet.roll_deg_x = roll_deg_x;
    packet.roll_deg_y = roll_deg_y;
    packet.roll_deg_z = roll_deg_z;
    packet.pitch_deg_x = pitch_deg_x;
    packet.pitch_deg_y = pitch_deg_y;
    packet.pitch_deg_z = pitch_deg_z;
    packet.yaw_deg_x = yaw_deg_x;
    packet.yaw_deg_y = yaw_deg_y;
    packet.yaw_deg_z = yaw_deg_z;
    packet.roll_acc_x = roll_acc_x;
    packet.roll_acc_y = roll_acc_y;
    packet.roll_acc_z = roll_acc_z;
    packet.pitch_acc_x = pitch_acc_x;
    packet.pitch_acc_y = pitch_acc_y;
    packet.pitch_acc_z = pitch_acc_z;
    packet.yaw_acc_x = yaw_acc_x;
    packet.yaw_acc_y = yaw_acc_y;
    packet.yaw_acc_z = yaw_acc_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS, (const char *)&packet, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
#endif
}

/**
 * @brief Send a excavator_inclinations message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_excavator_inclinations_send_struct(mavlink_channel_t chan, const mavlink_excavator_inclinations_t* excavator_inclinations)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_excavator_inclinations_send(chan, excavator_inclinations->roll_deg_x, excavator_inclinations->roll_deg_y, excavator_inclinations->roll_deg_z, excavator_inclinations->pitch_deg_x, excavator_inclinations->pitch_deg_y, excavator_inclinations->pitch_deg_z, excavator_inclinations->yaw_deg_x, excavator_inclinations->yaw_deg_y, excavator_inclinations->yaw_deg_z, excavator_inclinations->roll_acc_x, excavator_inclinations->roll_acc_y, excavator_inclinations->roll_acc_z, excavator_inclinations->pitch_acc_x, excavator_inclinations->pitch_acc_y, excavator_inclinations->pitch_acc_z, excavator_inclinations->yaw_acc_x, excavator_inclinations->yaw_acc_y, excavator_inclinations->yaw_acc_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS, (const char *)excavator_inclinations, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
#endif
}

#if MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_excavator_inclinations_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll_deg_x, float roll_deg_y, float roll_deg_z, float pitch_deg_x, float pitch_deg_y, float pitch_deg_z, float yaw_deg_x, float yaw_deg_y, float yaw_deg_z, float roll_acc_x, float roll_acc_y, float roll_acc_z, float pitch_acc_x, float pitch_acc_y, float pitch_acc_z, float yaw_acc_x, float yaw_acc_y, float yaw_acc_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll_deg_x);
    _mav_put_float(buf, 4, roll_deg_y);
    _mav_put_float(buf, 8, roll_deg_z);
    _mav_put_float(buf, 12, pitch_deg_x);
    _mav_put_float(buf, 16, pitch_deg_y);
    _mav_put_float(buf, 20, pitch_deg_z);
    _mav_put_float(buf, 24, yaw_deg_x);
    _mav_put_float(buf, 28, yaw_deg_y);
    _mav_put_float(buf, 32, yaw_deg_z);
    _mav_put_float(buf, 36, roll_acc_x);
    _mav_put_float(buf, 40, roll_acc_y);
    _mav_put_float(buf, 44, roll_acc_z);
    _mav_put_float(buf, 48, pitch_acc_x);
    _mav_put_float(buf, 52, pitch_acc_y);
    _mav_put_float(buf, 56, pitch_acc_z);
    _mav_put_float(buf, 60, yaw_acc_x);
    _mav_put_float(buf, 64, yaw_acc_y);
    _mav_put_float(buf, 68, yaw_acc_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS, buf, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
#else
    mavlink_excavator_inclinations_t *packet = (mavlink_excavator_inclinations_t *)msgbuf;
    packet->roll_deg_x = roll_deg_x;
    packet->roll_deg_y = roll_deg_y;
    packet->roll_deg_z = roll_deg_z;
    packet->pitch_deg_x = pitch_deg_x;
    packet->pitch_deg_y = pitch_deg_y;
    packet->pitch_deg_z = pitch_deg_z;
    packet->yaw_deg_x = yaw_deg_x;
    packet->yaw_deg_y = yaw_deg_y;
    packet->yaw_deg_z = yaw_deg_z;
    packet->roll_acc_x = roll_acc_x;
    packet->roll_acc_y = roll_acc_y;
    packet->roll_acc_z = roll_acc_z;
    packet->pitch_acc_x = pitch_acc_x;
    packet->pitch_acc_y = pitch_acc_y;
    packet->pitch_acc_z = pitch_acc_z;
    packet->yaw_acc_x = yaw_acc_x;
    packet->yaw_acc_y = yaw_acc_y;
    packet->yaw_acc_z = yaw_acc_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS, (const char *)packet, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_MIN_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_CRC);
#endif
}
#endif

#endif

// MESSAGE EXCAVATOR_INCLINATIONS UNPACKING


/**
 * @brief Get field roll_deg_x from excavator_inclinations message
 *
 * @return [deg] roll angle of the boom
 */
static inline float mavlink_msg_excavator_inclinations_get_roll_deg_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field roll_deg_y from excavator_inclinations message
 *
 * @return [deg] roll angle of the forearm
 */
static inline float mavlink_msg_excavator_inclinations_get_roll_deg_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field roll_deg_z from excavator_inclinations message
 *
 * @return [deg] roll angle of the bucket
 */
static inline float mavlink_msg_excavator_inclinations_get_roll_deg_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field pitch_deg_x from excavator_inclinations message
 *
 * @return [deg] pitch angle of the boom
 */
static inline float mavlink_msg_excavator_inclinations_get_pitch_deg_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field pitch_deg_y from excavator_inclinations message
 *
 * @return [deg] pitch angle of the forearm
 */
static inline float mavlink_msg_excavator_inclinations_get_pitch_deg_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field pitch_deg_z from excavator_inclinations message
 *
 * @return [deg] pitch angle of the bucket
 */
static inline float mavlink_msg_excavator_inclinations_get_pitch_deg_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field yaw_deg_x from excavator_inclinations message
 *
 * @return [deg] yaw angle of the boom
 */
static inline float mavlink_msg_excavator_inclinations_get_yaw_deg_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field yaw_deg_y from excavator_inclinations message
 *
 * @return [deg] yaw angle of the forearm
 */
static inline float mavlink_msg_excavator_inclinations_get_yaw_deg_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field yaw_deg_z from excavator_inclinations message
 *
 * @return [deg] yaw angle of the bucket
 */
static inline float mavlink_msg_excavator_inclinations_get_yaw_deg_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field roll_acc_x from excavator_inclinations message
 *
 * @return [rad/s] roll angle acceleration of the boom
 */
static inline float mavlink_msg_excavator_inclinations_get_roll_acc_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field roll_acc_y from excavator_inclinations message
 *
 * @return [rad/s] roll angle acceleration of the forearm
 */
static inline float mavlink_msg_excavator_inclinations_get_roll_acc_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field roll_acc_z from excavator_inclinations message
 *
 * @return [rad/s] roll angle acceleration of the bucket
 */
static inline float mavlink_msg_excavator_inclinations_get_roll_acc_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field pitch_acc_x from excavator_inclinations message
 *
 * @return [rad/s] pitch angle acceleration of the boom
 */
static inline float mavlink_msg_excavator_inclinations_get_pitch_acc_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field pitch_acc_y from excavator_inclinations message
 *
 * @return [rad/s] pitch angle acceleration of the forearm
 */
static inline float mavlink_msg_excavator_inclinations_get_pitch_acc_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field pitch_acc_z from excavator_inclinations message
 *
 * @return [rad/s] pitch angle acceleration of the bucket
 */
static inline float mavlink_msg_excavator_inclinations_get_pitch_acc_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field yaw_acc_x from excavator_inclinations message
 *
 * @return [rad/s] yaw angle acceleration of the boom
 */
static inline float mavlink_msg_excavator_inclinations_get_yaw_acc_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field yaw_acc_y from excavator_inclinations message
 *
 * @return [rad/s] yaw angle acceleration of the forearm
 */
static inline float mavlink_msg_excavator_inclinations_get_yaw_acc_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field yaw_acc_z from excavator_inclinations message
 *
 * @return [rad/s] yaw angle acceleration of the bucket
 */
static inline float mavlink_msg_excavator_inclinations_get_yaw_acc_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Decode a excavator_inclinations message into a struct
 *
 * @param msg The message to decode
 * @param excavator_inclinations C-struct to decode the message contents into
 */
static inline void mavlink_msg_excavator_inclinations_decode(const mavlink_message_t* msg, mavlink_excavator_inclinations_t* excavator_inclinations)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    excavator_inclinations->roll_deg_x = mavlink_msg_excavator_inclinations_get_roll_deg_x(msg);
    excavator_inclinations->roll_deg_y = mavlink_msg_excavator_inclinations_get_roll_deg_y(msg);
    excavator_inclinations->roll_deg_z = mavlink_msg_excavator_inclinations_get_roll_deg_z(msg);
    excavator_inclinations->pitch_deg_x = mavlink_msg_excavator_inclinations_get_pitch_deg_x(msg);
    excavator_inclinations->pitch_deg_y = mavlink_msg_excavator_inclinations_get_pitch_deg_y(msg);
    excavator_inclinations->pitch_deg_z = mavlink_msg_excavator_inclinations_get_pitch_deg_z(msg);
    excavator_inclinations->yaw_deg_x = mavlink_msg_excavator_inclinations_get_yaw_deg_x(msg);
    excavator_inclinations->yaw_deg_y = mavlink_msg_excavator_inclinations_get_yaw_deg_y(msg);
    excavator_inclinations->yaw_deg_z = mavlink_msg_excavator_inclinations_get_yaw_deg_z(msg);
    excavator_inclinations->roll_acc_x = mavlink_msg_excavator_inclinations_get_roll_acc_x(msg);
    excavator_inclinations->roll_acc_y = mavlink_msg_excavator_inclinations_get_roll_acc_y(msg);
    excavator_inclinations->roll_acc_z = mavlink_msg_excavator_inclinations_get_roll_acc_z(msg);
    excavator_inclinations->pitch_acc_x = mavlink_msg_excavator_inclinations_get_pitch_acc_x(msg);
    excavator_inclinations->pitch_acc_y = mavlink_msg_excavator_inclinations_get_pitch_acc_y(msg);
    excavator_inclinations->pitch_acc_z = mavlink_msg_excavator_inclinations_get_pitch_acc_z(msg);
    excavator_inclinations->yaw_acc_x = mavlink_msg_excavator_inclinations_get_yaw_acc_x(msg);
    excavator_inclinations->yaw_acc_y = mavlink_msg_excavator_inclinations_get_yaw_acc_y(msg);
    excavator_inclinations->yaw_acc_z = mavlink_msg_excavator_inclinations_get_yaw_acc_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN? msg->len : MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN;
        memset(excavator_inclinations, 0, MAVLINK_MSG_ID_EXCAVATOR_INCLINATIONS_LEN);
    memcpy(excavator_inclinations, _MAV_PAYLOAD(msg), len);
#endif
}
