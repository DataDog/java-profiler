---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:22:26 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 13 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (2 unique values: 30-50 cores)</summary>

```
1795198587 30
1795198592 30
1795198597 30
1795198602 30
1795198607 30
1795198612 30
1795198617 50
1795198622 50
1795198627 50
1795198632 50
1795198637 50
1795198642 50
1795198647 50
1795198652 50
1795198657 50
1795198662 50
1795198667 50
1795198672 50
1795198677 50
1795198682 50
```
</details>

---

