---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 21:04:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 69-81 cores)</summary>

```
1794707940 69
1794707945 69
1794707950 69
1794707955 69
1794707960 69
1794707965 69
1794707970 69
1794707975 69
1794707980 69
1794707985 69
1794707990 75
1794707995 75
1794708000 81
1794708005 81
1794708010 81
1794708015 81
1794708020 81
1794708025 81
1794708030 79
1794708035 79
```
</details>

---

