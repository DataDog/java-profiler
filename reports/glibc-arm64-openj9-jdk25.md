---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-03 00:59:23 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 12 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (4 unique values: 8-18 cores)</summary>

```
1791003294 18
1791003299 18
1791003304 18
1791003309 8
1791003314 8
1791003319 8
1791003324 8
1791003329 8
1791003334 8
1791003339 8
1791003344 8
1791003349 8
1791003354 8
1791003359 13
1791003364 13
1791003369 13
1791003374 13
1791003379 18
1791003384 18
1791003389 16
```
</details>

---

