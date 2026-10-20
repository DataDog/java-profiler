---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 12:29:06 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1091 |
| Sample Rate | 18.18/sec |
| Health Score | 1136% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1792513457 96
1792513462 96
1792513467 94
1792513472 94
1792513478 94
1792513483 92
1792513488 92
1792513493 92
1792513498 92
1792513503 92
1792513508 92
1792513513 92
1792513518 92
1792513523 92
1792513528 92
1792513533 92
1792513538 92
1792513543 90
1792513548 90
1792513553 90
```
</details>

---

