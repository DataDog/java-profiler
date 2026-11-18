---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 00:06:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1794978125 23
1794978130 23
1794978135 23
1794978140 23
1794978145 23
1794978150 23
1794978155 23
1794978160 23
1794978165 23
1794978170 23
1794978175 23
1794978180 23
1794978185 23
1794978190 23
1794978195 23
1794978200 23
1794978205 32
1794978210 32
1794978215 32
1794978220 32
```
</details>

---

