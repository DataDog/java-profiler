---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 11 |
| Allocations | 125 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1777064271 49
1777064276 49
1777064281 49
1777064286 49
1777064291 49
1777064296 49
1777064301 49
1777064306 49
1777064311 49
1777064316 49
1777064321 49
1777064326 49
1777064331 54
1777064336 54
1777064341 54
1777064346 54
1777064351 54
1777064356 54
1777064361 54
1777064366 54
```
</details>

---

