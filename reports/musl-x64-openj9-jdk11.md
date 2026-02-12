---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-12 07:47:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1106 |
| Sample Rate | 18.43/sec |
| Health Score | 1152% |
| Threads | 14 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1770900110 94
1770900115 96
1770900120 96
1770900125 96
1770900130 96
1770900135 96
1770900140 96
1770900145 96
1770900150 96
1770900155 96
1770900160 96
1770900165 96
1770900170 96
1770900175 96
1770900180 96
1770900185 96
1770900190 96
1770900195 96
1770900200 96
1770900205 96
```
</details>

---

