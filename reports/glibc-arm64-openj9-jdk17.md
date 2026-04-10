---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-10 19:29:53 EDT

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 13 |
| Allocations | 160 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1775863503 64
1775863508 64
1775863513 64
1775863518 64
1775863523 64
1775863528 64
1775863533 64
1775863538 64
1775863543 64
1775863548 64
1775863553 64
1775863558 64
1775863563 64
1775863568 64
1775863573 64
1775863578 64
1775863583 64
1775863588 64
1775863593 64
1775863598 64
```
</details>

---

