---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 9 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 14 |
| Allocations | 91 |

<details>
<summary>CPU Timeline (4 unique values: 72-81 cores)</summary>

```
1777064256 72
1777064261 72
1777064266 72
1777064271 72
1777064276 72
1777064281 72
1777064286 72
1777064291 72
1777064296 72
1777064301 72
1777064306 72
1777064311 72
1777064316 72
1777064321 72
1777064326 72
1777064331 72
1777064336 77
1777064341 77
1777064346 81
1777064351 81
```
</details>

---

