---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-31 06:41:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 285 |
| Sample Rate | 4.75/sec |
| Health Score | 297% |
| Threads | 15 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1788172515 64
1788172520 63
1788172525 63
1788172530 63
1788172535 63
1788172540 63
1788172545 63
1788172550 63
1788172555 64
1788172560 64
1788172565 64
1788172570 64
1788172575 64
1788172580 64
1788172585 64
1788172590 64
1788172596 64
1788172601 64
1788172606 64
1788172611 64
```
</details>

---

