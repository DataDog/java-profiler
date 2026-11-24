---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:59:18 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 21-52 cores)</summary>

```
1795531971 29
1795531976 29
1795531981 29
1795531986 29
1795531991 29
1795531996 29
1795532001 29
1795532006 29
1795532011 29
1795532016 29
1795532021 29
1795532026 29
1795532031 29
1795532036 21
1795532041 21
1795532046 21
1795532051 21
1795532056 52
1795532061 52
1795532066 52
```
</details>

---

