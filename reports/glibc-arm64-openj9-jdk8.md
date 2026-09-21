---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:40:55 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789997716 43
1789997721 43
1789997726 43
1789997731 43
1789997736 43
1789997741 43
1789997746 43
1789997751 43
1789997756 43
1789997761 43
1789997766 43
1789997771 43
1789997776 43
1789997781 43
1789997786 43
1789997791 43
1789997796 43
1789997801 43
1789997806 43
1789997811 48
```
</details>

---

