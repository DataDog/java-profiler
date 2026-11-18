---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 03:32:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 22-44 cores)</summary>

```
1794990506 23
1794990511 23
1794990516 23
1794990521 23
1794990526 23
1794990531 23
1794990536 23
1794990541 23
1794990546 23
1794990551 23
1794990556 23
1794990561 44
1794990566 44
1794990571 44
1794990576 22
1794990581 22
1794990586 22
1794990591 22
1794990596 22
1794990601 22
```
</details>

---

