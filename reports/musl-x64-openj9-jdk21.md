---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:38:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1795001638 71
1795001643 71
1795001648 71
1795001653 73
1795001658 73
1795001663 73
1795001668 73
1795001673 73
1795001678 73
1795001683 73
1795001689 73
1795001694 73
1795001699 73
1795001704 73
1795001709 73
1795001714 71
1795001719 71
1795001724 71
1795001729 71
1795001734 71
```
</details>

---

