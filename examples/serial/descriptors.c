
#include "descriptors.h"

#define ARRAY_SIZE(x) \
	(sizeof(x)/sizeof((x)[0]))

__code __at(DSCR_AREA) struct usb_descriptors code_descriptors = {
	.device = {
		.bLength		= USB_DT_DEVICE_SIZE,
		.bDescriptorType	= USB_DT_DEVICE,
		.bcdUSB			= USB_BCD_V20,
		.bDeviceClass 		= USB_CLASS_MISC,
		.bDeviceSubClass	= UVC_SC_VIDEOSTREAMING,
		.bDeviceProtocol	= 0x01, // ?? Protocol code?
		.bMaxPacketSize0	= 64,
		.idVendor		= VID,
		.idProduct		= PID,
		.bcdDevice		= DID,
		.iManufacturer		= USB_STRING_INDEX(0),
		.iProduct		= USB_STRING_INDEX(1),
		.iSerialNumber		= USB_STRING_INDEX(2),
		.bNumConfigurations	= 1
	},
	.highspeed = {
		.config = {
			.bLength		= USB_DT_CONFIG_SIZE,
			.bDescriptorType	= USB_DT_CONFIG,
			.wTotalLength		= sizeof(descriptors.highspeed),
			.bNumInterfaces		= 4,
			.bConfigurationValue	= 1,
			.iConfiguration		= USB_STRING_INDEX_NONE,
			.bmAttributes		= USB_CONFIG_ATT_ONE,
			.bMaxPower		= 250, // FIXME: ???
		},
		.cdc = {
			/* Interface association descriptor */
			.assoc_interface = {
				.bLength		= sizeof(struct usb_interface_assoc_descriptor),
				.bDescriptorType	= USB_DT_INTERFACE_ASSOCIATION,
				.bFirstInterface	= 2,
				.bInterfaceCount	= 1,
				.bFunctionClass		= USB_CLASS_COMM,
				.bFunctionSubClass	= USB_CLASS_PER_INTERFACE,
				.bFunctionProtocol	= USB_CDC_ACM_PROTO_AT_V25TER,
				.iFunction		= USB_STRING_INDEX(0),
			},
			.interface1 = {
				.interface = {
					.bLength		= USB_DT_INTERFACE_SIZE,
					.bDescriptorType	= USB_DT_INTERFACE,
					.bInterfaceNumber	= 2,
					.bAlternateSetting	= 0,
					.bNumEndpoints		= 1,
					.bInterfaceClass	= USB_CLASS_COMM,
					.bInterfaceSubClass	= USB_CDC_SUBCLASS_ACM,
					.bInterfaceProtocol	= USB_CDC_ACM_PROTO_AT_V25TER,
					.iInterface		= USB_STRING_INDEX(0),
				},
				.header = {
					.bLength		= sizeof(struct usb_cdc_header_desc),
					.bDescriptorType	= USB_DT_CS_INTERFACE,
					.bDescriptorSubType	= USB_CDC_HEADER_TYPE,
					.bcdCDC			= CDC_BCD_V11,
				},
				.union_ = {
					.bLength		= sizeof(struct usb_cdc_union_desc),
					.bDescriptorType	= USB_DT_CS_INTERFACE,
					.bDescriptorSubType	= USB_CDC_UNION_TYPE,
					.bMasterInterface0	= 2,
					.bSlaveInterface0	= 3,			
				},
				.cm = {
					.bLength		= sizeof(struct usb_cdc_call_mgmt_descriptor),
					.bDescriptorType	= USB_DT_CS_INTERFACE,
					.bDescriptorSubType	= USB_CDC_CALL_MANAGEMENT_TYPE,
					.bmCapabilities		= 0,
					.bDataInterface		= 3,
				},
				.acm = {
					.bLength		= sizeof(struct usb_cdc_acm_descriptor),
					.bDescriptorType	= USB_DT_CS_INTERFACE,
					.bDescriptorSubType	= USB_CDC_ACM_TYPE,
					.bmCapabilities		= USB_CDC_CAP_LINE,
				},
				.endpoints = {
					{
						.bLength		= USB_DT_ENDPOINT_SIZE,
						.bDescriptorType 	= USB_DT_ENDPOINT,
						.bEndpointAddress	= USB_ENDPOINT_NUMBER(0x1) | USB_DIR_IN,
						.bmAttributes		= USB_ENDPOINT_XFER_INT,
						.wMaxPacketSize		= 16,
						.bInterval		= 1,
					}
				},
			},
			.interface2 = {
				.interface = {
					.bLength		= USB_DT_INTERFACE_SIZE,
					.bDescriptorType	= USB_DT_INTERFACE,
					.bInterfaceNumber	= 3,
					.bAlternateSetting	= 0,
					.bNumEndpoints		= 2,
					.bInterfaceClass	= USB_CLASS_CDC_DATA,
					.bInterfaceSubClass	= 0x0, // FIXME?
					.bInterfaceProtocol	= USB_CDC_PROTO_NONE,
					.iInterface		= USB_STRING_INDEX(0),
				},
				.endpoints = {
					{
						.bLength		= USB_DT_ENDPOINT_SIZE,
						.bDescriptorType 	= USB_DT_ENDPOINT,
						.bEndpointAddress	= USB_ENDPOINT_NUMBER(0x2) | USB_DIR_OUT,
						.bmAttributes		= USB_ENDPOINT_XFER_BULK,
						.wMaxPacketSize		= 512,
						.bInterval		= 0,
					}, {
						.bLength		= USB_DT_ENDPOINT_SIZE,
						.bDescriptorType 	= USB_DT_ENDPOINT,
						.bEndpointAddress	= USB_ENDPOINT_NUMBER(0x4) | USB_DIR_IN,
						.bmAttributes		= USB_ENDPOINT_XFER_BULK,
						.wMaxPacketSize		= 512,
						.bInterval		= 0,
					},
				},
			},
		},
	},
	.qualifier = {
		.bLength = USB_DT_DEVICE_QUALIFIER_SIZE,
		.bDescriptorType = USB_DT_DEVICE_QUALIFIER,
		.bcdUSB = USB_BCD_V20,
		.bDeviceClass = USB_CLASS_MISC,
		.bDeviceSubClass = USB_CLASS_COMM,
		.bDeviceProtocol = USB_CDC_ACM_PROTO_AT_V25TER,
		.bMaxPacketSize0 = 64,
		.bNumConfigurations = 1,
		.bRESERVED = 0,
	},
	.fullspeed = 0x0,
#include "descriptors_strings.inc"
};
