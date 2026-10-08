---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 10:54:33 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 14 |
| Allocations | 193 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1791470981 48
1791470986 48
1791470991 48
1791470996 48
1791471001 48
1791471006 48
1791471011 48
1791471016 48
1791471021 48
1791471026 48
1791471031 48
1791471036 48
1791471041 48
1791471046 48
1791471051 48
1791471056 53
1791471061 53
1791471066 48
1791471071 48
1791471076 48
```
</details>

---

