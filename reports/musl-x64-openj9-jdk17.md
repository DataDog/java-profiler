---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 19:51:08 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 47-80 cores)</summary>

```
1794703601 47
1794703606 47
1794703611 47
1794703616 47
1794703621 80
1794703626 80
1794703631 80
1794703636 80
1794703641 80
1794703646 80
1794703651 80
1794703656 80
1794703661 80
1794703666 80
1794703671 80
1794703676 80
1794703681 80
1794703686 80
1794703691 80
1794703696 80
```
</details>

---

