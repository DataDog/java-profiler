---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:39:49 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795451624 59
1795451629 59
1795451634 59
1795451639 59
1795451644 59
1795451649 59
1795451654 64
1795451659 64
1795451664 64
1795451669 64
1795451674 64
1795451679 64
1795451684 64
1795451689 64
1795451694 64
1795451699 64
1795451704 64
1795451709 64
1795451714 64
1795451719 64
```
</details>

---

