#pragma once
// MESSAGE TBM_UNITY_INTERFACE PACKING

#define MAVLINK_MSG_ID_TBM_UNITY_INTERFACE 602


typedef struct __mavlink_tbm_unity_interface_t {
 float HuiZhuanTai_Left_Length; /*< [mm] HuiZhuanTai_Left_Length*/
 float HuiZhuanTai_Right_Length; /*< [mm] HuiZhuanTai_Right_Length*/
 float HuiZhuanTai_Left_Angle; /*< [rad] HuiZhuanTai_Left_Angle*/
 float HuiZhuanTai_Right_Angle; /*< [rad] HuiZhuanTai_Right_Angle*/
 float HuiZhuanTai_Angle; /*< [rad] HuiZhuanTai_Angle*/
 float DaBi_SiGan_Angle; /*< [rad] DaBi_SiGan_Angle*/
 float DaBi_SiGan_Length; /*< [mm] DaBi_SiGan_Length*/
 float Dianji_Angle_HZT; /*< [rad] Dianji_Angle_HZT*/
 float JieGeBuShenSuo_Length; /*< [mm] JieGeBuShenSuo_Length*/
 float JieGeTou_Rot_Speed; /*< [rad/s] JieGeTou_Rot_Speed*/
 float HouTuiCheng_Angle; /*< [rad] HouTuiCheng_Angle*/
 float roll; /*<  Attitude roll expressed as Euler angles, not recommended except for human-readable outputs*/
 float pitch; /*<  Attitude pitch expressed as Euler angles, not recommended except for human-readable outputs*/
 float yaw; /*<  Attitude yaw expressed as Euler angles, not recommended except for human-readable outputs*/
 float lat; /*< [deg] Latitude*1e7*/
 float lon; /*< [deg] Longitude*1e7*/
 float alt; /*< [m] Altitude*/
 float vn; /*< [m/s] True velocity in north direction in earth-fixed NED frame*/
 float ve; /*< [m/s] True velocity in east direction in earth-fixed NED frame*/
 float vd; /*< [m/s] True velocity in down direction in earth-fixed NED frame*/
 float xgyro; /*< [rad/s] Angular speed around X axis*/
 float ygyro; /*< [rad/s] Angular speed around Y axis*/
 float zgyro; /*< [rad/s] Angular speed around Z axis*/
} mavlink_tbm_unity_interface_t;

#define MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN 92
#define MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN 92
#define MAVLINK_MSG_ID_602_LEN 92
#define MAVLINK_MSG_ID_602_MIN_LEN 92

#define MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC 58
#define MAVLINK_MSG_ID_602_CRC 58



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TBM_UNITY_INTERFACE { \
    602, \
    "TBM_UNITY_INTERFACE", \
    23, \
    {  { "HuiZhuanTai_Left_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Left_Length) }, \
         { "HuiZhuanTai_Right_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Right_Length) }, \
         { "HuiZhuanTai_Left_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Left_Angle) }, \
         { "HuiZhuanTai_Right_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Right_Angle) }, \
         { "HuiZhuanTai_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Angle) }, \
         { "DaBi_SiGan_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_tbm_unity_interface_t, DaBi_SiGan_Angle) }, \
         { "DaBi_SiGan_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_tbm_unity_interface_t, DaBi_SiGan_Length) }, \
         { "Dianji_Angle_HZT", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_tbm_unity_interface_t, Dianji_Angle_HZT) }, \
         { "JieGeBuShenSuo_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_tbm_unity_interface_t, JieGeBuShenSuo_Length) }, \
         { "JieGeTou_Rot_Speed", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_tbm_unity_interface_t, JieGeTou_Rot_Speed) }, \
         { "HouTuiCheng_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_tbm_unity_interface_t, HouTuiCheng_Angle) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_tbm_unity_interface_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_tbm_unity_interface_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_tbm_unity_interface_t, yaw) }, \
         { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_tbm_unity_interface_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_tbm_unity_interface_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_tbm_unity_interface_t, alt) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_tbm_unity_interface_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_tbm_unity_interface_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_tbm_unity_interface_t, vd) }, \
         { "xgyro", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_tbm_unity_interface_t, xgyro) }, \
         { "ygyro", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_tbm_unity_interface_t, ygyro) }, \
         { "zgyro", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_tbm_unity_interface_t, zgyro) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TBM_UNITY_INTERFACE { \
    "TBM_UNITY_INTERFACE", \
    23, \
    {  { "HuiZhuanTai_Left_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Left_Length) }, \
         { "HuiZhuanTai_Right_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Right_Length) }, \
         { "HuiZhuanTai_Left_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Left_Angle) }, \
         { "HuiZhuanTai_Right_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Right_Angle) }, \
         { "HuiZhuanTai_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_tbm_unity_interface_t, HuiZhuanTai_Angle) }, \
         { "DaBi_SiGan_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_tbm_unity_interface_t, DaBi_SiGan_Angle) }, \
         { "DaBi_SiGan_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_tbm_unity_interface_t, DaBi_SiGan_Length) }, \
         { "Dianji_Angle_HZT", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_tbm_unity_interface_t, Dianji_Angle_HZT) }, \
         { "JieGeBuShenSuo_Length", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_tbm_unity_interface_t, JieGeBuShenSuo_Length) }, \
         { "JieGeTou_Rot_Speed", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_tbm_unity_interface_t, JieGeTou_Rot_Speed) }, \
         { "HouTuiCheng_Angle", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_tbm_unity_interface_t, HouTuiCheng_Angle) }, \
         { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_tbm_unity_interface_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_tbm_unity_interface_t, pitch) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_tbm_unity_interface_t, yaw) }, \
         { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_tbm_unity_interface_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_tbm_unity_interface_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_tbm_unity_interface_t, alt) }, \
         { "vn", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_tbm_unity_interface_t, vn) }, \
         { "ve", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_tbm_unity_interface_t, ve) }, \
         { "vd", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_tbm_unity_interface_t, vd) }, \
         { "xgyro", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_tbm_unity_interface_t, xgyro) }, \
         { "ygyro", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_tbm_unity_interface_t, ygyro) }, \
         { "zgyro", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_tbm_unity_interface_t, zgyro) }, \
         } \
}
#endif

/**
 * @brief Pack a tbm_unity_interface message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param HuiZhuanTai_Left_Length [mm] HuiZhuanTai_Left_Length
 * @param HuiZhuanTai_Right_Length [mm] HuiZhuanTai_Right_Length
 * @param HuiZhuanTai_Left_Angle [rad] HuiZhuanTai_Left_Angle
 * @param HuiZhuanTai_Right_Angle [rad] HuiZhuanTai_Right_Angle
 * @param HuiZhuanTai_Angle [rad] HuiZhuanTai_Angle
 * @param DaBi_SiGan_Angle [rad] DaBi_SiGan_Angle
 * @param DaBi_SiGan_Length [mm] DaBi_SiGan_Length
 * @param Dianji_Angle_HZT [rad] Dianji_Angle_HZT
 * @param JieGeBuShenSuo_Length [mm] JieGeBuShenSuo_Length
 * @param JieGeTou_Rot_Speed [rad/s] JieGeTou_Rot_Speed
 * @param HouTuiCheng_Angle [rad] HouTuiCheng_Angle
 * @param roll  Attitude roll expressed as Euler angles, not recommended except for human-readable outputs
 * @param pitch  Attitude pitch expressed as Euler angles, not recommended except for human-readable outputs
 * @param yaw  Attitude yaw expressed as Euler angles, not recommended except for human-readable outputs
 * @param lat [deg] Latitude*1e7
 * @param lon [deg] Longitude*1e7
 * @param alt [m] Altitude
 * @param vn [m/s] True velocity in north direction in earth-fixed NED frame
 * @param ve [m/s] True velocity in east direction in earth-fixed NED frame
 * @param vd [m/s] True velocity in down direction in earth-fixed NED frame
 * @param xgyro [rad/s] Angular speed around X axis
 * @param ygyro [rad/s] Angular speed around Y axis
 * @param zgyro [rad/s] Angular speed around Z axis
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tbm_unity_interface_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float HuiZhuanTai_Left_Length, float HuiZhuanTai_Right_Length, float HuiZhuanTai_Left_Angle, float HuiZhuanTai_Right_Angle, float HuiZhuanTai_Angle, float DaBi_SiGan_Angle, float DaBi_SiGan_Length, float Dianji_Angle_HZT, float JieGeBuShenSuo_Length, float JieGeTou_Rot_Speed, float HouTuiCheng_Angle, float roll, float pitch, float yaw, float lat, float lon, float alt, float vn, float ve, float vd, float xgyro, float ygyro, float zgyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN];
    _mav_put_float(buf, 0, HuiZhuanTai_Left_Length);
    _mav_put_float(buf, 4, HuiZhuanTai_Right_Length);
    _mav_put_float(buf, 8, HuiZhuanTai_Left_Angle);
    _mav_put_float(buf, 12, HuiZhuanTai_Right_Angle);
    _mav_put_float(buf, 16, HuiZhuanTai_Angle);
    _mav_put_float(buf, 20, DaBi_SiGan_Angle);
    _mav_put_float(buf, 24, DaBi_SiGan_Length);
    _mav_put_float(buf, 28, Dianji_Angle_HZT);
    _mav_put_float(buf, 32, JieGeBuShenSuo_Length);
    _mav_put_float(buf, 36, JieGeTou_Rot_Speed);
    _mav_put_float(buf, 40, HouTuiCheng_Angle);
    _mav_put_float(buf, 44, roll);
    _mav_put_float(buf, 48, pitch);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, lat);
    _mav_put_float(buf, 60, lon);
    _mav_put_float(buf, 64, alt);
    _mav_put_float(buf, 68, vn);
    _mav_put_float(buf, 72, ve);
    _mav_put_float(buf, 76, vd);
    _mav_put_float(buf, 80, xgyro);
    _mav_put_float(buf, 84, ygyro);
    _mav_put_float(buf, 88, zgyro);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN);
#else
    mavlink_tbm_unity_interface_t packet;
    packet.HuiZhuanTai_Left_Length = HuiZhuanTai_Left_Length;
    packet.HuiZhuanTai_Right_Length = HuiZhuanTai_Right_Length;
    packet.HuiZhuanTai_Left_Angle = HuiZhuanTai_Left_Angle;
    packet.HuiZhuanTai_Right_Angle = HuiZhuanTai_Right_Angle;
    packet.HuiZhuanTai_Angle = HuiZhuanTai_Angle;
    packet.DaBi_SiGan_Angle = DaBi_SiGan_Angle;
    packet.DaBi_SiGan_Length = DaBi_SiGan_Length;
    packet.Dianji_Angle_HZT = Dianji_Angle_HZT;
    packet.JieGeBuShenSuo_Length = JieGeBuShenSuo_Length;
    packet.JieGeTou_Rot_Speed = JieGeTou_Rot_Speed;
    packet.HouTuiCheng_Angle = HouTuiCheng_Angle;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TBM_UNITY_INTERFACE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
}

/**
 * @brief Pack a tbm_unity_interface message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param HuiZhuanTai_Left_Length [mm] HuiZhuanTai_Left_Length
 * @param HuiZhuanTai_Right_Length [mm] HuiZhuanTai_Right_Length
 * @param HuiZhuanTai_Left_Angle [rad] HuiZhuanTai_Left_Angle
 * @param HuiZhuanTai_Right_Angle [rad] HuiZhuanTai_Right_Angle
 * @param HuiZhuanTai_Angle [rad] HuiZhuanTai_Angle
 * @param DaBi_SiGan_Angle [rad] DaBi_SiGan_Angle
 * @param DaBi_SiGan_Length [mm] DaBi_SiGan_Length
 * @param Dianji_Angle_HZT [rad] Dianji_Angle_HZT
 * @param JieGeBuShenSuo_Length [mm] JieGeBuShenSuo_Length
 * @param JieGeTou_Rot_Speed [rad/s] JieGeTou_Rot_Speed
 * @param HouTuiCheng_Angle [rad] HouTuiCheng_Angle
 * @param roll  Attitude roll expressed as Euler angles, not recommended except for human-readable outputs
 * @param pitch  Attitude pitch expressed as Euler angles, not recommended except for human-readable outputs
 * @param yaw  Attitude yaw expressed as Euler angles, not recommended except for human-readable outputs
 * @param lat [deg] Latitude*1e7
 * @param lon [deg] Longitude*1e7
 * @param alt [m] Altitude
 * @param vn [m/s] True velocity in north direction in earth-fixed NED frame
 * @param ve [m/s] True velocity in east direction in earth-fixed NED frame
 * @param vd [m/s] True velocity in down direction in earth-fixed NED frame
 * @param xgyro [rad/s] Angular speed around X axis
 * @param ygyro [rad/s] Angular speed around Y axis
 * @param zgyro [rad/s] Angular speed around Z axis
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_tbm_unity_interface_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float HuiZhuanTai_Left_Length,float HuiZhuanTai_Right_Length,float HuiZhuanTai_Left_Angle,float HuiZhuanTai_Right_Angle,float HuiZhuanTai_Angle,float DaBi_SiGan_Angle,float DaBi_SiGan_Length,float Dianji_Angle_HZT,float JieGeBuShenSuo_Length,float JieGeTou_Rot_Speed,float HouTuiCheng_Angle,float roll,float pitch,float yaw,float lat,float lon,float alt,float vn,float ve,float vd,float xgyro,float ygyro,float zgyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN];
    _mav_put_float(buf, 0, HuiZhuanTai_Left_Length);
    _mav_put_float(buf, 4, HuiZhuanTai_Right_Length);
    _mav_put_float(buf, 8, HuiZhuanTai_Left_Angle);
    _mav_put_float(buf, 12, HuiZhuanTai_Right_Angle);
    _mav_put_float(buf, 16, HuiZhuanTai_Angle);
    _mav_put_float(buf, 20, DaBi_SiGan_Angle);
    _mav_put_float(buf, 24, DaBi_SiGan_Length);
    _mav_put_float(buf, 28, Dianji_Angle_HZT);
    _mav_put_float(buf, 32, JieGeBuShenSuo_Length);
    _mav_put_float(buf, 36, JieGeTou_Rot_Speed);
    _mav_put_float(buf, 40, HouTuiCheng_Angle);
    _mav_put_float(buf, 44, roll);
    _mav_put_float(buf, 48, pitch);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, lat);
    _mav_put_float(buf, 60, lon);
    _mav_put_float(buf, 64, alt);
    _mav_put_float(buf, 68, vn);
    _mav_put_float(buf, 72, ve);
    _mav_put_float(buf, 76, vd);
    _mav_put_float(buf, 80, xgyro);
    _mav_put_float(buf, 84, ygyro);
    _mav_put_float(buf, 88, zgyro);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN);
#else
    mavlink_tbm_unity_interface_t packet;
    packet.HuiZhuanTai_Left_Length = HuiZhuanTai_Left_Length;
    packet.HuiZhuanTai_Right_Length = HuiZhuanTai_Right_Length;
    packet.HuiZhuanTai_Left_Angle = HuiZhuanTai_Left_Angle;
    packet.HuiZhuanTai_Right_Angle = HuiZhuanTai_Right_Angle;
    packet.HuiZhuanTai_Angle = HuiZhuanTai_Angle;
    packet.DaBi_SiGan_Angle = DaBi_SiGan_Angle;
    packet.DaBi_SiGan_Length = DaBi_SiGan_Length;
    packet.Dianji_Angle_HZT = Dianji_Angle_HZT;
    packet.JieGeBuShenSuo_Length = JieGeBuShenSuo_Length;
    packet.JieGeTou_Rot_Speed = JieGeTou_Rot_Speed;
    packet.HouTuiCheng_Angle = HouTuiCheng_Angle;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TBM_UNITY_INTERFACE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
}

/**
 * @brief Encode a tbm_unity_interface struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param tbm_unity_interface C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tbm_unity_interface_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_tbm_unity_interface_t* tbm_unity_interface)
{
    return mavlink_msg_tbm_unity_interface_pack(system_id, component_id, msg, tbm_unity_interface->HuiZhuanTai_Left_Length, tbm_unity_interface->HuiZhuanTai_Right_Length, tbm_unity_interface->HuiZhuanTai_Left_Angle, tbm_unity_interface->HuiZhuanTai_Right_Angle, tbm_unity_interface->HuiZhuanTai_Angle, tbm_unity_interface->DaBi_SiGan_Angle, tbm_unity_interface->DaBi_SiGan_Length, tbm_unity_interface->Dianji_Angle_HZT, tbm_unity_interface->JieGeBuShenSuo_Length, tbm_unity_interface->JieGeTou_Rot_Speed, tbm_unity_interface->HouTuiCheng_Angle, tbm_unity_interface->roll, tbm_unity_interface->pitch, tbm_unity_interface->yaw, tbm_unity_interface->lat, tbm_unity_interface->lon, tbm_unity_interface->alt, tbm_unity_interface->vn, tbm_unity_interface->ve, tbm_unity_interface->vd, tbm_unity_interface->xgyro, tbm_unity_interface->ygyro, tbm_unity_interface->zgyro);
}

/**
 * @brief Encode a tbm_unity_interface struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param tbm_unity_interface C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_tbm_unity_interface_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_tbm_unity_interface_t* tbm_unity_interface)
{
    return mavlink_msg_tbm_unity_interface_pack_chan(system_id, component_id, chan, msg, tbm_unity_interface->HuiZhuanTai_Left_Length, tbm_unity_interface->HuiZhuanTai_Right_Length, tbm_unity_interface->HuiZhuanTai_Left_Angle, tbm_unity_interface->HuiZhuanTai_Right_Angle, tbm_unity_interface->HuiZhuanTai_Angle, tbm_unity_interface->DaBi_SiGan_Angle, tbm_unity_interface->DaBi_SiGan_Length, tbm_unity_interface->Dianji_Angle_HZT, tbm_unity_interface->JieGeBuShenSuo_Length, tbm_unity_interface->JieGeTou_Rot_Speed, tbm_unity_interface->HouTuiCheng_Angle, tbm_unity_interface->roll, tbm_unity_interface->pitch, tbm_unity_interface->yaw, tbm_unity_interface->lat, tbm_unity_interface->lon, tbm_unity_interface->alt, tbm_unity_interface->vn, tbm_unity_interface->ve, tbm_unity_interface->vd, tbm_unity_interface->xgyro, tbm_unity_interface->ygyro, tbm_unity_interface->zgyro);
}

/**
 * @brief Send a tbm_unity_interface message
 * @param chan MAVLink channel to send the message
 *
 * @param HuiZhuanTai_Left_Length [mm] HuiZhuanTai_Left_Length
 * @param HuiZhuanTai_Right_Length [mm] HuiZhuanTai_Right_Length
 * @param HuiZhuanTai_Left_Angle [rad] HuiZhuanTai_Left_Angle
 * @param HuiZhuanTai_Right_Angle [rad] HuiZhuanTai_Right_Angle
 * @param HuiZhuanTai_Angle [rad] HuiZhuanTai_Angle
 * @param DaBi_SiGan_Angle [rad] DaBi_SiGan_Angle
 * @param DaBi_SiGan_Length [mm] DaBi_SiGan_Length
 * @param Dianji_Angle_HZT [rad] Dianji_Angle_HZT
 * @param JieGeBuShenSuo_Length [mm] JieGeBuShenSuo_Length
 * @param JieGeTou_Rot_Speed [rad/s] JieGeTou_Rot_Speed
 * @param HouTuiCheng_Angle [rad] HouTuiCheng_Angle
 * @param roll  Attitude roll expressed as Euler angles, not recommended except for human-readable outputs
 * @param pitch  Attitude pitch expressed as Euler angles, not recommended except for human-readable outputs
 * @param yaw  Attitude yaw expressed as Euler angles, not recommended except for human-readable outputs
 * @param lat [deg] Latitude*1e7
 * @param lon [deg] Longitude*1e7
 * @param alt [m] Altitude
 * @param vn [m/s] True velocity in north direction in earth-fixed NED frame
 * @param ve [m/s] True velocity in east direction in earth-fixed NED frame
 * @param vd [m/s] True velocity in down direction in earth-fixed NED frame
 * @param xgyro [rad/s] Angular speed around X axis
 * @param ygyro [rad/s] Angular speed around Y axis
 * @param zgyro [rad/s] Angular speed around Z axis
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_tbm_unity_interface_send(mavlink_channel_t chan, float HuiZhuanTai_Left_Length, float HuiZhuanTai_Right_Length, float HuiZhuanTai_Left_Angle, float HuiZhuanTai_Right_Angle, float HuiZhuanTai_Angle, float DaBi_SiGan_Angle, float DaBi_SiGan_Length, float Dianji_Angle_HZT, float JieGeBuShenSuo_Length, float JieGeTou_Rot_Speed, float HouTuiCheng_Angle, float roll, float pitch, float yaw, float lat, float lon, float alt, float vn, float ve, float vd, float xgyro, float ygyro, float zgyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN];
    _mav_put_float(buf, 0, HuiZhuanTai_Left_Length);
    _mav_put_float(buf, 4, HuiZhuanTai_Right_Length);
    _mav_put_float(buf, 8, HuiZhuanTai_Left_Angle);
    _mav_put_float(buf, 12, HuiZhuanTai_Right_Angle);
    _mav_put_float(buf, 16, HuiZhuanTai_Angle);
    _mav_put_float(buf, 20, DaBi_SiGan_Angle);
    _mav_put_float(buf, 24, DaBi_SiGan_Length);
    _mav_put_float(buf, 28, Dianji_Angle_HZT);
    _mav_put_float(buf, 32, JieGeBuShenSuo_Length);
    _mav_put_float(buf, 36, JieGeTou_Rot_Speed);
    _mav_put_float(buf, 40, HouTuiCheng_Angle);
    _mav_put_float(buf, 44, roll);
    _mav_put_float(buf, 48, pitch);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, lat);
    _mav_put_float(buf, 60, lon);
    _mav_put_float(buf, 64, alt);
    _mav_put_float(buf, 68, vn);
    _mav_put_float(buf, 72, ve);
    _mav_put_float(buf, 76, vd);
    _mav_put_float(buf, 80, xgyro);
    _mav_put_float(buf, 84, ygyro);
    _mav_put_float(buf, 88, zgyro);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE, buf, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
#else
    mavlink_tbm_unity_interface_t packet;
    packet.HuiZhuanTai_Left_Length = HuiZhuanTai_Left_Length;
    packet.HuiZhuanTai_Right_Length = HuiZhuanTai_Right_Length;
    packet.HuiZhuanTai_Left_Angle = HuiZhuanTai_Left_Angle;
    packet.HuiZhuanTai_Right_Angle = HuiZhuanTai_Right_Angle;
    packet.HuiZhuanTai_Angle = HuiZhuanTai_Angle;
    packet.DaBi_SiGan_Angle = DaBi_SiGan_Angle;
    packet.DaBi_SiGan_Length = DaBi_SiGan_Length;
    packet.Dianji_Angle_HZT = Dianji_Angle_HZT;
    packet.JieGeBuShenSuo_Length = JieGeBuShenSuo_Length;
    packet.JieGeTou_Rot_Speed = JieGeTou_Rot_Speed;
    packet.HouTuiCheng_Angle = HouTuiCheng_Angle;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.yaw = yaw;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.vn = vn;
    packet.ve = ve;
    packet.vd = vd;
    packet.xgyro = xgyro;
    packet.ygyro = ygyro;
    packet.zgyro = zgyro;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE, (const char *)&packet, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
#endif
}

/**
 * @brief Send a tbm_unity_interface message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_tbm_unity_interface_send_struct(mavlink_channel_t chan, const mavlink_tbm_unity_interface_t* tbm_unity_interface)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_tbm_unity_interface_send(chan, tbm_unity_interface->HuiZhuanTai_Left_Length, tbm_unity_interface->HuiZhuanTai_Right_Length, tbm_unity_interface->HuiZhuanTai_Left_Angle, tbm_unity_interface->HuiZhuanTai_Right_Angle, tbm_unity_interface->HuiZhuanTai_Angle, tbm_unity_interface->DaBi_SiGan_Angle, tbm_unity_interface->DaBi_SiGan_Length, tbm_unity_interface->Dianji_Angle_HZT, tbm_unity_interface->JieGeBuShenSuo_Length, tbm_unity_interface->JieGeTou_Rot_Speed, tbm_unity_interface->HouTuiCheng_Angle, tbm_unity_interface->roll, tbm_unity_interface->pitch, tbm_unity_interface->yaw, tbm_unity_interface->lat, tbm_unity_interface->lon, tbm_unity_interface->alt, tbm_unity_interface->vn, tbm_unity_interface->ve, tbm_unity_interface->vd, tbm_unity_interface->xgyro, tbm_unity_interface->ygyro, tbm_unity_interface->zgyro);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE, (const char *)tbm_unity_interface, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
#endif
}

#if MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_tbm_unity_interface_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float HuiZhuanTai_Left_Length, float HuiZhuanTai_Right_Length, float HuiZhuanTai_Left_Angle, float HuiZhuanTai_Right_Angle, float HuiZhuanTai_Angle, float DaBi_SiGan_Angle, float DaBi_SiGan_Length, float Dianji_Angle_HZT, float JieGeBuShenSuo_Length, float JieGeTou_Rot_Speed, float HouTuiCheng_Angle, float roll, float pitch, float yaw, float lat, float lon, float alt, float vn, float ve, float vd, float xgyro, float ygyro, float zgyro)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, HuiZhuanTai_Left_Length);
    _mav_put_float(buf, 4, HuiZhuanTai_Right_Length);
    _mav_put_float(buf, 8, HuiZhuanTai_Left_Angle);
    _mav_put_float(buf, 12, HuiZhuanTai_Right_Angle);
    _mav_put_float(buf, 16, HuiZhuanTai_Angle);
    _mav_put_float(buf, 20, DaBi_SiGan_Angle);
    _mav_put_float(buf, 24, DaBi_SiGan_Length);
    _mav_put_float(buf, 28, Dianji_Angle_HZT);
    _mav_put_float(buf, 32, JieGeBuShenSuo_Length);
    _mav_put_float(buf, 36, JieGeTou_Rot_Speed);
    _mav_put_float(buf, 40, HouTuiCheng_Angle);
    _mav_put_float(buf, 44, roll);
    _mav_put_float(buf, 48, pitch);
    _mav_put_float(buf, 52, yaw);
    _mav_put_float(buf, 56, lat);
    _mav_put_float(buf, 60, lon);
    _mav_put_float(buf, 64, alt);
    _mav_put_float(buf, 68, vn);
    _mav_put_float(buf, 72, ve);
    _mav_put_float(buf, 76, vd);
    _mav_put_float(buf, 80, xgyro);
    _mav_put_float(buf, 84, ygyro);
    _mav_put_float(buf, 88, zgyro);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE, buf, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
#else
    mavlink_tbm_unity_interface_t *packet = (mavlink_tbm_unity_interface_t *)msgbuf;
    packet->HuiZhuanTai_Left_Length = HuiZhuanTai_Left_Length;
    packet->HuiZhuanTai_Right_Length = HuiZhuanTai_Right_Length;
    packet->HuiZhuanTai_Left_Angle = HuiZhuanTai_Left_Angle;
    packet->HuiZhuanTai_Right_Angle = HuiZhuanTai_Right_Angle;
    packet->HuiZhuanTai_Angle = HuiZhuanTai_Angle;
    packet->DaBi_SiGan_Angle = DaBi_SiGan_Angle;
    packet->DaBi_SiGan_Length = DaBi_SiGan_Length;
    packet->Dianji_Angle_HZT = Dianji_Angle_HZT;
    packet->JieGeBuShenSuo_Length = JieGeBuShenSuo_Length;
    packet->JieGeTou_Rot_Speed = JieGeTou_Rot_Speed;
    packet->HouTuiCheng_Angle = HouTuiCheng_Angle;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->yaw = yaw;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->vn = vn;
    packet->ve = ve;
    packet->vd = vd;
    packet->xgyro = xgyro;
    packet->ygyro = ygyro;
    packet->zgyro = zgyro;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE, (const char *)packet, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_MIN_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_CRC);
#endif
}
#endif

#endif

// MESSAGE TBM_UNITY_INTERFACE UNPACKING


/**
 * @brief Get field HuiZhuanTai_Left_Length from tbm_unity_interface message
 *
 * @return [mm] HuiZhuanTai_Left_Length
 */
static inline float mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Left_Length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field HuiZhuanTai_Right_Length from tbm_unity_interface message
 *
 * @return [mm] HuiZhuanTai_Right_Length
 */
static inline float mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Right_Length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field HuiZhuanTai_Left_Angle from tbm_unity_interface message
 *
 * @return [rad] HuiZhuanTai_Left_Angle
 */
static inline float mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Left_Angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field HuiZhuanTai_Right_Angle from tbm_unity_interface message
 *
 * @return [rad] HuiZhuanTai_Right_Angle
 */
static inline float mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Right_Angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field HuiZhuanTai_Angle from tbm_unity_interface message
 *
 * @return [rad] HuiZhuanTai_Angle
 */
static inline float mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field DaBi_SiGan_Angle from tbm_unity_interface message
 *
 * @return [rad] DaBi_SiGan_Angle
 */
static inline float mavlink_msg_tbm_unity_interface_get_DaBi_SiGan_Angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field DaBi_SiGan_Length from tbm_unity_interface message
 *
 * @return [mm] DaBi_SiGan_Length
 */
static inline float mavlink_msg_tbm_unity_interface_get_DaBi_SiGan_Length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field Dianji_Angle_HZT from tbm_unity_interface message
 *
 * @return [rad] Dianji_Angle_HZT
 */
static inline float mavlink_msg_tbm_unity_interface_get_Dianji_Angle_HZT(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field JieGeBuShenSuo_Length from tbm_unity_interface message
 *
 * @return [mm] JieGeBuShenSuo_Length
 */
static inline float mavlink_msg_tbm_unity_interface_get_JieGeBuShenSuo_Length(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field JieGeTou_Rot_Speed from tbm_unity_interface message
 *
 * @return [rad/s] JieGeTou_Rot_Speed
 */
static inline float mavlink_msg_tbm_unity_interface_get_JieGeTou_Rot_Speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field HouTuiCheng_Angle from tbm_unity_interface message
 *
 * @return [rad] HouTuiCheng_Angle
 */
static inline float mavlink_msg_tbm_unity_interface_get_HouTuiCheng_Angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field roll from tbm_unity_interface message
 *
 * @return  Attitude roll expressed as Euler angles, not recommended except for human-readable outputs
 */
static inline float mavlink_msg_tbm_unity_interface_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field pitch from tbm_unity_interface message
 *
 * @return  Attitude pitch expressed as Euler angles, not recommended except for human-readable outputs
 */
static inline float mavlink_msg_tbm_unity_interface_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field yaw from tbm_unity_interface message
 *
 * @return  Attitude yaw expressed as Euler angles, not recommended except for human-readable outputs
 */
static inline float mavlink_msg_tbm_unity_interface_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field lat from tbm_unity_interface message
 *
 * @return [deg] Latitude*1e7
 */
static inline float mavlink_msg_tbm_unity_interface_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field lon from tbm_unity_interface message
 *
 * @return [deg] Longitude*1e7
 */
static inline float mavlink_msg_tbm_unity_interface_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field alt from tbm_unity_interface message
 *
 * @return [m] Altitude
 */
static inline float mavlink_msg_tbm_unity_interface_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field vn from tbm_unity_interface message
 *
 * @return [m/s] True velocity in north direction in earth-fixed NED frame
 */
static inline float mavlink_msg_tbm_unity_interface_get_vn(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field ve from tbm_unity_interface message
 *
 * @return [m/s] True velocity in east direction in earth-fixed NED frame
 */
static inline float mavlink_msg_tbm_unity_interface_get_ve(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field vd from tbm_unity_interface message
 *
 * @return [m/s] True velocity in down direction in earth-fixed NED frame
 */
static inline float mavlink_msg_tbm_unity_interface_get_vd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field xgyro from tbm_unity_interface message
 *
 * @return [rad/s] Angular speed around X axis
 */
static inline float mavlink_msg_tbm_unity_interface_get_xgyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field ygyro from tbm_unity_interface message
 *
 * @return [rad/s] Angular speed around Y axis
 */
static inline float mavlink_msg_tbm_unity_interface_get_ygyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field zgyro from tbm_unity_interface message
 *
 * @return [rad/s] Angular speed around Z axis
 */
static inline float mavlink_msg_tbm_unity_interface_get_zgyro(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Decode a tbm_unity_interface message into a struct
 *
 * @param msg The message to decode
 * @param tbm_unity_interface C-struct to decode the message contents into
 */
static inline void mavlink_msg_tbm_unity_interface_decode(const mavlink_message_t* msg, mavlink_tbm_unity_interface_t* tbm_unity_interface)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    tbm_unity_interface->HuiZhuanTai_Left_Length = mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Left_Length(msg);
    tbm_unity_interface->HuiZhuanTai_Right_Length = mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Right_Length(msg);
    tbm_unity_interface->HuiZhuanTai_Left_Angle = mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Left_Angle(msg);
    tbm_unity_interface->HuiZhuanTai_Right_Angle = mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Right_Angle(msg);
    tbm_unity_interface->HuiZhuanTai_Angle = mavlink_msg_tbm_unity_interface_get_HuiZhuanTai_Angle(msg);
    tbm_unity_interface->DaBi_SiGan_Angle = mavlink_msg_tbm_unity_interface_get_DaBi_SiGan_Angle(msg);
    tbm_unity_interface->DaBi_SiGan_Length = mavlink_msg_tbm_unity_interface_get_DaBi_SiGan_Length(msg);
    tbm_unity_interface->Dianji_Angle_HZT = mavlink_msg_tbm_unity_interface_get_Dianji_Angle_HZT(msg);
    tbm_unity_interface->JieGeBuShenSuo_Length = mavlink_msg_tbm_unity_interface_get_JieGeBuShenSuo_Length(msg);
    tbm_unity_interface->JieGeTou_Rot_Speed = mavlink_msg_tbm_unity_interface_get_JieGeTou_Rot_Speed(msg);
    tbm_unity_interface->HouTuiCheng_Angle = mavlink_msg_tbm_unity_interface_get_HouTuiCheng_Angle(msg);
    tbm_unity_interface->roll = mavlink_msg_tbm_unity_interface_get_roll(msg);
    tbm_unity_interface->pitch = mavlink_msg_tbm_unity_interface_get_pitch(msg);
    tbm_unity_interface->yaw = mavlink_msg_tbm_unity_interface_get_yaw(msg);
    tbm_unity_interface->lat = mavlink_msg_tbm_unity_interface_get_lat(msg);
    tbm_unity_interface->lon = mavlink_msg_tbm_unity_interface_get_lon(msg);
    tbm_unity_interface->alt = mavlink_msg_tbm_unity_interface_get_alt(msg);
    tbm_unity_interface->vn = mavlink_msg_tbm_unity_interface_get_vn(msg);
    tbm_unity_interface->ve = mavlink_msg_tbm_unity_interface_get_ve(msg);
    tbm_unity_interface->vd = mavlink_msg_tbm_unity_interface_get_vd(msg);
    tbm_unity_interface->xgyro = mavlink_msg_tbm_unity_interface_get_xgyro(msg);
    tbm_unity_interface->ygyro = mavlink_msg_tbm_unity_interface_get_ygyro(msg);
    tbm_unity_interface->zgyro = mavlink_msg_tbm_unity_interface_get_zgyro(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN? msg->len : MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN;
        memset(tbm_unity_interface, 0, MAVLINK_MSG_ID_TBM_UNITY_INTERFACE_LEN);
    memcpy(tbm_unity_interface, _MAV_PAYLOAD(msg), len);
#endif
}
