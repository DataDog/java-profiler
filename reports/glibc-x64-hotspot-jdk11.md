---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 06:31:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 65-70 cores)</summary>

```
1790850353 70
1790850358 70
1790850363 70
1790850368 70
1790850373 70
1790850378 70
1790850383 70
1790850388 70
1790850393 70
1790850398 70
1790850403 67
1790850408 67
1790850413 67
1790850418 67
1790850423 67
1790850428 67
1790850433 67
1790850438 67
1790850444 67
1790850449 67
```
</details>

---

