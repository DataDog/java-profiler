---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-05 13:29:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1021 |
| Sample Rate | 17.02/sec |
| Health Score | 1064% |
| Threads | 13 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1772735110 59
1772735115 59
1772735120 59
1772735125 59
1772735130 57
1772735135 57
1772735140 57
1772735145 57
1772735150 57
1772735155 59
1772735160 59
1772735165 59
1772735170 59
1772735175 59
1772735180 59
1772735185 59
1772735190 61
1772735195 61
1772735200 61
1772735205 61
```
</details>

---

