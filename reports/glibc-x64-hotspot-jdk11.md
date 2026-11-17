---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 21-26 cores)</summary>

```
1794944984 21
1794944989 21
1794944994 21
1794944999 21
1794945004 21
1794945009 21
1794945014 21
1794945019 24
1794945024 24
1794945029 24
1794945034 24
1794945039 24
1794945044 24
1794945049 26
1794945054 26
1794945059 24
1794945064 24
1794945069 24
1794945074 24
1794945079 24
```
</details>

---

