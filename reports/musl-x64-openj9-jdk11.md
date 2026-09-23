---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:09:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1790168633 32
1790168638 22
1790168643 22
1790168648 22
1790168653 22
1790168659 22
1790168664 22
1790168669 22
1790168674 22
1790168679 22
1790168684 22
1790168689 22
1790168694 22
1790168699 22
1790168704 22
1790168709 22
1790168714 22
1790168719 22
1790168724 22
1790168729 22
```
</details>

---

