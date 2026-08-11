---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 07:16:41 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 87 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1786446609 51
1786446614 51
1786446619 51
1786446624 51
1786446629 51
1786446634 51
1786446639 51
1786446644 51
1786446649 51
1786446654 51
1786446659 51
1786446664 51
1786446669 39
1786446674 39
1786446679 39
1786446684 39
1786446689 39
1786446694 39
1786446699 39
1786446704 39
```
</details>

---

