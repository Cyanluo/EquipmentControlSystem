#pragma once
// MESSAGE TEST PACKING

#define MAVLINK_MSG_ID_TEST 236


typedef struct __mavlink_test_t {
 uint8_t byte1; /*<   byte1*/
 uint8_t byte2; /*<   byte2*/
 uint8_t byte3; /*<   byte3*/
 uint8_t byte4; /*<   byte4*/
 uint8_t byte5; /*<   byte5*/
 uint8_t byte6; /*<   byte6*/
} mavlink_test_t;

#define MAVLINK_MSG_ID_TEST_LEN 6
#define MAVLINK_MSG_ID_TEST_MIN_LEN 6
#define MAVLINK_MSG_ID_236_LEN 6
#define MAVLINK_MSG_ID_236_MIN_LEN 6

#define MAVLINK_MSG_ID_TEST_CRC 28
#define MAVLINK_MSG_ID_236_CRC 28



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TEST { \
    236, \
    "TEST", \
    6, \
    {  { "byte1", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_test_t, byte1) }, \
         { "byte2", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_test_t, byte2) }, \
         { "byte3", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_test_t, byte3) }, \
         { "byte4", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_test_t, byte4) }, \
         { "byte5", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_test_t, byte5) }, \
         { "byte6", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_test_t, byte6) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TEST { \
    "TEST", \
    6, \
    {  { "byte1", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_test_t, byte1) }, \
         { "byte2", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_test_t, byte2) }, \
         { "byte3", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_test_t, byte3) }, \
         { "byte4", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_test_t, byte4) }, \
         { "byte5", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_test_t, byte5) }, \
         { "byte6", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_test_t, byte6) }, \
         } \
}
#endif

/**
 * @brief Pack a test message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param byte1   byte1
 * @param byte2   byte2
 * @param byte3   byte3
 * @param byte4   byte4
 * @param byte5   byte5
 * @param byte6   byte6
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_LEN];
    _mav_put_uint8_t(buf, 0, byte1);
    _mav_put_uint8_t(buf, 1, byte2);
    _mav_put_uint8_t(buf, 2, byte3);
    _mav_put_uint8_t(buf, 3, byte4);
    _mav_put_uint8_t(buf, 4, byte5);
    _mav_put_uint8_t(buf, 5, byte6);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TEST_LEN);
#else
    mavlink_test_t packet;
    packet.byte1 = byte1;
    packet.byte2 = byte2;
    packet.byte3 = byte3;
    packet.byte4 = byte4;
    packet.byte5 = byte5;
    packet.byte6 = byte6;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
}

/**
 * @brief Pack a test message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param byte1   byte1
 * @param byte2   byte2
 * @param byte3   byte3
 * @param byte4   byte4
 * @param byte5   byte5
 * @param byte6   byte6
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t byte1,uint8_t byte2,uint8_t byte3,uint8_t byte4,uint8_t byte5,uint8_t byte6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_LEN];
    _mav_put_uint8_t(buf, 0, byte1);
    _mav_put_uint8_t(buf, 1, byte2);
    _mav_put_uint8_t(buf, 2, byte3);
    _mav_put_uint8_t(buf, 3, byte4);
    _mav_put_uint8_t(buf, 4, byte5);
    _mav_put_uint8_t(buf, 5, byte6);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TEST_LEN);
#else
    mavlink_test_t packet;
    packet.byte1 = byte1;
    packet.byte2 = byte2;
    packet.byte3 = byte3;
    packet.byte4 = byte4;
    packet.byte5 = byte5;
    packet.byte6 = byte6;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
}

/**
 * @brief Encode a test struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_test_t* test)
{
    return mavlink_msg_test_pack(system_id, component_id, msg, test->byte1, test->byte2, test->byte3, test->byte4, test->byte5, test->byte6);
}

/**
 * @brief Encode a test struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_test_t* test)
{
    return mavlink_msg_test_pack_chan(system_id, component_id, chan, msg, test->byte1, test->byte2, test->byte3, test->byte4, test->byte5, test->byte6);
}

/**
 * @brief Send a test message
 * @param chan MAVLink channel to send the message
 *
 * @param byte1   byte1
 * @param byte2   byte2
 * @param byte3   byte3
 * @param byte4   byte4
 * @param byte5   byte5
 * @param byte6   byte6
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_test_send(mavlink_channel_t chan, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_LEN];
    _mav_put_uint8_t(buf, 0, byte1);
    _mav_put_uint8_t(buf, 1, byte2);
    _mav_put_uint8_t(buf, 2, byte3);
    _mav_put_uint8_t(buf, 3, byte4);
    _mav_put_uint8_t(buf, 4, byte5);
    _mav_put_uint8_t(buf, 5, byte6);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, buf, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#else
    mavlink_test_t packet;
    packet.byte1 = byte1;
    packet.byte2 = byte2;
    packet.byte3 = byte3;
    packet.byte4 = byte4;
    packet.byte5 = byte5;
    packet.byte6 = byte6;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, (const char *)&packet, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#endif
}

/**
 * @brief Send a test message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_test_send_struct(mavlink_channel_t chan, const mavlink_test_t* test)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_test_send(chan, test->byte1, test->byte2, test->byte3, test->byte4, test->byte5, test->byte6);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, (const char *)test, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_TEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_test_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4, uint8_t byte5, uint8_t byte6)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, byte1);
    _mav_put_uint8_t(buf, 1, byte2);
    _mav_put_uint8_t(buf, 2, byte3);
    _mav_put_uint8_t(buf, 3, byte4);
    _mav_put_uint8_t(buf, 4, byte5);
    _mav_put_uint8_t(buf, 5, byte6);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, buf, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#else
    mavlink_test_t *packet = (mavlink_test_t *)msgbuf;
    packet->byte1 = byte1;
    packet->byte2 = byte2;
    packet->byte3 = byte3;
    packet->byte4 = byte4;
    packet->byte5 = byte5;
    packet->byte6 = byte6;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, (const char *)packet, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#endif
}
#endif

#endif

// MESSAGE TEST UNPACKING


/**
 * @brief Get field byte1 from test message
 *
 * @return   byte1
 */
static inline uint8_t mavlink_msg_test_get_byte1(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field byte2 from test message
 *
 * @return   byte2
 */
static inline uint8_t mavlink_msg_test_get_byte2(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field byte3 from test message
 *
 * @return   byte3
 */
static inline uint8_t mavlink_msg_test_get_byte3(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field byte4 from test message
 *
 * @return   byte4
 */
static inline uint8_t mavlink_msg_test_get_byte4(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field byte5 from test message
 *
 * @return   byte5
 */
static inline uint8_t mavlink_msg_test_get_byte5(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field byte6 from test message
 *
 * @return   byte6
 */
static inline uint8_t mavlink_msg_test_get_byte6(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Decode a test message into a struct
 *
 * @param msg The message to decode
 * @param test C-struct to decode the message contents into
 */
static inline void mavlink_msg_test_decode(const mavlink_message_t* msg, mavlink_test_t* test)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    test->byte1 = mavlink_msg_test_get_byte1(msg);
    test->byte2 = mavlink_msg_test_get_byte2(msg);
    test->byte3 = mavlink_msg_test_get_byte3(msg);
    test->byte4 = mavlink_msg_test_get_byte4(msg);
    test->byte5 = mavlink_msg_test_get_byte5(msg);
    test->byte6 = mavlink_msg_test_get_byte6(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TEST_LEN? msg->len : MAVLINK_MSG_ID_TEST_LEN;
        memset(test, 0, MAVLINK_MSG_ID_TEST_LEN);
    memcpy(test, _MAV_PAYLOAD(msg), len);
#endif
}
