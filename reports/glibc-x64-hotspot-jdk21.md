---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:53:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1795106978 64
1795106983 64
1795106988 64
1795106993 64
1795106998 64
1795107003 64
1795107008 64
1795107013 64
1795107018 64
1795107023 64
1795107028 64
1795107033 64
1795107038 64
1795107043 64
1795107048 64
1795107053 64
1795107058 64
1795107063 64
1795107068 64
1795107073 64
```
</details>

---

