---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-30 05:30:08 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (2 unique values: 70-79 cores)</summary>

```
1777541153 70
1777541158 70
1777541163 70
1777541168 79
1777541173 79
1777541178 79
1777541183 79
1777541188 79
1777541193 79
1777541198 79
1777541203 79
1777541208 79
1777541213 79
1777541218 79
1777541223 79
1777541228 79
1777541233 79
1777541238 79
1777541243 79
1777541248 79
```
</details>

---

