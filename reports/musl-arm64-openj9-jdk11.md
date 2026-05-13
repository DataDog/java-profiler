---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-13 11:08:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 13 |
| Allocations | 144 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1778684536 52
1778684541 52
1778684546 52
1778684551 52
1778684556 52
1778684561 52
1778684566 52
1778684571 52
1778684576 52
1778684581 52
1778684586 52
1778684591 52
1778684596 52
1778684601 52
1778684606 52
1778684611 52
1778684616 52
1778684621 47
1778684626 47
1778684631 47
```
</details>

---

