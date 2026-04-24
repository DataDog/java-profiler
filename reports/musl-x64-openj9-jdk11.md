---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 12:55:19 EDT

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
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777049444 32
1777049449 32
1777049454 32
1777049459 32
1777049464 32
1777049469 32
1777049474 32
1777049479 32
1777049484 32
1777049489 32
1777049494 32
1777049499 32
1777049504 32
1777049509 32
1777049514 32
1777049519 32
1777049525 32
1777049530 32
1777049535 32
1777049540 32
```
</details>

---

