---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 02:27:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 958 |
| Sample Rate | 15.97/sec |
| Health Score | 998% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794986644 29
1794986649 29
1794986654 29
1794986659 29
1794986664 29
1794986669 29
1794986674 29
1794986679 29
1794986684 29
1794986689 29
1794986694 29
1794986699 29
1794986704 29
1794986709 29
1794986714 34
1794986719 34
1794986724 34
1794986729 34
1794986734 34
1794986739 34
```
</details>

---

