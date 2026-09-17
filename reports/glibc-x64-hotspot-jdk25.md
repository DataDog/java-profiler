---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 15:35:22 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 10 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 40-79 cores)</summary>

```
1789673384 75
1789673389 75
1789673394 75
1789673399 75
1789673404 58
1789673409 58
1789673414 58
1789673419 79
1789673424 79
1789673429 79
1789673434 79
1789673439 59
1789673444 59
1789673449 40
1789673454 40
1789673459 40
1789673464 40
1789673469 40
1789673474 40
1789673479 40
```
</details>

---

