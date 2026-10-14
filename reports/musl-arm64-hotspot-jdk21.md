---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 10:47:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 20-25 cores)</summary>

```
1791988936 20
1791988941 20
1791988946 20
1791988951 20
1791988956 20
1791988961 20
1791988966 20
1791988971 20
1791988976 20
1791988981 20
1791988986 20
1791988991 20
1791988996 20
1791989001 20
1791989006 20
1791989011 20
1791989016 20
1791989021 20
1791989026 20
1791989031 25
```
</details>

---

