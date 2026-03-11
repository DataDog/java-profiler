---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 10:47:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (5 unique values: 74-83 cores)</summary>

```
1773240218 76
1773240223 76
1773240228 76
1773240233 76
1773240238 76
1773240243 76
1773240248 74
1773240253 74
1773240258 79
1773240263 79
1773240268 79
1773240273 75
1773240278 75
1773240283 79
1773240288 79
1773240293 79
1773240298 79
1773240303 79
1773240308 79
1773240313 79
```
</details>

---

