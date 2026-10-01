---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 00:59:51 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 63-66 cores)</summary>

```
1790830460 63
1790830465 63
1790830470 63
1790830475 63
1790830480 63
1790830485 63
1790830490 63
1790830495 63
1790830500 63
1790830505 63
1790830510 63
1790830515 66
1790830520 66
1790830525 66
1790830530 66
1790830535 66
1790830540 66
1790830545 66
1790830550 66
1790830555 66
```
</details>

---

