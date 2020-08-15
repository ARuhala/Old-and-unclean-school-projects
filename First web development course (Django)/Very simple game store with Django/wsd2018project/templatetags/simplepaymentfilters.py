from django import template
from hashlib import md5

#register = template.Library()
#
#@register.filter(name=prchecksum)
#def payementrequestchecksum(value):
#    checksumstr="pid={}&sid={}&amount={}&token={}".format("payid", "lentavayksisarvisgebardioletettu", value, "d818eab5c8f17682e64614ad086ebbfe")
#
#    # checksumstr is the string concatenated above
#    m = md5(checksumstr.encode("ascii"))
#    checksum = m.hexdigest()
#    # checksum is the value that should be used in the payment request
#
#    return checksum

