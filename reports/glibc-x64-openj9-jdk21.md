---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-24 14:25:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1787595621 49
1787595626 49
1787595631 49
1787595636 49
1787595641 49
1787595646 49
1787595651 49
1787595657 51
1787595662 51
1787595667 51
1787595672 51
1787595677 51
1787595682 51
1787595687 51
1787595692 51
1787595697 51
1787595702 51
1787595707 51
1787595712 51
1787595717 51
```
</details>

---

