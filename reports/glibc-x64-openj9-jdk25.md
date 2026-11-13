---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 12:24:44 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1794590386 85
1794590391 85
1794590397 85
1794590402 85
1794590407 85
1794590412 85
1794590417 85
1794590422 85
1794590427 85
1794590432 85
1794590437 83
1794590442 83
1794590447 83
1794590452 83
1794590457 83
1794590462 87
1794590467 87
1794590472 87
1794590477 87
1794590482 87
```
</details>

---

