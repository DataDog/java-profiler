---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:47:08 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 9 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 10 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 48-51 cores)</summary>

```
1794487333 49
1794487338 49
1794487343 49
1794487348 49
1794487353 49
1794487358 49
1794487363 49
1794487368 49
1794487373 49
1794487378 49
1794487383 49
1794487389 49
1794487394 49
1794487399 49
1794487404 51
1794487409 51
1794487414 51
1794487419 51
1794487424 51
1794487429 51
```
</details>

---

