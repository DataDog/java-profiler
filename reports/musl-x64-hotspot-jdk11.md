---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 05:59:05 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 49-59 cores)</summary>

```
1794999170 59
1794999175 59
1794999180 59
1794999185 59
1794999190 59
1794999195 59
1794999200 49
1794999205 49
1794999210 49
1794999215 51
1794999220 51
1794999225 51
1794999230 51
1794999235 51
1794999240 51
1794999245 51
1794999250 51
1794999255 51
1794999260 51
1794999265 51
```
</details>

---

