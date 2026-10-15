---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 11:06:41 EDT

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
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 11 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792076376 43
1792076381 43
1792076386 43
1792076391 43
1792076396 43
1792076401 43
1792076406 43
1792076411 43
1792076416 43
1792076421 43
1792076426 43
1792076431 43
1792076436 43
1792076441 43
1792076446 43
1792076451 43
1792076456 43
1792076461 48
1792076466 48
1792076471 48
```
</details>

---

