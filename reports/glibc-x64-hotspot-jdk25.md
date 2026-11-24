---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:59:17 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 66-71 cores)</summary>

```
1795532017 71
1795532022 71
1795532027 71
1795532032 71
1795532037 71
1795532042 66
1795532047 66
1795532052 66
1795532057 66
1795532062 66
1795532067 66
1795532072 66
1795532077 66
1795532082 66
1795532087 68
1795532092 68
1795532097 71
1795532102 71
1795532107 71
1795532112 69
```
</details>

---

