---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-26 09:56:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (6 unique values: 68-85 cores)</summary>

```
1779803422 82
1779803427 82
1779803432 82
1779803437 82
1779803442 85
1779803447 85
1779803452 85
1779803457 73
1779803462 73
1779803467 73
1779803472 73
1779803477 73
1779803482 73
1779803487 69
1779803492 69
1779803497 69
1779803502 69
1779803507 68
1779803512 68
1779803517 70
```
</details>

---

