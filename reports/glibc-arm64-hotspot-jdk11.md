---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 04:45:05 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790325658 43
1790325663 43
1790325668 38
1790325673 38
1790325678 38
1790325683 38
1790325688 38
1790325693 38
1790325698 38
1790325703 38
1790325708 43
1790325713 43
1790325718 43
1790325723 43
1790325728 43
1790325733 43
1790325738 43
1790325743 48
1790325748 48
1790325753 43
```
</details>

---

