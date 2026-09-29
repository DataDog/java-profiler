---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 58-61 cores)</summary>

```
1790699385 61
1790699390 61
1790699395 61
1790699400 61
1790699406 61
1790699411 61
1790699416 61
1790699421 61
1790699426 61
1790699431 58
1790699436 58
1790699441 58
1790699446 58
1790699451 58
1790699456 58
1790699461 61
1790699466 61
1790699471 61
1790699476 61
1790699481 61
```
</details>

---

