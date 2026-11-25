---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:28:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 68-96 cores)</summary>

```
1795641800 96
1795641805 96
1795641810 96
1795641815 96
1795641820 96
1795641825 96
1795641830 70
1795641835 70
1795641840 70
1795641845 70
1795641850 70
1795641855 70
1795641860 70
1795641865 70
1795641870 70
1795641875 70
1795641880 70
1795641885 70
1795641890 70
1795641895 70
```
</details>

---

