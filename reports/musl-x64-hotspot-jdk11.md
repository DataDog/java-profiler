---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:22:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 919 |
| Sample Rate | 15.32/sec |
| Health Score | 957% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 56-59 cores)</summary>

```
1795429023 59
1795429028 59
1795429033 59
1795429038 59
1795429043 59
1795429048 59
1795429053 59
1795429058 59
1795429063 59
1795429068 59
1795429073 59
1795429078 56
1795429083 56
1795429088 56
1795429093 56
1795429098 56
1795429103 56
1795429108 56
1795429113 56
1795429118 56
```
</details>

---

