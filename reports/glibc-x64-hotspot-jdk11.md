---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ❌ FAIL

**Date:** 2026-11-24 11:42:49 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1007 |
| Sample Rate | 16.78/sec |
| Health Score | 1049% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 64-73 cores)</summary>

```
1795538295 67
1795538300 67
1795538305 67
1795538310 64
1795538315 64
1795538320 73
1795538325 73
1795538330 73
1795538335 73
1795538340 73
1795538345 73
1795538350 73
1795538355 73
1795538360 73
1795538365 73
1795538370 73
1795538375 73
1795538380 73
1795538385 73
1795538390 73
```
</details>

---

