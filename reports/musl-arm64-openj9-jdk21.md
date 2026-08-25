---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 08:42:53 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1787661416 40
1787661421 40
1787661426 40
1787661431 35
1787661436 35
1787661441 35
1787661446 35
1787661451 35
1787661456 35
1787661461 35
1787661466 35
1787661471 35
1787661476 35
1787661481 35
1787661486 35
1787661491 35
1787661496 35
1787661501 35
1787661506 35
1787661511 35
```
</details>

---

