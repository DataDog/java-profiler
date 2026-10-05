---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-05 11:50:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 8 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791215115 30
1791215120 30
1791215125 30
1791215130 30
1791215135 32
1791215140 32
1791215145 32
1791215150 32
1791215155 32
1791215160 32
1791215165 32
1791215170 32
1791215175 32
1791215180 32
1791215185 32
1791215190 32
1791215195 32
1791215200 32
1791215205 32
1791215210 32
```
</details>

---

