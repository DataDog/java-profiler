---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 12:53:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 73-82 cores)</summary>

```
1778172494 73
1778172499 73
1778172504 80
1778172509 80
1778172514 80
1778172519 80
1778172524 80
1778172529 82
1778172534 82
1778172539 82
1778172544 82
1778172549 73
1778172554 73
1778172559 73
1778172564 73
1778172569 73
1778172574 73
1778172579 77
1778172584 77
1778172589 77
```
</details>

---

