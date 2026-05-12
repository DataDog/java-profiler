---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 03:34:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 12 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1778571048 51
1778571053 51
1778571058 51
1778571063 51
1778571068 51
1778571073 51
1778571078 51
1778571083 51
1778571088 51
1778571093 51
1778571098 51
1778571103 51
1778571108 51
1778571113 51
1778571118 51
1778571123 51
1778571128 51
1778571133 51
1778571138 46
1778571143 46
```
</details>

---

