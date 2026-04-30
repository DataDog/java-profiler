---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:12:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 66-70 cores)</summary>

```
1777558103 66
1777558108 66
1777558113 66
1777558118 66
1777558123 66
1777558128 66
1777558133 66
1777558138 66
1777558143 66
1777558148 70
1777558153 70
1777558158 70
1777558163 70
1777558168 70
1777558173 70
1777558178 70
1777558183 70
1777558188 70
1777558193 70
1777558198 70
```
</details>

---

