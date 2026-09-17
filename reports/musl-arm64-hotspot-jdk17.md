---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 05:57:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1789638775 46
1789638780 46
1789638785 43
1789638790 43
1789638795 43
1789638800 43
1789638805 43
1789638810 43
1789638815 43
1789638820 43
1789638825 43
1789638830 43
1789638836 43
1789638841 43
1789638846 43
1789638851 43
1789638856 41
1789638861 41
1789638866 41
1789638871 41
```
</details>

---

