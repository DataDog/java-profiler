---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 09:27:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794234162 79
1794234167 79
1794234172 81
1794234177 81
1794234182 81
1794234187 81
1794234192 81
1794234197 81
1794234202 81
1794234207 81
1794234212 81
1794234217 81
1794234222 81
1794234227 81
1794234232 81
1794234237 81
1794234242 81
1794234247 81
1794234252 81
1794234257 81
```
</details>

---

