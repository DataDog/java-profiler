---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 01:06:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 23-48 cores)</summary>

```
1792472540 23
1792472545 23
1792472550 23
1792472555 23
1792472560 23
1792472565 23
1792472570 23
1792472575 23
1792472580 23
1792472585 43
1792472590 43
1792472595 43
1792472600 43
1792472605 43
1792472610 43
1792472615 43
1792472620 43
1792472625 43
1792472630 48
1792472635 48
```
</details>

---

