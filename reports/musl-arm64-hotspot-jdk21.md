---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 11:43:20 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 11 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 11 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795624625 42
1795624630 42
1795624635 42
1795624640 42
1795624645 42
1795624650 47
1795624655 47
1795624660 47
1795624665 47
1795624670 47
1795624675 47
1795624680 47
1795624685 47
1795624690 47
1795624695 47
1795624700 47
1795624705 47
1795624710 47
1795624715 47
1795624720 47
```
</details>

---

