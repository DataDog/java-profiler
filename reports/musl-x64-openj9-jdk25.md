---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 10:36:06 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 86-91 cores)</summary>

```
1793370655 86
1793370660 86
1793370666 86
1793370671 86
1793370676 86
1793370681 86
1793370686 90
1793370691 90
1793370696 90
1793370701 90
1793370706 90
1793370711 90
1793370716 90
1793370721 90
1793370726 90
1793370731 90
1793370736 90
1793370741 90
1793370746 90
1793370751 91
```
</details>

---

