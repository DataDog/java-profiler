---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 14:06:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (4 unique values: 15-30 cores)</summary>

```
1790272874 15
1790272879 20
1790272884 20
1790272889 20
1790272894 20
1790272899 20
1790272904 20
1790272909 20
1790272914 20
1790272919 20
1790272924 20
1790272929 21
1790272934 21
1790272939 21
1790272944 21
1790272949 21
1790272954 21
1790272959 21
1790272964 21
1790272969 21
```
</details>

---

