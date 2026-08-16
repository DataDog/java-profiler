---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-16 11:16:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1786893154 64
1786893159 64
1786893164 64
1786893169 64
1786893174 64
1786893179 64
1786893184 64
1786893189 64
1786893194 64
1786893199 64
1786893204 64
1786893209 64
1786893214 64
1786893219 64
1786893224 64
1786893229 64
1786893234 64
1786893239 64
1786893244 64
1786893249 64
```
</details>

---

