---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:31:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 11 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787232437 64
1787232442 64
1787232447 64
1787232452 64
1787232457 64
1787232462 64
1787232467 64
1787232472 64
1787232477 64
1787232482 64
1787232487 64
1787232492 64
1787232497 64
1787232502 64
1787232507 64
1787232512 64
1787232517 64
1787232522 64
1787232527 64
1787232532 64
```
</details>

---

