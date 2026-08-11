---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 20:17:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 30-36 cores)</summary>

```
1786407154 32
1786407159 32
1786407164 32
1786407169 32
1786407174 32
1786407179 32
1786407184 32
1786407189 32
1786407194 32
1786407199 30
1786407204 30
1786407209 30
1786407214 30
1786407219 30
1786407224 30
1786407229 30
1786407234 30
1786407239 30
1786407244 30
1786407249 30
```
</details>

---

