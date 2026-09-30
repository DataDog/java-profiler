---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 10:44:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 55-58 cores)</summary>

```
1790779143 55
1790779148 55
1790779153 55
1790779158 55
1790779163 58
1790779168 58
1790779173 58
1790779178 58
1790779183 58
1790779188 58
1790779193 58
1790779198 58
1790779203 58
1790779208 58
1790779213 58
1790779218 58
1790779223 58
1790779228 58
1790779233 58
1790779238 58
```
</details>

---

