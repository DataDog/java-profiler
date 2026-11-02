---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 14:28:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 18-30 cores)</summary>

```
1793647516 18
1793647521 18
1793647526 18
1793647531 18
1793647536 18
1793647541 18
1793647546 18
1793647551 18
1793647556 18
1793647561 18
1793647566 18
1793647571 18
1793647576 18
1793647581 18
1793647586 18
1793647591 18
1793647596 18
1793647601 18
1793647606 18
1793647611 18
```
</details>

---

