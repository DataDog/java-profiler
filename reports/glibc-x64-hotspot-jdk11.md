---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 15:03:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 66-75 cores)</summary>

```
1776970681 75
1776970686 71
1776970691 71
1776970696 71
1776970701 71
1776970706 71
1776970711 67
1776970716 67
1776970721 66
1776970726 66
1776970731 66
1776970736 66
1776970741 66
1776970746 66
1776970751 66
1776970756 66
1776970761 66
1776970766 66
1776970771 66
1776970776 66
```
</details>

---

