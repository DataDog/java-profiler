---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-20 05:49:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (2 unique values: 88-93 cores)</summary>

```
1779270370 93
1779270375 93
1779270380 93
1779270385 93
1779270390 93
1779270395 93
1779270400 93
1779270405 93
1779270410 93
1779270415 93
1779270420 88
1779270425 88
1779270430 88
1779270435 88
1779270440 88
1779270445 88
1779270450 88
1779270455 88
1779270460 88
1779270465 88
```
</details>

---

