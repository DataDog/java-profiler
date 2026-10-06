---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 05:52:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 11 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 37-42 cores)</summary>

```
1791279953 37
1791279958 37
1791279963 37
1791279968 37
1791279973 37
1791279978 37
1791279983 42
1791279988 42
1791279993 42
1791279998 42
1791280003 37
1791280008 37
1791280013 37
1791280018 37
1791280023 37
1791280028 37
1791280033 37
1791280038 37
1791280043 37
1791280048 37
```
</details>

---

