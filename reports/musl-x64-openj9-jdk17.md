---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:01:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 993 |
| Sample Rate | 16.55/sec |
| Health Score | 1034% |
| Threads | 12 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1795618512 53
1795618517 53
1795618522 53
1795618527 53
1795618532 53
1795618537 53
1795618542 53
1795618547 53
1795618552 53
1795618557 53
1795618562 53
1795618567 53
1795618572 53
1795618577 51
1795618582 51
1795618587 51
1795618592 51
1795618597 51
1795618602 51
1795618607 51
```
</details>

---

