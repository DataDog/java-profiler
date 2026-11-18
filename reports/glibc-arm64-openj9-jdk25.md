---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 00:06:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794978177 29
1794978182 29
1794978187 29
1794978192 29
1794978197 29
1794978202 29
1794978207 29
1794978212 29
1794978217 29
1794978222 29
1794978227 29
1794978232 34
1794978237 34
1794978242 34
1794978247 34
1794978252 34
1794978257 34
1794978262 34
1794978267 34
1794978272 34
```
</details>

---

