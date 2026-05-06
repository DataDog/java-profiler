---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:08:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 76-81 cores)</summary>

```
1778090404 77
1778090409 76
1778090414 76
1778090419 79
1778090424 79
1778090429 79
1778090434 79
1778090439 79
1778090444 79
1778090449 79
1778090454 79
1778090459 79
1778090464 79
1778090469 81
1778090474 81
1778090479 81
1778090484 81
1778090489 81
1778090494 81
1778090499 81
```
</details>

---

