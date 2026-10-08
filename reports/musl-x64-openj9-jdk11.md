---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 09:20:16 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 10 |
| Allocations | 561 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1791465225 60
1791465230 60
1791465235 62
1791465240 62
1791465245 62
1791465250 62
1791465255 62
1791465260 62
1791465265 62
1791465270 64
1791465275 64
1791465280 64
1791465285 64
1791465290 64
1791465296 64
1791465301 64
1791465306 64
1791465311 64
1791465316 64
1791465321 64
```
</details>

---

