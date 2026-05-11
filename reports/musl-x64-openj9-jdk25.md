---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-11 10:05:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 70-76 cores)</summary>

```
1778507975 72
1778507980 72
1778507985 72
1778507990 72
1778507995 72
1778508000 72
1778508005 72
1778508010 70
1778508015 70
1778508020 70
1778508025 70
1778508030 72
1778508035 72
1778508040 72
1778508045 71
1778508050 71
1778508055 71
1778508060 71
1778508065 71
1778508070 71
```
</details>

---

