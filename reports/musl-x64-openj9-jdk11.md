---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 12:32:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 899 |
| Sample Rate | 14.98/sec |
| Health Score | 936% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1770139427 32
1770139432 32
1770139437 32
1770139442 32
1770139447 32
1770139452 30
1770139457 30
1770139462 30
1770139467 30
1770139472 30
1770139477 30
1770139482 30
1770139487 30
1770139492 28
1770139497 28
1770139502 32
1770139507 32
1770139512 32
1770139518 32
1770139523 32
```
</details>

---

