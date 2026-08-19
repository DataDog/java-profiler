---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 11:07:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1787151684 74
1787151689 74
1787151694 74
1787151699 76
1787151704 76
1787151709 76
1787151714 74
1787151719 74
1787151724 74
1787151729 74
1787151734 74
1787151739 74
1787151744 74
1787151749 74
1787151754 74
1787151759 74
1787151764 74
1787151769 74
1787151774 76
1787151779 76
```
</details>

---

