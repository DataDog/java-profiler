---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 15:07:40 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (6 unique values: 76-88 cores)</summary>

```
1787684437 80
1787684442 80
1787684447 78
1787684452 78
1787684457 78
1787684462 78
1787684467 78
1787684472 78
1787684477 76
1787684482 76
1787684487 84
1787684492 84
1787684497 84
1787684502 86
1787684507 86
1787684512 86
1787684517 88
1787684522 88
1787684527 88
1787684532 88
```
</details>

---

