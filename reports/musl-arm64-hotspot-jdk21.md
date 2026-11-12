---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:45:29 EST

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 16 |
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
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 8-28 cores)</summary>

```
1794497507 8
1794497512 8
1794497517 8
1794497522 8
1794497527 8
1794497532 8
1794497537 8
1794497542 8
1794497547 8
1794497552 8
1794497557 8
1794497562 8
1794497568 8
1794497573 8
1794497578 8
1794497583 28
1794497588 28
1794497593 28
1794497598 28
1794497603 28
```
</details>

---

