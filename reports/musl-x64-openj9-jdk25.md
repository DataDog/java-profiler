---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:03:57 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 74-96 cores)</summary>

```
1789682160 76
1789682165 76
1789682170 76
1789682175 76
1789682180 74
1789682185 74
1789682190 74
1789682195 74
1789682200 74
1789682205 74
1789682210 74
1789682215 94
1789682220 94
1789682225 94
1789682230 94
1789682235 94
1789682240 94
1789682245 96
1789682250 96
1789682255 96
```
</details>

---

