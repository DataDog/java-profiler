---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:52:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 50-60 cores)</summary>

```
1790243071 50
1790243076 50
1790243081 50
1790243086 50
1790243091 50
1790243096 50
1790243101 50
1790243106 50
1790243111 50
1790243116 50
1790243121 50
1790243126 50
1790243131 50
1790243136 50
1790243141 50
1790243146 50
1790243151 60
1790243156 60
1790243161 60
1790243166 60
```
</details>

---

