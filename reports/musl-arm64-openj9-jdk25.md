---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 07:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 9 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 31-43 cores)</summary>

```
1790855138 31
1790855143 31
1790855148 31
1790855153 31
1790855158 31
1790855163 31
1790855168 31
1790855173 31
1790855178 31
1790855183 31
1790855188 31
1790855193 31
1790855198 31
1790855203 43
1790855208 43
1790855213 33
1790855218 33
1790855223 38
1790855228 38
1790855233 38
```
</details>

---

