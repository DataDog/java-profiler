---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-04 05:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 15 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1791107013 29
1791107018 29
1791107023 29
1791107028 29
1791107033 34
1791107038 34
1791107043 34
1791107048 34
1791107053 34
1791107058 34
1791107063 34
1791107068 34
1791107073 34
1791107078 34
1791107083 34
1791107088 34
1791107093 34
1791107099 34
1791107104 34
1791107109 34
```
</details>

---

