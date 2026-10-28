---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:01:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1793184696 61
1793184701 63
1793184706 63
1793184711 61
1793184716 61
1793184721 61
1793184726 61
1793184731 61
1793184736 61
1793184741 61
1793184747 61
1793184752 61
1793184757 61
1793184762 61
1793184767 61
1793184772 61
1793184777 61
1793184782 61
1793184787 61
1793184792 61
```
</details>

---

