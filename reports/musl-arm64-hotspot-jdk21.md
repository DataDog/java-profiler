---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 06:25:17 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 15 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1794914426 64
1794914431 64
1794914436 59
1794914442 59
1794914447 59
1794914452 59
1794914457 59
1794914462 59
1794914467 59
1794914472 59
1794914477 64
1794914482 64
1794914487 64
1794914492 64
1794914497 64
1794914502 64
1794914507 64
1794914512 64
1794914517 64
1794914522 64
```
</details>

---

