---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 07:20:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 40-68 cores)</summary>

```
1795436124 40
1795436129 68
1795436134 68
1795436139 48
1795436145 48
1795436150 48
1795436155 48
1795436160 48
1795436165 48
1795436170 48
1795436175 48
1795436180 48
1795436185 48
1795436190 48
1795436195 48
1795436200 48
1795436205 48
1795436210 48
1795436215 48
1795436220 48
```
</details>

---

