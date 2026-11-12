---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 08:26:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 235 |
| Sample Rate | 3.92/sec |
| Health Score | 245% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 67-75 cores)</summary>

```
1794489694 75
1794489699 75
1794489704 75
1794489709 75
1794489714 75
1794489719 75
1794489724 75
1794489729 75
1794489734 67
1794489739 67
1794489744 67
1794489749 67
1794489754 67
1794489759 67
1794489764 67
1794489769 67
1794489774 67
1794489779 67
1794489784 67
1794489789 67
```
</details>

---

