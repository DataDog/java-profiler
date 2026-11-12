---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 11:49:15 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 77-91 cores)</summary>

```
1794501705 77
1794501710 91
1794501715 91
1794501720 88
1794501725 88
1794501730 88
1794501735 88
1794501740 88
1794501745 80
1794501750 80
1794501755 80
1794501760 80
1794501765 80
1794501770 80
1794501775 80
1794501780 80
1794501785 80
1794501790 80
1794501795 82
1794501800 82
```
</details>

---

