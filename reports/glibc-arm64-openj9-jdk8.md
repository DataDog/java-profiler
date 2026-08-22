---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-22 08:14:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787400634 48
1787400639 48
1787400644 48
1787400649 48
1787400654 48
1787400659 48
1787400664 48
1787400669 48
1787400674 48
1787400679 48
1787400684 48
1787400689 48
1787400694 48
1787400699 48
1787400704 48
1787400709 48
1787400714 48
1787400719 48
1787400724 48
1787400729 43
```
</details>

---

