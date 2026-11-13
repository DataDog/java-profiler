---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:26:20 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 10 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 62-73 cores)</summary>

```
1794572469 73
1794572474 65
1794572479 65
1794572484 65
1794572489 65
1794572494 65
1794572499 65
1794572504 62
1794572509 62
1794572514 62
1794572519 62
1794572524 62
1794572529 62
1794572534 62
1794572539 62
1794572544 62
1794572549 62
1794572554 62
1794572559 62
1794572564 62
```
</details>

---

