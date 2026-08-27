---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-27 09:40:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787837746 48
1787837751 48
1787837756 48
1787837761 48
1787837766 48
1787837771 48
1787837776 48
1787837781 48
1787837786 48
1787837791 48
1787837796 48
1787837801 40
1787837806 40
1787837811 40
1787837816 40
1787837821 40
1787837826 40
1787837831 40
1787837836 40
1787837841 40
```
</details>

---

