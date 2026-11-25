---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:33:29 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 12 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 29-60 cores)</summary>

```
1795631391 29
1795631396 29
1795631401 29
1795631406 29
1795631411 29
1795631416 29
1795631421 29
1795631426 29
1795631431 29
1795631436 29
1795631441 29
1795631446 29
1795631451 29
1795631456 29
1795631461 60
1795631466 60
1795631471 60
1795631476 29
1795631481 29
1795631486 29
```
</details>

---

