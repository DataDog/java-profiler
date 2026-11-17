---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:43:11 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 352 |
| Sample Rate | 5.87/sec |
| Health Score | 367% |
| Threads | 13 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (1 unique values: 15-15 cores)</summary>

```
1794915472 15
1794915477 15
1794915482 15
1794915487 15
1794915492 15
1794915497 15
1794915502 15
1794915507 15
1794915512 15
1794915517 15
1794915522 15
1794915527 15
1794915532 15
1794915537 15
1794915542 15
1794915547 15
1794915552 15
1794915557 15
1794915562 15
1794915567 15
```
</details>

---

