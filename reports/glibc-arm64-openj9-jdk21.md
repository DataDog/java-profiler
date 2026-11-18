---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:30:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 11 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1795011937 47
1795011942 47
1795011947 47
1795011952 47
1795011957 47
1795011962 47
1795011967 47
1795011972 47
1795011977 47
1795011982 47
1795011987 47
1795011992 52
1795011997 52
1795012002 52
1795012007 52
1795012012 52
1795012017 52
1795012022 52
1795012027 52
1795012032 52
```
</details>

---

