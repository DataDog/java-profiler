---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 14:46:35 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 12 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1793126509 28
1793126514 28
1793126519 28
1793126524 28
1793126529 28
1793126535 28
1793126540 28
1793126545 28
1793126550 28
1793126555 28
1793126560 48
1793126565 48
1793126570 48
1793126575 48
1793126580 48
1793126585 48
1793126590 48
1793126595 48
1793126600 48
1793126605 48
```
</details>

---

