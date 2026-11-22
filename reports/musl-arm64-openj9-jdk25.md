---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 15:36:12 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 11 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1795379493 40
1795379498 40
1795379503 40
1795379508 40
1795379514 40
1795379519 40
1795379524 40
1795379529 40
1795379534 40
1795379539 40
1795379544 40
1795379549 40
1795379554 40
1795379559 40
1795379564 40
1795379569 40
1795379574 40
1795379579 40
1795379584 40
1795379589 40
```
</details>

---

