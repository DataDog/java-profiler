---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 06:49:55 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 14 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778150762 64
1778150767 64
1778150772 64
1778150777 64
1778150782 64
1778150787 64
1778150792 59
1778150797 59
1778150802 59
1778150807 59
1778150812 59
1778150817 59
1778150822 59
1778150827 59
1778150832 59
1778150837 59
1778150842 59
1778150847 59
1778150852 59
1778150857 59
```
</details>

---

