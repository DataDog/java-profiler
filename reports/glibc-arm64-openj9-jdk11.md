---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:22:14 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (1 unique values: 39-39 cores)</summary>

```
1793722631 39
1793722636 39
1793722641 39
1793722646 39
1793722651 39
1793722656 39
1793722661 39
1793722666 39
1793722671 39
1793722676 39
1793722681 39
1793722686 39
1793722691 39
1793722696 39
1793722701 39
1793722706 39
1793722711 39
1793722716 39
1793722721 39
1793722726 39
```
</details>

---

