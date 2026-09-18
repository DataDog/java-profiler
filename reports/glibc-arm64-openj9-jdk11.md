---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:29:03 EDT

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
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1789737710 48
1789737715 48
1789737720 48
1789737725 48
1789737730 48
1789737735 48
1789737740 48
1789737745 48
1789737750 48
1789737755 48
1789737760 48
1789737765 48
1789737770 48
1789737775 48
1789737780 48
1789737785 48
1789737790 48
1789737795 48
1789737800 37
1789737805 37
```
</details>

---

