---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:11:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789686375 43
1789686380 43
1789686385 43
1789686390 43
1789686395 43
1789686400 43
1789686405 43
1789686410 43
1789686415 43
1789686420 43
1789686425 43
1789686430 43
1789686435 43
1789686440 43
1789686445 43
1789686450 43
1789686455 43
1789686460 43
1789686465 43
1789686470 43
```
</details>

---

