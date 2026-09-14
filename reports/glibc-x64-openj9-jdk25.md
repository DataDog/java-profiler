---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-14 12:04:47 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (7 unique values: 78-96 cores)</summary>

```
1789401540 90
1789401545 86
1789401550 86
1789401555 80
1789401560 80
1789401565 80
1789401570 78
1789401575 78
1789401580 80
1789401585 80
1789401590 80
1789401595 80
1789401600 84
1789401605 84
1789401610 84
1789401615 84
1789401620 84
1789401625 90
1789401630 90
1789401635 90
```
</details>

---

