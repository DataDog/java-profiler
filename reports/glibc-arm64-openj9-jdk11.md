---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1023 |
| Sample Rate | 17.05/sec |
| Health Score | 1066% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793288617 48
1793288622 48
1793288627 48
1793288632 48
1793288637 48
1793288642 48
1793288647 48
1793288652 48
1793288657 48
1793288662 48
1793288667 48
1793288672 48
1793288677 48
1793288682 48
1793288687 48
1793288692 48
1793288697 48
1793288702 48
1793288707 48
1793288712 48
```
</details>

---

