---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:26:45 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 860 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 47-64 cores)</summary>

```
1794406985 47
1794406990 47
1794406995 47
1794407000 47
1794407005 47
1794407010 47
1794407015 47
1794407020 47
1794407025 47
1794407030 47
1794407035 47
1794407040 47
1794407045 47
1794407050 47
1794407055 47
1794407060 47
1794407065 47
1794407070 47
1794407075 64
1794407080 64
```
</details>

---

