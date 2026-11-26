---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:26:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 52-57 cores)</summary>

```
1795702918 52
1795702923 52
1795702928 52
1795702933 52
1795702938 52
1795702943 54
1795702948 54
1795702953 57
1795702958 57
1795702963 55
1795702968 55
1795702973 55
1795702978 55
1795702983 55
1795702988 55
1795702993 55
1795702998 55
1795703003 55
1795703008 55
1795703013 55
```
</details>

---

