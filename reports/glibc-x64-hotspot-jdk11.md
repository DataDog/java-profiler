---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-29 07:49:57 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 18.37/sec |
| Health Score | 1148% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 22.10/sec |
| Health Score | 1381% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 69-77 cores)</summary>

```
1769690668 69
1769690673 69
1769690678 69
1769690683 69
1769690688 69
1769690693 69
1769690698 69
1769690703 69
1769690708 73
1769690713 73
1769690718 73
1769690723 77
1769690728 77
1769690733 77
1769690738 77
1769690743 74
1769690748 74
1769690753 74
1769690758 74
1769690763 74
```
</details>

---

