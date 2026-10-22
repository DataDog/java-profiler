---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 09:44:16 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 82-87 cores)</summary>

```
1792676384 87
1792676389 87
1792676394 87
1792676399 87
1792676404 87
1792676409 85
1792676414 85
1792676419 85
1792676424 85
1792676429 85
1792676434 82
1792676439 82
1792676444 82
1792676449 82
1792676454 82
1792676459 82
1792676464 82
1792676469 82
1792676474 84
1792676479 84
```
</details>

---

