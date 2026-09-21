---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-20 21:23:21 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 12 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1789953515 62
1789953520 62
1789953525 62
1789953530 62
1789953535 62
1789953540 62
1789953545 62
1789953550 62
1789953555 62
1789953560 62
1789953565 62
1789953570 62
1789953575 64
1789953580 64
1789953585 64
1789953590 64
1789953595 64
1789953600 64
1789953605 59
1789953610 59
```
</details>

---

