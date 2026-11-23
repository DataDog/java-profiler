---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 05:22:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 29-34 cores)</summary>

```
1795429053 29
1795429058 29
1795429063 29
1795429068 29
1795429073 29
1795429078 29
1795429083 29
1795429088 29
1795429093 29
1795429098 29
1795429103 29
1795429108 29
1795429113 33
1795429118 33
1795429123 33
1795429128 31
1795429133 31
1795429138 34
1795429143 34
1795429148 34
```
</details>

---

