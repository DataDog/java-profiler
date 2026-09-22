---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 13:14:50 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 50-96 cores)</summary>

```
1790097029 50
1790097034 50
1790097039 50
1790097044 50
1790097049 50
1790097054 50
1790097059 50
1790097064 60
1790097069 60
1790097074 60
1790097079 60
1790097084 60
1790097089 60
1790097094 60
1790097100 60
1790097105 60
1790097110 60
1790097115 60
1790097120 60
1790097125 96
```
</details>

---

