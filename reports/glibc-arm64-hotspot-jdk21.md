---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:32:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 13 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789737720 42
1789737725 42
1789737730 42
1789737735 42
1789737740 42
1789737745 42
1789737750 42
1789737755 42
1789737760 42
1789737765 42
1789737770 42
1789737775 42
1789737780 42
1789737785 42
1789737790 42
1789737795 42
1789737800 42
1789737805 42
1789737810 42
1789737815 42
```
</details>

---

