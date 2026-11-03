---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793734782 30
1793734787 30
1793734792 30
1793734797 30
1793734802 30
1793734807 30
1793734812 30
1793734817 30
1793734822 30
1793734827 30
1793734832 30
1793734837 30
1793734842 30
1793734847 30
1793734852 30
1793734857 32
1793734862 32
1793734867 32
1793734872 32
1793734877 32
```
</details>

---

