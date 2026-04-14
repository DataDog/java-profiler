---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-14 11:42:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 71-78 cores)</summary>

```
1776180920 74
1776180925 76
1776180930 76
1776180935 76
1776180940 76
1776180945 76
1776180950 76
1776180955 76
1776180960 78
1776180965 78
1776180970 78
1776180975 78
1776180980 78
1776180985 78
1776180990 76
1776180995 76
1776181000 76
1776181005 76
1776181010 76
1776181015 74
```
</details>

---

