---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:29:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (5 unique values: 52-76 cores)</summary>

```
1790238296 73
1790238301 71
1790238306 71
1790238311 71
1790238316 71
1790238321 71
1790238326 71
1790238331 71
1790238336 71
1790238341 71
1790238346 71
1790238351 71
1790238356 53
1790238361 53
1790238366 53
1790238371 53
1790238376 53
1790238381 53
1790238386 53
1790238391 53
```
</details>

---

