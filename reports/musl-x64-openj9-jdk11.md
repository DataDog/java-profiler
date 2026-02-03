---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:55:44 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1770137444 26
1770137449 26
1770137454 26
1770137459 26
1770137464 30
1770137469 30
1770137474 30
1770137479 30
1770137484 30
1770137489 30
1770137494 30
1770137499 30
1770137504 30
1770137509 29
1770137514 29
1770137519 29
1770137524 29
1770137529 29
1770137534 29
1770137539 32
```
</details>

---

