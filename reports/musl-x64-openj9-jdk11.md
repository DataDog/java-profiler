---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:38:36 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 858 |
| Sample Rate | 14.30/sec |
| Health Score | 894% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1770125486 32
1770125491 32
1770125496 32
1770125501 32
1770125506 32
1770125511 32
1770125516 32
1770125521 32
1770125526 32
1770125532 32
1770125537 27
1770125542 27
1770125547 27
1770125552 27
1770125557 27
1770125562 27
1770125567 27
1770125572 27
1770125577 27
1770125582 27
```
</details>

---

