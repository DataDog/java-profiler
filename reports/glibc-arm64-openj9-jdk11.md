---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-28 15:54:53 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 6 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777405587 64
1777405592 64
1777405597 64
1777405602 64
1777405607 64
1777405612 64
1777405617 64
1777405622 64
1777405627 64
1777405632 64
1777405637 64
1777405642 64
1777405647 64
1777405652 64
1777405657 64
1777405662 64
1777405667 64
1777405672 64
1777405677 64
1777405682 64
```
</details>

---

