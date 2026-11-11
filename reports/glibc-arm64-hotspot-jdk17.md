---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:36:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794407489 43
1794407494 43
1794407499 43
1794407504 43
1794407509 43
1794407514 43
1794407519 43
1794407524 43
1794407529 43
1794407534 43
1794407539 43
1794407544 48
1794407549 48
1794407554 48
1794407559 48
1794407564 48
1794407569 48
1794407574 48
1794407579 48
1794407584 48
```
</details>

---

