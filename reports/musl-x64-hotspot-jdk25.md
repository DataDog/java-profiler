---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 14:13:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 85-93 cores)</summary>

```
1793297242 85
1793297247 90
1793297252 90
1793297257 90
1793297262 90
1793297267 90
1793297272 90
1793297277 93
1793297282 93
1793297287 93
1793297292 93
1793297297 93
1793297302 93
1793297307 93
1793297312 90
1793297317 90
1793297322 88
1793297327 88
1793297332 88
1793297337 88
```
</details>

---

