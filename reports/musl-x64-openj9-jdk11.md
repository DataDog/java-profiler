---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

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
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795691099 94
1795691104 94
1795691109 94
1795691114 94
1795691119 94
1795691124 94
1795691129 94
1795691134 94
1795691139 94
1795691144 94
1795691149 94
1795691154 94
1795691159 96
1795691164 96
1795691169 96
1795691174 96
1795691179 96
1795691184 96
1795691189 96
1795691194 96
```
</details>

---

