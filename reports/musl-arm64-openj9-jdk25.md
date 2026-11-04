---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 14:11:24 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793819182 43
1793819187 43
1793819192 43
1793819197 43
1793819202 43
1793819207 43
1793819212 43
1793819217 43
1793819222 43
1793819227 43
1793819232 43
1793819237 43
1793819242 43
1793819247 48
1793819252 48
1793819257 48
1793819262 48
1793819267 48
1793819272 48
1793819277 48
```
</details>

---

