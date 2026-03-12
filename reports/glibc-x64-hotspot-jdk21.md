---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-12 03:41:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 11 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 12 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 59-71 cores)</summary>

```
1773300990 64
1773300995 64
1773301000 64
1773301005 59
1773301010 59
1773301015 59
1773301020 59
1773301025 59
1773301030 59
1773301035 59
1773301040 59
1773301045 59
1773301050 59
1773301055 59
1773301060 59
1773301065 59
1773301070 59
1773301075 59
1773301080 59
1773301085 59
```
</details>

---

