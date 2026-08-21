---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 10:08:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1787321043 44
1787321048 44
1787321053 44
1787321058 44
1787321063 44
1787321068 64
1787321073 64
1787321078 64
1787321083 64
1787321088 44
1787321093 44
1787321098 44
1787321103 44
1787321108 44
1787321113 44
1787321118 44
1787321123 44
1787321128 44
1787321133 44
1787321138 44
```
</details>

---

