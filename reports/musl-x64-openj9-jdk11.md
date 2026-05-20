---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-20 05:49:44 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1779270390 45
1779270395 45
1779270400 45
1779270405 45
1779270410 45
1779270415 45
1779270420 45
1779270425 45
1779270430 45
1779270435 45
1779270440 45
1779270445 45
1779270450 40
1779270455 40
1779270460 40
1779270465 40
1779270470 40
1779270475 40
1779270480 40
1779270485 40
```
</details>

---

