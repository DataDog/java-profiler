---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 09:28:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 15 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 38-42 cores)</summary>

```
1786454471 42
1786454476 42
1786454481 38
1786454486 38
1786454491 38
1786454496 38
1786454501 38
1786454506 38
1786454511 42
1786454516 42
1786454521 42
1786454526 42
1786454532 42
1786454537 42
1786454542 42
1786454547 42
1786454552 42
1786454557 42
1786454562 42
1786454567 42
```
</details>

---

