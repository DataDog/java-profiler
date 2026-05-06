---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:42:36 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 81-91 cores)</summary>

```
1778092674 82
1778092679 82
1778092684 82
1778092689 82
1778092694 82
1778092699 82
1778092704 82
1778092709 82
1778092714 82
1778092719 82
1778092724 81
1778092729 81
1778092734 81
1778092739 86
1778092744 86
1778092749 86
1778092754 86
1778092759 86
1778092764 86
1778092769 91
```
</details>

---

