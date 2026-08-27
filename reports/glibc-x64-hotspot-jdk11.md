---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-27 09:40:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787837736 66
1787837741 66
1787837746 64
1787837751 64
1787837756 64
1787837761 64
1787837766 64
1787837771 64
1787837776 64
1787837781 64
1787837786 66
1787837791 66
1787837796 66
1787837801 66
1787837806 66
1787837811 66
1787837816 66
1787837821 66
1787837826 66
1787837831 66
```
</details>

---

