---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-06 16:43:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794001091 61
1794001096 61
1794001101 61
1794001106 61
1794001111 61
1794001116 61
1794001121 61
1794001126 61
1794001131 61
1794001136 61
1794001141 59
1794001146 59
1794001151 59
1794001156 59
1794001161 59
1794001166 59
1794001171 59
1794001176 59
1794001181 59
1794001186 59
```
</details>

---

