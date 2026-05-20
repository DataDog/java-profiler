---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-20 05:49:44 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1779270360 59
1779270365 59
1779270370 59
1779270375 59
1779270380 59
1779270385 59
1779270390 59
1779270395 54
1779270400 54
1779270405 54
1779270410 54
1779270415 54
1779270420 54
1779270425 54
1779270430 54
1779270435 54
1779270440 54
1779270445 54
1779270450 54
1779270455 54
```
</details>

---

