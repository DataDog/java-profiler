---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:31:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 22-63 cores)</summary>

```
1790767665 22
1790767670 22
1790767675 22
1790767680 22
1790767685 61
1790767690 61
1790767695 61
1790767700 61
1790767705 61
1790767710 61
1790767715 61
1790767720 61
1790767725 61
1790767730 61
1790767735 61
1790767740 61
1790767745 61
1790767750 61
1790767755 61
1790767760 61
```
</details>

---

