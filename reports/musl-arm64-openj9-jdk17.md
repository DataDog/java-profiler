---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:36:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794396695 41
1794396700 43
1794396705 43
1794396710 43
1794396715 43
1794396720 43
1794396725 43
1794396730 48
1794396735 48
1794396740 43
1794396745 43
1794396750 43
1794396755 43
1794396760 43
1794396765 43
1794396770 43
1794396775 43
1794396780 43
1794396785 43
1794396790 43
```
</details>

---

