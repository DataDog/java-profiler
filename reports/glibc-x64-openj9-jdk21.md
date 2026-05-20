---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-20 05:49:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 634 |
| Sample Rate | 10.57/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 53-60 cores)</summary>

```
1779270360 58
1779270365 58
1779270370 58
1779270375 58
1779270380 58
1779270385 60
1779270390 60
1779270395 60
1779270400 60
1779270405 60
1779270410 60
1779270415 60
1779270420 60
1779270425 60
1779270430 60
1779270435 60
1779270440 60
1779270445 55
1779270450 55
1779270455 55
```
</details>

---

