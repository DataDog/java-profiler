---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:51:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 12 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 11 |
| Allocations | 183 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789731971 48
1789731976 48
1789731981 48
1789731986 48
1789731991 48
1789731996 48
1789732001 48
1789732006 48
1789732011 48
1789732016 48
1789732021 48
1789732026 48
1789732031 48
1789732036 48
1789732041 48
1789732046 43
1789732051 43
1789732056 43
1789732061 43
1789732066 43
```
</details>

---

