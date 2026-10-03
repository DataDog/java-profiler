---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-03 00:59:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 14 |
| Allocations | 104 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791003299 48
1791003304 48
1791003309 48
1791003314 48
1791003319 48
1791003324 48
1791003329 48
1791003334 48
1791003339 43
1791003344 43
1791003349 43
1791003354 43
1791003359 43
1791003364 43
1791003369 43
1791003374 43
1791003379 43
1791003384 43
1791003389 43
1791003394 43
```
</details>

---

