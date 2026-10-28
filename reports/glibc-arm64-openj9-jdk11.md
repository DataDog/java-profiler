---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:01:13 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793184672 43
1793184677 43
1793184682 43
1793184687 43
1793184692 43
1793184697 43
1793184702 43
1793184707 43
1793184712 43
1793184717 43
1793184722 43
1793184727 43
1793184732 43
1793184737 43
1793184742 43
1793184747 48
1793184752 48
1793184757 48
1793184762 48
1793184767 48
```
</details>

---

