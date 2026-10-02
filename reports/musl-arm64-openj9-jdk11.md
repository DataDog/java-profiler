---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-02 04:21:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 9 |
| Allocations | 209 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790929017 43
1790929022 43
1790929027 43
1790929032 43
1790929037 43
1790929042 43
1790929047 48
1790929052 48
1790929057 48
1790929062 48
1790929067 48
1790929072 48
1790929077 48
1790929082 48
1790929087 48
1790929092 48
1790929097 48
1790929102 48
1790929107 45
1790929112 45
```
</details>

---

