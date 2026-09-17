---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 06:26:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 33-43 cores)</summary>

```
1789640469 43
1789640474 43
1789640479 43
1789640484 43
1789640489 43
1789640494 43
1789640499 43
1789640504 43
1789640509 43
1789640514 41
1789640519 41
1789640525 41
1789640530 41
1789640535 41
1789640540 41
1789640545 39
1789640550 39
1789640555 39
1789640560 39
1789640565 39
```
</details>

---

