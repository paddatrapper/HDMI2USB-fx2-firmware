/*
 * Copyright (C) 2017 Kyle Robbertze
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>

#include "date.h"
#include "descriptors_strings.h"

#include <ch9.h>
#include <ch9-extra.h>

#include <cdc.h>
#include <cdc-extra.h>

#ifndef DESCRIPTORS_H_
#define DESCRIPTORS_H_

struct usb_section {
	struct usb_config_descriptor config;
	/* ;;;;;;;;;;;;;;;;;;;;;;;;;; CDC ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; */
	struct usb_cdc {
		struct usb_interface_assoc_descriptor assoc_interface;

		struct usb_cdc_interface1 {
			struct usb_interface_descriptor interface;
			/* Header Functional Descriptor */
			struct usb_cdc_header_desc header;
			/* Union Functional Descriptor */
			struct usb_cdc_union_desc union_;
			/* CM Functional Descriptor */
			struct usb_cdc_call_mgmt_descriptor cm;
			/* ACM Functional Descriptor */
			struct usb_cdc_acm_descriptor acm;
			/* EP1 Descriptor */
			struct usb_endpoint_descriptor endpoints[1];
		} interface1;

		struct usb_cdc_interface2 {
			/* Virtual COM Port Data Interface Descriptor */
			struct usb_interface_descriptor interface;
			/* EP2OUT Descriptor + EP4 Descriptor */
			struct usb_endpoint_descriptor endpoints[2];
		} interface2;
	} cdc;
};

struct usb_descriptors {
	struct usb_device_descriptor device;
	struct usb_section highspeed;
	struct usb_qualifier_descriptor qualifier;
	WORD fullspeed;
	struct usb_descriptors_strings strings;
};

__xdata __at(DSCR_AREA) struct usb_descriptors descriptors;

__code __at(DSCR_AREA+offsetof(struct usb_descriptors, device)) WORD dev_dscr;
__code __at(DSCR_AREA+offsetof(struct usb_descriptors, qualifier)) WORD dev_qual_dscr;
__code __at(DSCR_AREA+offsetof(struct usb_descriptors, highspeed)) WORD highspd_dscr;
__code __at(DSCR_AREA+offsetof(struct usb_descriptors, fullspeed)) WORD fullspd_dscr;
__code __at(DSCR_AREA+offsetof(struct usb_descriptors, strings)) WORD dev_strings;

#endif // DESCRIPTORS_H_
