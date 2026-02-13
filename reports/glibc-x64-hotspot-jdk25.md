---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-13 03:09:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 10 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 867 |
| Sample Rate | 14.45/sec |
| Health Score | 903% |
| Threads | 13 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 62-76 cores)</summary>

```
1770969726 62
1770969731 62
1770969736 62
1770969741 64
1770969746 64
1770969751 64
1770969756 64
1770969761 76
1770969766 76
1770969771 76
1770969776 76
1770969781 76
1770969786 76
1770969791 76
1770969796 76
1770969801 76
1770969806 76
1770969811 76
1770969816 76
1770969821 76
```
</details>

---

