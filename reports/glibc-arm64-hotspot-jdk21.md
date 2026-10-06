---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 14:26:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 11 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1791310965 41
1791310970 41
1791310975 41
1791310980 41
1791310985 41
1791310990 41
1791310995 46
1791311000 46
1791311005 51
1791311010 51
1791311015 51
1791311020 51
1791311025 51
1791311030 51
1791311035 51
1791311040 51
1791311045 51
1791311050 51
1791311055 51
1791311060 51
```
</details>

---

