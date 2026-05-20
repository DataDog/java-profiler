---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-20 05:49:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1040 |
| Sample Rate | 17.33/sec |
| Health Score | 1083% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1779270404 70
1779270410 70
1779270415 70
1779270420 70
1779270425 70
1779270430 70
1779270435 70
1779270440 70
1779270445 70
1779270450 70
1779270455 70
1779270460 70
1779270465 70
1779270470 70
1779270475 72
1779270480 72
1779270485 72
1779270490 72
1779270495 72
1779270500 72
```
</details>

---

