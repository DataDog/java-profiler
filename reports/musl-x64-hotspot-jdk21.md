---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-15 16:13:28 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 43-52 cores)</summary>

```
1794776963 43
1794776968 43
1794776973 43
1794776978 43
1794776983 43
1794776988 43
1794776993 43
1794776998 43
1794777003 43
1794777008 52
1794777013 52
1794777018 52
1794777023 52
1794777028 52
1794777033 52
1794777038 52
1794777043 52
1794777048 52
1794777053 52
1794777058 52
```
</details>

---

