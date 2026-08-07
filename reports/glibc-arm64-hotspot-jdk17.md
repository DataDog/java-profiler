---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 16:29:10 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 11 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (4 unique values: 17-29 cores)</summary>

```
1786134301 29
1786134306 29
1786134311 19
1786134316 19
1786134321 19
1786134326 19
1786134331 19
1786134336 19
1786134341 19
1786134346 19
1786134351 19
1786134356 19
1786134361 19
1786134366 19
1786134371 29
1786134376 29
1786134382 19
1786134387 19
1786134392 19
1786134397 19
```
</details>

---

