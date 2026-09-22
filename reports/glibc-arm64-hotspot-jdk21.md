---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 15:04:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 11 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790103638 38
1790103643 38
1790103648 38
1790103653 38
1790103658 38
1790103663 38
1790103668 43
1790103673 43
1790103678 43
1790103683 43
1790103688 43
1790103693 43
1790103698 43
1790103703 43
1790103708 43
1790103713 43
1790103718 48
1790103723 48
1790103728 48
1790103733 48
```
</details>

---

