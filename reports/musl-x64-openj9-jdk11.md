---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 06:49:44 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1027 |
| Sample Rate | 17.12/sec |
| Health Score | 1070% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 38-40 cores)</summary>

```
1790765091 40
1790765096 40
1790765101 40
1790765106 40
1790765111 40
1790765116 40
1790765121 40
1790765126 40
1790765131 40
1790765136 40
1790765141 40
1790765146 40
1790765151 38
1790765156 38
1790765161 38
1790765166 38
1790765171 38
1790765176 38
1790765181 38
1790765186 38
```
</details>

---

