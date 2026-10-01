---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 00:59:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 805 |
| Sample Rate | 13.42/sec |
| Health Score | 839% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 49-64 cores)</summary>

```
1790830498 54
1790830503 49
1790830508 49
1790830513 49
1790830518 49
1790830523 49
1790830528 49
1790830533 49
1790830538 49
1790830543 49
1790830548 49
1790830553 49
1790830558 49
1790830563 49
1790830568 49
1790830573 54
1790830578 54
1790830583 59
1790830588 59
1790830593 59
```
</details>

---

