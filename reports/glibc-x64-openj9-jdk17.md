---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:07:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1794394989 30
1794394994 30
1794394999 30
1794395004 32
1794395009 32
1794395014 32
1794395019 32
1794395024 32
1794395029 32
1794395034 32
1794395039 32
1794395044 32
1794395049 32
1794395054 32
1794395059 32
1794395064 32
1794395069 32
1794395074 32
1794395079 32
1794395084 10
```
</details>

---

