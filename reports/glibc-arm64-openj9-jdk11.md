---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-29 12:24:44 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777479482 64
1777479487 64
1777479492 64
1777479497 64
1777479502 64
1777479507 64
1777479512 64
1777479517 64
1777479522 64
1777479527 64
1777479532 64
1777479537 64
1777479542 64
1777479547 64
1777479552 64
1777479557 64
1777479562 64
1777479567 64
1777479572 64
1777479577 64
```
</details>

---

