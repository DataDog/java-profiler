---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-26 09:56:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1779803529 64
1779803534 64
1779803539 64
1779803544 64
1779803549 64
1779803554 64
1779803559 64
1779803564 64
1779803569 64
1779803574 64
1779803579 64
1779803584 64
1779803589 64
1779803594 64
1779803599 64
1779803604 64
1779803609 64
1779803614 64
1779803619 64
1779803624 64
```
</details>

---

