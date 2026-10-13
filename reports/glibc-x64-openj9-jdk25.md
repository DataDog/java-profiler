---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 07:44:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 17-37 cores)</summary>

```
1791891551 37
1791891556 37
1791891561 37
1791891566 37
1791891571 37
1791891576 37
1791891581 37
1791891586 37
1791891591 17
1791891596 17
1791891601 17
1791891606 17
1791891611 17
1791891616 17
1791891621 17
1791891626 17
1791891631 17
1791891636 17
1791891641 17
1791891646 17
```
</details>

---

