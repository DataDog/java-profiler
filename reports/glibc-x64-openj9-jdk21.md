---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:15:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 52-88 cores)</summary>

```
1794352235 54
1794352240 52
1794352245 52
1794352250 52
1794352255 52
1794352260 74
1794352265 74
1794352270 74
1794352275 81
1794352280 81
1794352285 81
1794352290 81
1794352295 81
1794352300 81
1794352305 81
1794352310 81
1794352315 81
1794352320 81
1794352325 81
1794352330 88
```
</details>

---

