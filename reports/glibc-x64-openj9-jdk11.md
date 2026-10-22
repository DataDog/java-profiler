---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 13:06:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792688473 32
1792688478 32
1792688483 32
1792688488 32
1792688493 32
1792688498 32
1792688503 32
1792688508 32
1792688513 32
1792688518 32
1792688523 32
1792688528 32
1792688533 32
1792688538 32
1792688543 32
1792688548 32
1792688553 32
1792688558 32
1792688563 32
1792688568 32
```
</details>

---

