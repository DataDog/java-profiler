---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 12:51:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 25-45 cores)</summary>

```
1793727941 45
1793727946 45
1793727951 45
1793727956 45
1793727961 45
1793727966 45
1793727971 45
1793727976 45
1793727981 45
1793727986 45
1793727991 45
1793727996 25
1793728001 25
1793728006 25
1793728011 25
1793728016 25
1793728021 25
1793728026 25
1793728031 25
1793728036 25
```
</details>

---

