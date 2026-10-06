---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 05:52:39 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 11 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 11 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 43-51 cores)</summary>

```
1791279948 51
1791279953 51
1791279958 51
1791279963 51
1791279968 51
1791279973 51
1791279978 51
1791279983 51
1791279988 51
1791279993 51
1791279998 43
1791280003 43
1791280008 43
1791280013 43
1791280018 43
1791280023 43
1791280028 43
1791280033 43
1791280038 43
1791280043 43
```
</details>

---

