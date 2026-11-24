---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-24 11:29:58 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 61-85 cores)</summary>

```
1795537494 83
1795537499 83
1795537504 83
1795537509 83
1795537514 85
1795537519 85
1795537524 85
1795537529 85
1795537534 64
1795537539 64
1795537544 64
1795537549 64
1795537554 64
1795537559 64
1795537564 61
1795537569 61
1795537574 61
1795537579 61
1795537584 61
1795537589 70
```
</details>

---

