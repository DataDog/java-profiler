---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:34:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1794580038 79
1794580043 79
1794580048 79
1794580053 79
1794580058 79
1794580063 79
1794580068 79
1794580073 79
1794580078 77
1794580083 77
1794580088 77
1794580094 77
1794580099 77
1794580104 77
1794580109 77
1794580114 77
1794580119 77
1794580124 77
1794580129 77
1794580134 77
```
</details>

---

