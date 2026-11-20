---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 13:22:28 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (7 unique values: 61-85 cores)</summary>

```
1795198581 85
1795198586 85
1795198591 85
1795198596 85
1795198601 85
1795198606 83
1795198611 83
1795198616 83
1795198621 83
1795198626 83
1795198631 83
1795198636 76
1795198641 76
1795198646 76
1795198651 71
1795198656 71
1795198661 68
1795198666 68
1795198671 63
1795198676 63
```
</details>

---

