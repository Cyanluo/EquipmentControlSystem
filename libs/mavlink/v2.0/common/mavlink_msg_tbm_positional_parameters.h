#pragma once
// MESSAGE TBM_POSITIONAL_PARAMETERS PACKING

#define MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS 600


typedef struct __mavlink_tbm_positional_parameters_t {
 float rdheader_xb; /*< [mm] the coordinate of roadheader X in the body frame.*/
 float rdheader_yb; /*< [mm] the coordinate of roadheader Y in the body frame.*/
 float rdheader_zb; /*< [mm] the coordinate of roadheader Z in the body frame.*/
 float boom_cylinder_L; /*< [cm] the stroke of the boom cylinder.*/
 float turning_angle; /*< [degrees] the angle value of the encoder of the rotary table*/
} mavlink_tbm_positional_parameters_t;

#define MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN 20
#define MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN 20
#define MAVLINK_MSG_ID_600_LEN 20
#define MAVLINK_MSG_ID_600_MIN_LEN 20

#define MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC 252
#define MAVLINK_MSG_ID_600_CRC 252



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TBM_POSITIONAL_PARAMETERS { \
    600, \
    "TBM_POSITIONAL_PARAMETERS", \
    5, \
    {  { "rdheader_xb", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tbm_positional_parameters_t, rdheader_xb) }, \
         { "rdheader_yb", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tbm_positional_parameters_t, rdheader_yb) }, \
         { "rdheader_zb", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tbm_positional_parameters_t, rdheader_zb) }, \
         { "boom_cylinder_L", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_tbm_positional_parameters_t, boom_cylinder_L) }, \
         { "turning_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_tbm_positional_parameters_t, turning_angle) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TBM_POSITIONAL_PARAMETERS { \
    "TBM_POSITIONAL_PARAMETERS", \
    5, \
    {  { "rdheader_xb", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tbm_positional_parameters_t, rdheader_xb) }, \
         { "rdheader_yb", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tbm_positional_parameters_t, rdheader_yb) }, \
         { "rdheader_zb", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tbm_positional_parameters_t, rdheader_zb) }, \
         { "boom_cylinder_L", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_tbm_positional_parameters_t, boom_cylinder_L) }, \
         { "turning_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_tbm_positional_parameters_t, turning_angle) }, \
         } \
}
#endif

/**
 * @brief Pack a tbm_positional_parameters message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param rdheader_xb [mm] the coordinate of roadheader X in the body frame.
 * @param rdheader_yb [mm] the coordinate of roadheader Y in the body frame.
 * @param rdheader_zb [mm] the coordinate of roadheader Z in the body frame.
 * @param boom_cylinder_L [cm] the stroke of the boom cylinder.
 * @param turning_angle [degrees] the angle value of the encoder of the rotary table
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tbm_positional_parameters_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float rdheader_xb, float rdheader_yb, float rdheader_zb, float boom_cylinder_L, float turning_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN];
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, boom_cylinder_L);
    _mav_put_float(buf, 16, turning_angle);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN);
#else
    mavlink_tbm_positional_parameters_t packet;
    packet.rdheader_xb = rdheader_xb;
    packet.rdheader_yb = rdheader_yb;
    packet.rdheader_zb = rdheader_zb;
    packet.boom_cylinder_L = boom_cylinder_L;
    packet.turning_angle = turning_angle;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
}

/**
 * @brief Pack a tbm_positional_parameters message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param rdheader_xb [mm] the coordinate of roadheader X in the body frame.
 * @param rdheader_yb [mm] the coordinate of roadheader Y in the body frame.
 * @param rdheader_zb [mm] the coordinate of roadheader Z in the body frame.
 * @param boom_cylinder_L [cm] the stroke of the boom cylinder.
 * @param turning_angle [degrees] the angle value of the encoder of the rotary table
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tbm_positional_parameters_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float rdheader_xb,float rdheader_yb,float rdheader_zb,float boom_cylinder_L,float turning_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN];
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, boom_cylinder_L);
    _mav_put_float(buf, 16, turning_angle);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN);
#else
    mavlink_tbm_positional_parameters_t packet;
    packet.rdheader_xb = rdheader_xb;
    packet.rdheader_yb = rdheader_yb;
    packet.rdheader_zb = rdheader_zb;
    packet.boom_cylinder_L = boom_cylinder_L;
    packet.turning_angle = turning_angle;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
}

/**
 * @brief Encode a tbm_positional_parameters struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tbm_positional_parameters C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tbm_positional_parameters_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tbm_positional_parameters_t* tbm_positional_parameters)
{
    return mavlink_msg_tbm_positional_parameters_pack(system_id, component_id, msg, tbm_positional_parameters->rdheader_xb, tbm_positional_parameters->rdheader_yb, tbm_positional_parameters->rdheader_zb, tbm_positional_parameters->boom_cylinder_L, tbm_positional_parameters->turning_angle);
}

/**
 * @brief Encode a tbm_positional_parameters struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tbm_positional_parameters C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tbm_positional_parameters_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tbm_positional_parameters_t* tbm_positional_parameters)
{
    return mavlink_msg_tbm_positional_parameters_pack_chan(system_id, component_id, chan, msg, tbm_positional_parameters->rdheader_xb, tbm_positional_parameters->rdheader_yb, tbm_positional_parameters->rdheader_zb, tbm_positional_parameters->boom_cylinder_L, tbm_positional_parameters->turning_angle);
}

/**
 * @brief Send a tbm_positional_parameters message
 * @param chan MAVLink channel to send the message
 *
 * @param rdheader_xb [mm] the coordinate of roadheader X in the body frame.
 * @param rdheader_yb [mm] the coordinate of roadheader Y in the body frame.
 * @param rdheader_zb [mm] the coordinate of roadheader Z in the body frame.
 * @param boom_cylinder_L [cm] the stroke of the boom cylinder.
 * @param turning_angle [degrees] the angle value of the encoder of the rotary table
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tbm_positional_parameters_send(mavlink_channel_t chan, float rdheader_xb, float rdheader_yb, float rdheader_zb, float boom_cylinder_L, float turning_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN];
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, boom_cylinder_L);
    _mav_put_float(buf, 16, turning_angle);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS, buf, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
#else
    mavlink_tbm_positional_parameters_t packet;
    packet.rdheader_xb = rdheader_xb;
    packet.rdheader_yb = rdheader_yb;
    packet.rdheader_zb = rdheader_zb;
    packet.boom_cylinder_L = boom_cylinder_L;
    packet.turning_angle = turning_angle;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS, (const char *)&packet, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
#endif
}

/**
 * @brief Send a tbm_positional_parameters message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tbm_positional_parameters_send_struct(mavlink_channel_t chan, const mavlink_tbm_positional_parameters_t* tbm_positional_parameters)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tbm_positional_parameters_send(chan, tbm_positional_parameters->rdheader_xb, tbm_positional_parameters->rdheader_yb, tbm_positional_parameters->rdheader_zb, tbm_positional_parameters->boom_cylinder_L, tbm_positional_parameters->turning_angle);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS, (const char *)tbm_positional_parameters, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
#endif
}

#if MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tbm_positional_parameters_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float rdheader_xb, float rdheader_yb, float rdheader_zb, float boom_cylinder_L, float turning_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, rdheader_xb);
    _mav_put_float(buf, 4, rdheader_yb);
    _mav_put_float(buf, 8, rdheader_zb);
    _mav_put_float(buf, 12, boom_cylinder_L);
    _mav_put_float(buf, 16, turning_angle);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS, buf, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
#else
    mavlink_tbm_positional_parameters_t *packet = (mavlink_tbm_positional_parameters_t *)msgbuf;
    packet->rdheader_xb = rdheader_xb;
    packet->rdheader_yb = rdheader_yb;
    packet->rdheader_zb = rdheader_zb;
    packet->boom_cylinder_L = boom_cylinder_L;
    packet->turning_angle = turning_angle;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS, (const char *)packet, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_MIN_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_CRC);
#endif
}
#endif

#endif

// MESSAGE TBM_POSITIONAL_PARAMETERS UNPACKING


/**
 * @brief Get field rdheader_xb from tbm_positional_parameters message
 *
 * @return [mm] the coordinate of roadheader X in the body frame.
 */
static inline float mavlink_msg_tbm_positional_parameters_get_rdheader_xb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field rdheader_yb from tbm_positional_parameters message
 *
 * @return [mm] the coordinate of roadheader Y in the body frame.
 */
static inline float mavlink_msg_tbm_positional_parameters_get_rdheader_yb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field rdheader_zb from tbm_positional_parameters message
 *
 * @return [mm] the coordinate of roadheader Z in the body frame.
 */
static inline float mavlink_msg_tbm_positional_parameters_get_rdheader_zb(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field boom_cylinder_L from tbm_positional_parameters message
 *
 * @return [cm] the stroke of the boom cylinder.
 */
static inline float mavlink_msg_tbm_positional_parameters_get_boom_cylinder_L(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field turning_angle from tbm_positional_parameters message
 *
 * @return [degrees] the angle value of the encoder of the rotary table
 */
static inline float mavlink_msg_tbm_positional_parameters_get_turning_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a tbm_positional_parameters message into a struct
 *
 * @param msg The message to decode
 * @param tbm_positional_parameters C-struct to decode the message contents into
 */
static inline void mavlink_msg_tbm_positional_parameters_decode(const mavlink_message_t* msg, mavlink_tbm_positional_parameters_t* tbm_positional_parameters)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tbm_positional_parameters->rdheader_xb = mavlink_msg_tbm_positional_parameters_get_rdheader_xb(msg);
    tbm_positional_parameters->rdheader_yb = mavlink_msg_tbm_positional_parameters_get_rdheader_yb(msg);
    tbm_positional_parameters->rdheader_zb = mavlink_msg_tbm_positional_parameters_get_rdheader_zb(msg);
    tbm_positional_parameters->boom_cylinder_L = mavlink_msg_tbm_positional_parameters_get_boom_cylinder_L(msg);
    tbm_positional_parameters->turning_angle = mavlink_msg_tbm_positional_parameters_get_turning_angle(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN? msg->len : MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN;
        memset(tbm_positional_parameters, 0, MAVLINK_MSG_ID_TBM_POSITIONAL_PARAMETERS_LEN);
    memcpy(tbm_positional_parameters, _MAV_PAYLOAD(msg), len);
#endif
}
