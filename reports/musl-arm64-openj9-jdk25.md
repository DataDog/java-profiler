---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-29 10:20:25 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 14 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793283324 48
1793283329 48
1793283334 48
1793283339 48
1793283344 48
1793283349 48
1793283354 48
1793283359 48
1793283364 48
1793283369 48
1793283374 48
1793283379 48
1793283384 48
1793283389 48
1793283394 48
1793283399 48
1793283404 48
1793283409 48
1793283414 48
1793283419 48
```
</details>

---

