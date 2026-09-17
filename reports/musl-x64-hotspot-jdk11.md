---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 16:57:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 989 |
| Sample Rate | 16.48/sec |
| Health Score | 1030% |
| Threads | 12 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 67-68 cores)</summary>

```
1789677738 68
1789677743 68
1789677748 68
1789677753 68
1789677758 68
1789677763 68
1789677768 68
1789677773 68
1789677778 68
1789677783 68
1789677788 67
1789677793 67
1789677798 67
1789677803 67
1789677808 67
1789677813 67
1789677818 67
1789677823 67
1789677828 67
1789677833 67
```
</details>

---

