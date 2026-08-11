---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 07:16:43 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 7 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1786446604 13
1786446609 18
1786446614 18
1786446619 18
1786446624 18
1786446629 18
1786446634 18
1786446639 18
1786446644 18
1786446649 18
1786446654 18
1786446659 18
1786446664 18
1786446669 18
1786446674 18
1786446679 18
1786446684 18
1786446689 18
1786446694 18
1786446699 18
```
</details>

---

