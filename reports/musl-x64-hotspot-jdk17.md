---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 13:09:37 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 66-88 cores)</summary>

```
1791306163 66
1791306168 66
1791306173 86
1791306178 86
1791306183 86
1791306188 86
1791306193 86
1791306198 86
1791306203 88
1791306208 88
1791306213 88
1791306218 88
1791306223 88
1791306228 88
1791306233 88
1791306238 88
1791306243 88
1791306248 88
1791306253 88
1791306258 88
```
</details>

---

