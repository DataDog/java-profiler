---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 11:50:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 13 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791215115 43
1791215120 43
1791215125 43
1791215130 43
1791215135 48
1791215140 48
1791215145 48
1791215150 48
1791215155 48
1791215160 48
1791215165 48
1791215170 48
1791215175 48
1791215180 48
1791215185 48
1791215190 48
1791215195 48
1791215200 48
1791215205 48
1791215210 48
```
</details>

---

