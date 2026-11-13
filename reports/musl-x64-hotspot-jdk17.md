---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:24:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 62-96 cores)</summary>

```
1794593988 96
1794593993 96
1794593998 96
1794594003 96
1794594008 96
1794594013 96
1794594018 96
1794594023 96
1794594028 96
1794594033 79
1794594038 79
1794594043 62
1794594048 62
1794594053 62
1794594058 62
1794594063 62
1794594068 62
1794594073 62
1794594078 62
1794594083 62
```
</details>

---

