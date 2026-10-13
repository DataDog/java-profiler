---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 12:35:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1791908941 62
1791908946 62
1791908951 62
1791908956 62
1791908961 62
1791908966 62
1791908971 62
1791908976 62
1791908981 62
1791908986 62
1791908991 62
1791908996 62
1791909001 62
1791909006 62
1791909011 62
1791909016 62
1791909021 62
1791909026 62
1791909031 62
1791909036 60
```
</details>

---

