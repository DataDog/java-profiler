---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 19:49:08 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 63-96 cores)</summary>

```
1794789927 75
1794789932 75
1794789937 75
1794789942 75
1794789947 75
1794789952 75
1794789957 75
1794789962 75
1794789967 75
1794789972 96
1794789977 96
1794789982 96
1794789987 96
1794789992 96
1794789997 96
1794790002 96
1794790007 96
1794790012 96
1794790017 96
1794790022 96
```
</details>

---

