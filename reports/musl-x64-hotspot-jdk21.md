---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-08-10 01:04:39 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 96-96 cores)</summary>

```
1786337961 96
1786337966 96
1786337971 96
1786337976 96
1786337981 96
1786337986 96
1786337991 96
1786337996 96
1786338001 96
1786338006 96
1786338011 96
1786338016 96
1786338021 96
1786338026 96
1786338031 96
1786338036 96
1786338041 96
1786338046 96
1786338051 96
1786338056 96
```
</details>

---

