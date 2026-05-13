---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-13 11:08:22 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778684531 59
1778684536 59
1778684541 59
1778684546 59
1778684551 59
1778684556 59
1778684561 59
1778684566 59
1778684571 59
1778684576 59
1778684581 59
1778684586 59
1778684591 59
1778684596 59
1778684601 64
1778684606 64
1778684611 64
1778684616 64
1778684621 64
1778684626 64
```
</details>

---

