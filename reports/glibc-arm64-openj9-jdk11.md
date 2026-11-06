---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 21:05:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793930498 48
1793930503 48
1793930508 48
1793930513 48
1793930518 48
1793930523 48
1793930528 48
1793930533 48
1793930538 48
1793930543 48
1793930548 48
1793930553 48
1793930558 48
1793930563 48
1793930568 48
1793930573 48
1793930578 48
1793930583 48
1793930588 48
1793930593 48
```
</details>

---

