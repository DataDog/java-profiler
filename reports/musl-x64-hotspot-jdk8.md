---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-08 13:30:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 75-89 cores)</summary>

```
1775668989 89
1775668994 89
1775668999 89
1775669004 85
1775669009 85
1775669014 85
1775669019 80
1775669024 80
1775669029 80
1775669034 78
1775669039 78
1775669044 80
1775669049 80
1775669054 80
1775669059 75
1775669064 75
1775669069 75
1775669074 75
1775669079 75
1775669084 75
```
</details>

---

