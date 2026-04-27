---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 04:26:05 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1777277938 32
1777277943 32
1777277948 32
1777277953 32
1777277958 32
1777277963 32
1777277968 32
1777277973 32
1777277978 32
1777277983 32
1777277988 32
1777277993 32
1777277998 30
1777278003 30
1777278008 30
1777278013 30
1777278018 28
1777278023 28
1777278028 28
1777278033 28
```
</details>

---

