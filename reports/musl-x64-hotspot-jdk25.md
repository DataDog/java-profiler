---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-06 07:48:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 12 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 22-28 cores)</summary>

```
1772800918 28
1772800923 28
1772800928 28
1772800933 28
1772800938 24
1772800943 24
1772800948 22
1772800953 22
1772800958 26
1772800963 26
1772800968 28
1772800973 28
1772800978 28
1772800983 28
1772800988 28
1772800993 28
1772800998 28
1772801003 28
1772801008 28
1772801013 26
```
</details>

---

