---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-01-29 12:19:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 8 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 4 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769706830 24
1769706835 24
1769706840 24
1769706845 24
1769706850 24
1769706855 24
1769706860 24
1769706865 24
1769706870 24
1769706875 24
1769706880 24
1769706885 24
1769706890 24
1769706895 24
1769706900 24
1769706905 24
1769706910 24
1769706915 24
1769706920 24
1769706925 24
```
</details>

---

