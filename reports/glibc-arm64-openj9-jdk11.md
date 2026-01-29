---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ❌ FAIL

**Date:** 2026-01-29 12:43:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 21 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769708369 24
1769708374 24
1769708379 24
1769708384 24
1769708389 24
1769708394 24
1769708399 24
1769708404 24
1769708409 24
1769708414 24
1769708419 24
1769708424 24
1769708429 24
1769708434 24
1769708439 24
1769708444 24
1769708449 24
1769708454 24
1769708459 24
1769708464 24
```
</details>

---

