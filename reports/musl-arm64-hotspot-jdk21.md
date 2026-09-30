---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 12:30:29 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 11 |
| Allocations | 193 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790785527 43
1790785532 43
1790785537 43
1790785543 43
1790785548 43
1790785553 43
1790785558 43
1790785563 43
1790785568 48
1790785573 48
1790785578 48
1790785583 48
1790785588 48
1790785593 48
1790785598 48
1790785603 48
1790785608 48
1790785613 48
1790785618 48
1790785623 48
```
</details>

---

