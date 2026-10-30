---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:56:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1793357491 36
1793357496 36
1793357501 36
1793357506 36
1793357511 36
1793357516 36
1793357521 36
1793357526 36
1793357531 36
1793357536 36
1793357541 36
1793357546 36
1793357551 36
1793357556 36
1793357561 36
1793357566 36
1793357571 36
1793357576 36
1793357581 36
1793357586 36
```
</details>

---

