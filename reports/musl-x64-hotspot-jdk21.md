---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:30:44 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 63-77 cores)</summary>

```
1795011946 77
1795011951 77
1795011956 77
1795011961 77
1795011966 77
1795011971 77
1795011976 68
1795011981 68
1795011986 68
1795011991 68
1795011996 63
1795012001 63
1795012006 63
1795012011 67
1795012016 67
1795012021 67
1795012026 67
1795012031 67
1795012037 67
1795012042 67
```
</details>

---

