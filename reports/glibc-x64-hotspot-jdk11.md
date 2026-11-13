---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 19:03:47 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 65-74 cores)</summary>

```
1794527959 74
1794527964 74
1794527969 74
1794527974 74
1794527979 74
1794527984 74
1794527989 74
1794527995 74
1794528000 74
1794528005 74
1794528010 69
1794528015 69
1794528020 69
1794528025 69
1794528030 65
1794528035 65
1794528040 65
1794528045 65
1794528050 65
1794528055 65
```
</details>

---

