---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 11:43:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 434 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1788363452 96
1788363457 96
1788363462 96
1788363467 96
1788363472 96
1788363477 96
1788363482 96
1788363487 96
1788363492 88
1788363497 88
1788363502 88
1788363507 88
1788363512 88
1788363517 88
1788363522 88
1788363527 88
1788363532 88
1788363537 88
1788363542 88
1788363547 88
```
</details>

---

