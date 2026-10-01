---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 06:31:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 48-58 cores)</summary>

```
1790850368 58
1790850373 58
1790850378 58
1790850383 50
1790850388 50
1790850394 50
1790850399 50
1790850404 50
1790850409 50
1790850414 50
1790850419 50
1790850424 50
1790850429 50
1790850434 50
1790850439 48
1790850444 48
1790850449 48
1790850454 48
1790850459 48
1790850464 48
```
</details>

---

