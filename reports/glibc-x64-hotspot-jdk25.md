---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-11 14:07:59 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 11 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 44-53 cores)</summary>

```
1773252166 44
1773252171 53
1773252176 53
1773252181 53
1773252186 53
1773252191 53
1773252196 53
1773252201 53
1773252206 53
1773252211 53
1773252216 53
1773252221 53
1773252226 53
1773252231 53
1773252236 50
1773252241 50
1773252246 50
1773252251 50
1773252256 50
1773252261 50
```
</details>

---

