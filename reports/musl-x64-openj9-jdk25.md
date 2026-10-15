---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 09:57:56 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 18-29 cores)</summary>

```
1792072283 18
1792072288 18
1792072293 26
1792072298 26
1792072303 29
1792072308 29
1792072313 29
1792072318 29
1792072323 29
1792072328 29
1792072333 29
1792072338 29
1792072343 29
1792072348 29
1792072353 29
1792072358 29
1792072363 29
1792072368 29
1792072373 20
1792072378 20
```
</details>

---

