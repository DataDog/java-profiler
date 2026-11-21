---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-21 00:02:12 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 8 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 13-33 cores)</summary>

```
1795237115 33
1795237120 33
1795237125 13
1795237130 13
1795237135 13
1795237140 13
1795237145 13
1795237150 13
1795237155 13
1795237160 13
1795237165 13
1795237170 13
1795237175 13
1795237180 13
1795237185 13
1795237190 13
1795237195 13
1795237200 13
1795237205 13
1795237210 13
```
</details>

---

