---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-28 12:57:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 18-22 cores)</summary>

```
1787935960 18
1787935965 18
1787935970 18
1787935975 18
1787935980 18
1787935985 18
1787935990 18
1787935995 18
1787936000 18
1787936005 18
1787936010 19
1787936015 19
1787936020 19
1787936025 19
1787936030 22
1787936035 22
1787936040 22
1787936045 22
1787936050 22
1787936055 22
```
</details>

---

