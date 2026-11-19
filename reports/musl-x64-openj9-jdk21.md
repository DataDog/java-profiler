---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:46:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (6 unique values: 43-75 cores)</summary>

```
1795084952 43
1795084957 43
1795084962 43
1795084967 43
1795084972 59
1795084977 59
1795084982 45
1795084987 45
1795084992 45
1795084997 45
1795085002 45
1795085007 45
1795085012 47
1795085017 47
1795085022 49
1795085027 49
1795085032 49
1795085037 49
1795085042 49
1795085047 49
```
</details>

---

