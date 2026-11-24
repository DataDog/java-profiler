---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:59:16 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 12 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 15 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 31-37 cores)</summary>

```
1795532043 37
1795532048 37
1795532053 37
1795532058 37
1795532063 37
1795532068 37
1795532073 37
1795532078 37
1795532083 37
1795532088 37
1795532093 37
1795532098 37
1795532103 37
1795532108 37
1795532113 37
1795532118 37
1795532123 37
1795532128 37
1795532133 37
1795532138 31
```
</details>

---

