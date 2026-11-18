---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 07:19:40 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (7 unique values: 71-89 cores)</summary>

```
1795004187 78
1795004192 78
1795004197 76
1795004202 76
1795004207 73
1795004212 73
1795004217 71
1795004222 71
1795004227 80
1795004232 80
1795004237 80
1795004242 84
1795004247 84
1795004252 84
1795004257 84
1795004262 84
1795004267 84
1795004272 84
1795004277 84
1795004282 84
```
</details>

---

