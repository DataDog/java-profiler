---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:59:16 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 31-35 cores)</summary>

```
1795532026 34
1795532031 34
1795532036 34
1795532041 34
1795532046 35
1795532051 35
1795532056 31
1795532061 31
1795532066 31
1795532071 31
1795532076 31
1795532081 31
1795532086 31
1795532091 31
1795532096 31
1795532101 31
1795532106 31
1795532111 31
1795532116 31
1795532121 31
```
</details>

---

