---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 11:49:14 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (4 unique values: 38-44 cores)</summary>

```
1794501725 43
1794501730 43
1794501735 43
1794501740 43
1794501745 43
1794501750 43
1794501755 44
1794501760 44
1794501765 44
1794501770 44
1794501775 44
1794501780 44
1794501785 44
1794501790 44
1794501795 44
1794501800 44
1794501805 44
1794501810 41
1794501815 41
1794501820 41
```
</details>

---

