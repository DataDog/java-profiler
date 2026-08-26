---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 07:12:54 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 10 |
| Allocations | 180 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 141 |
| Sample Rate | 2.35/sec |
| Health Score | 147% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787742542 48
1787742547 48
1787742552 48
1787742557 43
1787742562 43
1787742567 43
1787742572 43
1787742577 43
1787742582 43
1787742587 43
1787742592 43
1787742597 43
1787742602 43
1787742607 48
1787742612 48
1787742617 48
1787742622 48
1787742627 48
1787742632 48
1787742637 48
```
</details>

---

