---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-24 05:38:29 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 8 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 91-96 cores)</summary>

```
1792834349 91
1792834354 91
1792834359 91
1792834364 91
1792834369 91
1792834374 91
1792834379 96
1792834384 96
1792834389 96
1792834394 96
1792834399 96
1792834404 96
1792834409 96
1792834414 96
1792834419 96
1792834424 96
1792834429 96
1792834434 96
1792834439 96
1792834444 96
```
</details>

---

