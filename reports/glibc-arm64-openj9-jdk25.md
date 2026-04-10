---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-10 19:29:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1775863482 64
1775863488 64
1775863493 64
1775863498 64
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
```
</details>

---

