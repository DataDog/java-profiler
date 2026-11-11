---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:27:14 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (5 unique values: 47-67 cores)</summary>

```
1794428526 54
1794428531 54
1794428536 54
1794428541 54
1794428546 54
1794428551 54
1794428556 54
1794428561 54
1794428566 54
1794428571 54
1794428576 56
1794428581 56
1794428586 47
1794428591 47
1794428596 47
1794428601 47
1794428606 67
1794428611 67
1794428616 67
1794428621 67
```
</details>

---

