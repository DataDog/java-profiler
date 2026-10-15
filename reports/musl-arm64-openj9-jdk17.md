---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-15 11:57:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1792079306 64
1792079311 64
1792079316 64
1792079321 64
1792079326 64
1792079331 53
1792079336 53
1792079341 53
1792079346 53
1792079351 53
1792079356 53
1792079361 53
1792079366 53
1792079371 53
1792079376 53
1792079381 53
1792079386 53
1792079391 53
1792079396 53
1792079401 53
```
</details>

---

