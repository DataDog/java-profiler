---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 05:20:29 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 27-40 cores)</summary>

```
1786526227 27
1786526232 27
1786526237 27
1786526242 27
1786526247 27
1786526252 27
1786526257 27
1786526262 27
1786526267 27
1786526272 27
1786526277 27
1786526282 27
1786526287 27
1786526292 27
1786526297 40
1786526302 40
1786526307 30
1786526312 30
1786526317 30
1786526322 30
```
</details>

---

