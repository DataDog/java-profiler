---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 09:32:08 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 19-20 cores)</summary>

```
1787232421 20
1787232426 20
1787232431 20
1787232436 20
1787232442 20
1787232447 20
1787232452 20
1787232457 20
1787232462 20
1787232467 20
1787232472 20
1787232477 19
1787232482 19
1787232487 19
1787232492 19
1787232497 19
1787232502 19
1787232507 19
1787232512 19
1787232517 19
```
</details>

---

