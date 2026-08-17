---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 16:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 14 |
| Allocations | 187 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786999827 64
1786999832 64
1786999837 64
1786999842 64
1786999847 64
1786999852 64
1786999857 64
1786999862 64
1786999867 64
1786999872 64
1786999877 64
1786999882 64
1786999887 64
1786999892 64
1786999897 64
1786999902 64
1786999907 64
1786999912 64
1786999917 64
1786999922 64
```
</details>

---

