---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-06 14:42:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 63-87 cores)</summary>

```
1778092676 63
1778092681 63
1778092686 63
1778092691 63
1778092696 63
1778092701 63
1778092706 63
1778092711 63
1778092716 63
1778092721 63
1778092726 63
1778092731 63
1778092736 63
1778092741 63
1778092746 68
1778092751 68
1778092756 68
1778092761 87
1778092766 87
1778092771 87
```
</details>

---

