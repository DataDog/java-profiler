---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 07:24:20 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 20-24 cores)</summary>

```
1776252019 21
1776252024 21
1776252029 21
1776252034 21
1776252039 21
1776252044 21
1776252049 21
1776252054 21
1776252059 23
1776252064 23
1776252069 23
1776252074 23
1776252079 23
1776252084 23
1776252089 23
1776252094 23
1776252099 24
1776252104 24
1776252109 23
1776252114 23
```
</details>

---

