---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:39:38 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (5 unique values: 41-91 cores)</summary>

```
1791531246 59
1791531251 59
1791531256 61
1791531261 61
1791531266 91
1791531271 91
1791531276 91
1791531281 91
1791531286 91
1791531291 91
1791531296 91
1791531301 58
1791531306 58
1791531311 58
1791531316 58
1791531321 58
1791531327 58
1791531332 58
1791531337 58
1791531342 41
```
</details>

---

