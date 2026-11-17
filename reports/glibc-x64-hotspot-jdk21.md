---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:02:49 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1794927389 89
1794927394 89
1794927399 89
1794927404 89
1794927409 89
1794927414 89
1794927419 89
1794927424 91
1794927429 91
1794927434 91
1794927439 91
1794927444 91
1794927449 91
1794927454 91
1794927459 91
1794927464 93
1794927469 93
1794927474 93
1794927479 93
1794927484 93
```
</details>

---

