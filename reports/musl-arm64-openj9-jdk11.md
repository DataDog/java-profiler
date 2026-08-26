---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 09:45:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 11 |
| Allocations | 196 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 13 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787751591 59
1787751596 59
1787751601 59
1787751606 59
1787751611 59
1787751616 59
1787751621 59
1787751626 59
1787751631 59
1787751636 59
1787751641 64
1787751646 64
1787751651 59
1787751656 59
1787751661 59
1787751666 59
1787751671 59
1787751676 59
1787751681 59
1787751686 59
```
</details>

---

