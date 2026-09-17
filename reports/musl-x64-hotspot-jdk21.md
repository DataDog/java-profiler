---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 05:57:24 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 981 |
| Sample Rate | 16.35/sec |
| Health Score | 1022% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 58-81 cores)</summary>

```
1789638790 81
1789638795 81
1789638800 81
1789638805 81
1789638810 81
1789638815 81
1789638820 81
1789638825 81
1789638830 81
1789638835 81
1789638840 81
1789638845 81
1789638851 81
1789638856 81
1789638861 81
1789638866 81
1789638871 81
1789638876 81
1789638881 81
1789638886 58
```
</details>

---

