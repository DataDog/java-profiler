---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 09:38:17 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 34-39 cores)</summary>

```
1793367207 37
1793367212 37
1793367217 37
1793367222 37
1793367227 37
1793367232 37
1793367237 37
1793367242 37
1793367247 37
1793367252 37
1793367257 37
1793367262 39
1793367267 39
1793367272 39
1793367277 39
1793367282 39
1793367287 39
1793367292 39
1793367297 39
1793367302 39
```
</details>

---

