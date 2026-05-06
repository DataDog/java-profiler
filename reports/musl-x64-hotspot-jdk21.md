---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-06 14:10:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 45-52 cores)</summary>

```
1778090735 45
1778090740 45
1778090745 45
1778090750 45
1778090755 45
1778090760 45
1778090766 45
1778090771 45
1778090776 45
1778090781 47
1778090786 47
1778090791 47
1778090796 47
1778090801 47
1778090806 47
1778090811 47
1778090816 47
1778090821 47
1778090826 47
1778090831 52
```
</details>

---

