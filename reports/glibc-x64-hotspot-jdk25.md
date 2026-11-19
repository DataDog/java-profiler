---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 06:06:30 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 68-77 cores)</summary>

```
1795085959 70
1795085964 70
1795085969 68
1795085974 68
1795085979 68
1795085984 68
1795085989 68
1795085994 68
1795085999 68
1795086004 68
1795086009 68
1795086014 68
1795086019 68
1795086024 68
1795086029 68
1795086034 68
1795086039 68
1795086044 68
1795086049 68
1795086054 77
```
</details>

---

