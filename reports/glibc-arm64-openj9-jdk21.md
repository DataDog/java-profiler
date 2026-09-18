---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 15 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1789737715 64
1789737720 64
1789737725 64
1789737730 64
1789737735 64
1789737740 64
1789737745 64
1789737750 64
1789737755 64
1789737760 64
1789737765 64
1789737770 64
1789737775 64
1789737780 64
1789737785 50
1789737790 50
1789737795 50
1789737800 50
1789737805 50
1789737810 47
```
</details>

---

