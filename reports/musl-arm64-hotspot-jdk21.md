---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:36:29 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 9 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794407484 48
1794407489 48
1794407494 48
1794407499 48
1794407504 48
1794407509 48
1794407514 48
1794407519 48
1794407524 48
1794407529 48
1794407534 48
1794407539 43
1794407544 43
1794407549 43
1794407554 43
1794407559 43
1794407564 43
1794407569 43
1794407574 43
1794407579 48
```
</details>

---

