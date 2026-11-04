---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 00:07:59 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1793768526 81
1793768531 81
1793768536 81
1793768541 81
1793768546 81
1793768551 81
1793768556 81
1793768561 81
1793768566 81
1793768571 81
1793768576 81
1793768581 81
1793768586 81
1793768591 81
1793768596 81
1793768601 79
1793768606 79
1793768611 79
1793768616 79
1793768621 79
```
</details>

---

