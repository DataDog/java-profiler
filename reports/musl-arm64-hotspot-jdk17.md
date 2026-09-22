---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:47:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (4 unique values: 31-40 cores)</summary>

```
1790091853 36
1790091858 36
1790091863 36
1790091868 36
1790091873 36
1790091878 31
1790091883 31
1790091888 31
1790091893 35
1790091899 35
1790091904 35
1790091909 35
1790091914 35
1790091919 35
1790091924 40
1790091929 40
1790091934 40
1790091939 40
1790091944 40
1790091949 40
```
</details>

---

