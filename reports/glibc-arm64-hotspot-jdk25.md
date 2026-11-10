---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:56:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 360 |
| Sample Rate | 6.00/sec |
| Health Score | 375% |
| Threads | 9 |
| Allocations | 444 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1794325930 46
1794325935 48
1794325940 48
1794325945 46
1794325950 46
1794325955 46
1794325960 46
1794325965 46
1794325970 46
1794325975 46
1794325980 46
1794325985 46
1794325990 46
1794325995 46
1794326000 46
1794326005 46
1794326010 44
1794326015 44
1794326020 44
1794326025 44
```
</details>

---

