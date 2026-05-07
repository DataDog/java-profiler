---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 13:44:41 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1047 |
| Sample Rate | 17.45/sec |
| Health Score | 1091% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1778175610 43
1778175615 43
1778175620 43
1778175625 43
1778175630 43
1778175635 43
1778175640 43
1778175645 43
1778175650 43
1778175655 43
1778175660 43
1778175665 43
1778175670 43
1778175675 43
1778175680 43
1778175685 48
1778175690 48
1778175695 46
1778175700 46
1778175705 46
```
</details>

---

