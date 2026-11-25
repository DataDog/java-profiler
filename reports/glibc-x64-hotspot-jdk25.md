---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:28:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 45-53 cores)</summary>

```
1795641785 45
1795641790 45
1795641795 45
1795641800 45
1795641805 45
1795641810 45
1795641815 53
1795641820 53
1795641825 53
1795641830 53
1795641835 53
1795641840 53
1795641845 53
1795641850 53
1795641855 53
1795641860 53
1795641865 53
1795641870 53
1795641875 53
1795641880 53
```
</details>

---

