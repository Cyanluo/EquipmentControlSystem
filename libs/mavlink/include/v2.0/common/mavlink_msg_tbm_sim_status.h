#pragma once
// MESSAGE TBM_SIM_STATUS PACKING

#define MAVLINK_MSG_ID_TBM_SIM_STATUS 601


typedef struct __mavlink_tbm_sim_status_t {
 float rdheader_xb; /*< [mm] the coordinate of roadheader X in the body frame.*/
 float rdheader_yb; /*< [mm] the coordinate of roadheader Y in the body frame.*/
 float rdheader_zb; /*< [mm] the coordinate of roadheader Z in the body frame.*/
 float roll_b; /*<  Attitude roll expressed as Euler angles*/
 float pitch_b; /*<  Attitude pitch expressed as Euler angles*/
 float yaw_b; /*<  Attitude yaw expressed as Euler angles*/
 float boom_cylinder_L; /*< [mm] the stroke of the boom cylinder.*/
 float support_leg_rad; /*< [rad] radians of support leg.*/
 float cutting_header_S; /*< [rad/s] Angular speed of cutting header.*/
 float boom_rad; /*< [rad] radians of support boom cylinder.*/
} mavlink_tbm_sim_status_t;

#define MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN 40
#define MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN 40
#define MAVLINK_MSG_ID_601_LEN 40
#define MAVLINK_MSG_ID_601_MIN_LEN 40

#define MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC 71
#define MAVLINK_MSG_ID_601_CRC 71



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TBM_SIM_STATUS { \
    601, \
    "TBM_SIM_STATUS", \
    10, \
    {  { "rdheader_xb", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tbm_sim_status_t, rdheader_xb) }, \
         { "rdheader_yb", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tbm_sim_status_t, rdheader_yb) }, \
         { "rdheader_zb", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tbm_sim_status_t, rdheader_zb) }, \
         { "roll_b", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_tbm_sim_status_t, roll_b) }, \
         { "pitch_b", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_tbm_sim_status_t, pitch_b) }, \
         { "yaw_b", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_tbm_sim_status_t, yaw_b) }, \
         { "boom_cylinder_L", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_tbm_sim_status_t, boom_cylinder_L) }, \
         { "support_leg_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_tbm_sim_status_t, support_leg_rad) }, \
         { "cutting_header_S", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_tbm_sim_status_t, cutting_header_S) }, \
         { "boom_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_tbm_sim_status_t, boom_rad) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TBM_SIM_STATUS { \
    "TBM_SIM_STATUS", \
    10, \
    {  { "rdheader_xb", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tbm_sim_status_t, rdheader_xb) }, \
         { "rdheader_yb", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tbm_sim_status_t, rdheader_yb) }, \
         { "rdheader_zb", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tbm_sim_status_t, rdheader_zb) }, \
         { "roll_b", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_tbm_sim_status_t, roll_b) }, \
         { "pitch_b", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_tbm_sim_status_t, pitch_b) }, \
         { "yaw_b", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_tbm_sim_status_t, yaw_b) }, \
         { "boom_cylinder_L", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_tbm_sim_status_t, boom_cylinder_L) }, \
         { "support_leg_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_tbm_sim_status_t, support_leg_rad) }, \
         { "cutting_header_S", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_tbm_sim_status_t, cutting_header_S) }, \
         { "boom_rad", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_tbm_sim_status_t, boom_rad) }, \
         } \
}
#endif

/**
 * @brief Pack a tbm_sim_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param rdheader_xb [mm] the coordinate of roadheader X in the body frame.
 * @param rdheader_yb [mm] the coordinate of roadheader Y in the body frame.
 * @param rdheader_zb [mm] the coordinate of roadheader Z in the body frame.
 * @param roll_b  Attitude roll expressed as Euler angles
 * @param pitch_b  Attitude pitch expressed as Euler angles
 * @param yaw_b  Attitude yaw expressed as Euler angles
 * @param boom_cylinder_L [mm] the stroke of the boom cylinder.
 * @param support_leg_rad [rad] radians of support leg.
 * @param cutting_header_S [rad/s] Angular speed of cutting header.
 * @param boom_rad [rad] radians of support boom cylinder.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tbm_sim_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float rdheader_xb, float rdheader_yb, float rdheader_zb, float roll_b, float pitch_b, float yaw_b, float boom_cylinder_L, float support_leg_rad, float cutting_header_S, float boom_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN];
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, roll_b);
    _mav_put_float(buf, 16, pitch_b);
    _mav_put_float(buf, 20, yaw_b);
    _mav_put_float(buf, 24, boom_cylinder_L);
    _mav_put_float(buf, 28, support_leg_rad);
    _mav_put_float(buf, 32, cutting_header_S);
    _mav_put_float(buf, 36, boom_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN);
#else
    mavlink_tbm_sim_status_t packet;
    packet.rdheader_xb = rdheader_xb;
    packet.rdheader_yb = rdheader_yb;
    packet.rdheader_zb = rdheader_zb;
    packet.roll_b = roll_b;
    packet.pitch_b = pitch_b;
    packet.yaw_b = yaw_b;
    packet.boom_cylinder_L = boom_cylinder_L;
    packet.support_leg_rad = support_leg_rad;
    packet.cutting_header_S = cutting_header_S;
    packet.boom_rad = boom_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TBM_SIM_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
}

/**
 * @brief Pack a tbm_sim_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rdheader_xb [mm] the coordinate of roadheader X in the body frame.
 * @param rdheader_yb [mm] the coordinate of roadheader Y in the body frame.
 * @param rdheader_zb [mm] the coordinate of roadheader Z in the body frame.
 * @param roll_b  Attitude roll expressed as Euler angles
 * @param pitch_b  Attitude pitch expressed as Euler angles
 * @param yaw_b  Attitude yaw expressed as Euler angles
 * @param boom_cylinder_L [mm] the stroke of the boom cylinder.
 * @param support_leg_rad [rad] radians of support leg.
 * @param cutting_header_S [rad/s] Angular speed of cutting header.
 * @param boom_rad [rad] radians of support boom cylinder.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tbm_sim_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float rdheader_xb,float rdheader_yb,float rdheader_zb,float roll_b,float pitch_b,float yaw_b,float boom_cylinder_L,float support_leg_rad,float cutting_header_S,float boom_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN];
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, roll_b);
    _mav_put_float(buf, 16, pitch_b);
    _mav_put_float(buf, 20, yaw_b);
    _mav_put_float(buf, 24, boom_cylinder_L);
    _mav_put_float(buf, 28, support_leg_rad);
    _mav_put_float(buf, 32, cutting_header_S);
    _mav_put_float(buf, 36, boom_rad);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN);
#else
    mavlink_tbm_sim_status_t packet;
    packet.rdheader_xb = rdheader_xb;
    packet.rdheader_yb = rdheader_yb;
    packet.rdheader_zb = rdheader_zb;
    packet.roll_b = roll_b;
    packet.pitch_b = pitch_b;
    packet.yaw_b = yaw_b;
    packet.boom_cylinder_L = boom_cylinder_L;
    packet.support_leg_rad = support_leg_rad;
    packet.cutting_header_S = cutting_header_S;
    packet.boom_rad = boom_rad;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TBM_SIM_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
}

/**
 * @brief Encode a tbm_sim_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tbm_sim_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tbm_sim_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tbm_sim_status_t* tbm_sim_status)
{
    return mavlink_msg_tbm_sim_status_pack(system_id, component_id, msg, tbm_sim_status->rdheader_xb, tbm_sim_status->rdheader_yb, tbm_sim_status->rdheader_zb, tbm_sim_status->roll_b, tbm_sim_status->pitch_b, tbm_sim_status->yaw_b, tbm_sim_status->boom_cylinder_L, tbm_sim_status->support_leg_rad, tbm_sim_status->cutting_header_S, tbm_sim_status->boom_rad);
}

/**
 * @brief Encode a tbm_sim_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tbm_sim_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tbm_sim_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tbm_sim_status_t* tbm_sim_status)
{
    return mavlink_msg_tbm_sim_status_pack_chan(system_id, component_id, chan, msg, tbm_sim_status->rdheader_xb, tbm_sim_status->rdheader_yb, tbm_sim_status->rdheader_zb, tbm_sim_status->roll_b, tbm_sim_status->pitch_b, tbm_sim_status->yaw_b, tbm_sim_status->boom_cylinder_L, tbm_sim_status->support_leg_rad, tbm_sim_status->cutting_header_S, tbm_sim_status->boom_rad);
}

/**
 * @brief Send a tbm_sim_status message
 * @param chan MAVLink channel to send the message
 *
 * @param rdheader_xb [mm] the coordinate of roadheader X in the body frame.
 * @param rdheader_yb [mm] the coordinate of roadheader Y in the body frame.
 * @param rdheader_zb [mm] the coordinate of roadheader Z in the body frame.
 * @param roll_b  Attitude roll expressed as Euler angles
 * @param pitch_b  Attitude pitch expressed as Euler angles
 * @param yaw_b  Attitude yaw expressed as Euler angles
 * @param boom_cylinder_L [mm] the stroke of the boom cylinder.
 * @param support_leg_rad [rad] radians of support leg.
 * @param cutting_header_S [rad/s] Angular speed of cutting header.
 * @param boom_rad [rad] radians of support boom cylinder.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tbm_sim_status_send(mavlink_channel_t chan, float rdheader_xb, float rdheader_yb, float rdheader_zb, float roll_b, float pitch_b, float yaw_b, float boom_cylinder_L, float support_leg_rad, float cutting_header_S, float boom_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN];
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, roll_b);
    _mav_put_float(buf, 16, pitch_b);
    _mav_put_float(buf, 20, yaw_b);
    _mav_put_float(buf, 24, boom_cylinder_L);
    _mav_put_float(buf, 28, support_leg_rad);
    _mav_put_float(buf, 32, cutting_header_S);
    _mav_put_float(buf, 36, boom_rad);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_SIM_STATUS, buf, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
#else
    mavlink_tbm_sim_status_t packet;
    packet.rdheader_xb = rdheader_xb;
    packet.rdheader_yb = rdheader_yb;
    packet.rdheader_zb = rdheader_zb;
    packet.roll_b = roll_b;
    packet.pitch_b = pitch_b;
    packet.yaw_b = yaw_b;
    packet.boom_cylinder_L = boom_cylinder_L;
    packet.support_leg_rad = support_leg_rad;
    packet.cutting_header_S = cutting_header_S;
    packet.boom_rad = boom_rad;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_SIM_STATUS, (const char *)&packet, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
#endif
}

/**
 * @brief Send a tbm_sim_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tbm_sim_status_send_struct(mavlink_channel_t chan, const mavlink_tbm_sim_status_t* tbm_sim_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tbm_sim_status_send(chan, tbm_sim_status->rdheader_xb, tbm_sim_status->rdheader_yb, tbm_sim_status->rdheader_zb, tbm_sim_status->roll_b, tbm_sim_status->pitch_b, tbm_sim_status->yaw_b, tbm_sim_status->boom_cylinder_L, tbm_sim_status->support_leg_rad, tbm_sim_status->cutting_header_S, tbm_sim_status->boom_rad);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_SIM_STATUS, (const char *)tbm_sim_status, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tbm_sim_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float rdheader_xb, float rdheader_yb, float rdheader_zb, float roll_b, float pitch_b, float yaw_b, float boom_cylinder_L, float support_leg_rad, float cutting_header_S, float boom_rad)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, roll_b);
    _mav_put_float(buf, 16, pitch_b);
    _mav_put_float(buf, 20, yaw_b);
    _mav_put_float(buf, 24, boom_cylinder_L);
    _mav_put_float(buf, 28, support_leg_rad);
    _mav_put_float(buf, 32, cutting_header_S);
    _mav_put_float(buf, 36, boom_rad);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_SIM_STATUS, buf, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
#else
    mavlink_tbm_sim_status_t *packet = (mavlink_tbm_sim_status_t *)msgbuf;
    packet->rdheader_xb = rdheader_xb;
    packet->rdheader_yb = rdheader_yb;
    packet->rdheader_zb = rdheader_zb;
    packet->roll_b = roll_b;
    packet->pitch_b = pitch_b;
    packet->yaw_b = yaw_b;
    packet->boom_cylinder_L = boom_cylinder_L;
    packet->support_leg_rad = support_leg_rad;
    packet->cutting_header_S = cutting_header_S;
    packet->boom_rad = boom_rad;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_SIM_STATUS, (const char *)packet, MAVLINK_MSG_ID_TBM_SIM_STATUS_MIN_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN, MAVLINK_MSG_ID_TBM_SIM_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE TBM_SIM_STATUS UNPACKING


/**
 * @brief Get field rdheader_xb from tbm_sim_status message
 *
 * @return [mm] the coordinate of roadheader X in the body frame.
 */
static inline float mavlink_msg_tbm_sim_status_get_rdheader_xb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field rdheader_yb from tbm_sim_status message
 *
 * @return [mm] the coordinate of roadheader Y in the body frame.
 */
static inline float mavlink_msg_tbm_sim_status_get_rdheader_yb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field rdheader_zb from tbm_sim_status message
 *
 * @return [mm] the coordinate of roadheader Z in the body frame.
 */
static inline float mavlink_msg_tbm_sim_status_get_rdheader_zb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field roll_b from tbm_sim_status message
 *
 * @return  Attitude roll expressed as Euler angles
 */
static inline float mavlink_msg_tbm_sim_status_get_roll_b(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field pitch_b from tbm_sim_status message
 *
 * @return  Attitude pitch expressed as Euler angles
 */
static inline float mavlink_msg_tbm_sim_status_get_pitch_b(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field yaw_b from tbm_sim_status message
 *
 * @return  Attitude yaw expressed as Euler angles
 */
static inline float mavlink_msg_tbm_sim_status_get_yaw_b(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field boom_cylinder_L from tbm_sim_status message
 *
 * @return [mm] the stroke of the boom cylinder.
 */
static inline float mavlink_msg_tbm_sim_status_get_boom_cylinder_L(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field support_leg_rad from tbm_sim_status message
 *
 * @return [rad] radians of support leg.
 */
static inline float mavlink_msg_tbm_sim_status_get_support_leg_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field cutting_header_S from tbm_sim_status message
 *
 * @return [rad/s] Angular speed of cutting header.
 */
static inline float mavlink_msg_tbm_sim_status_get_cutting_header_S(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field boom_rad from tbm_sim_status message
 *
 * @return [rad] radians of support boom cylinder.
 */
static inline float mavlink_msg_tbm_sim_status_get_boom_rad(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Decode a tbm_sim_status message into a struct
 *
 * @param msg The message to decode
 * @param tbm_sim_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_tbm_sim_status_decode(const mavlink_message_t* msg, mavlink_tbm_sim_status_t* tbm_sim_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tbm_sim_status->rdheader_xb = mavlink_msg_tbm_sim_status_get_rdheader_xb(msg);
    tbm_sim_status->rdheader_yb = mavlink_msg_tbm_sim_status_get_rdheader_yb(msg);
    tbm_sim_status->rdheader_zb = mavlink_msg_tbm_sim_status_get_rdheader_zb(msg);
    tbm_sim_status->roll_b = mavlink_msg_tbm_sim_status_get_roll_b(msg);
    tbm_sim_status->pitch_b = mavlink_msg_tbm_sim_status_get_pitch_b(msg);
    tbm_sim_status->yaw_b = mavlink_msg_tbm_sim_status_get_yaw_b(msg);
    tbm_sim_status->boom_cylinder_L = mavlink_msg_tbm_sim_status_get_boom_cylinder_L(msg);
    tbm_sim_status->support_leg_rad = mavlink_msg_tbm_sim_status_get_support_leg_rad(msg);
    tbm_sim_status->cutting_header_S = mavlink_msg_tbm_sim_status_get_cutting_header_S(msg);
    tbm_sim_status->boom_rad = mavlink_msg_tbm_sim_status_get_boom_rad(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN? msg->len : MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN;
        memset(tbm_sim_status, 0, MAVLINK_MSG_ID_TBM_SIM_STATUS_LEN);
    memcpy(tbm_sim_status, _MAV_PAYLOAD(msg), len);
#endif
}
