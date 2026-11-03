---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-03 14:44:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793734852 64
1793734857 64
1793734862 64
1793734867 64
1793734872 64
1793734877 64
1793734882 64
1793734887 64
1793734892 64
1793734897 64
1793734902 64
1793734907 64
1793734912 64
1793734917 64
1793734922 64
1793734927 64
1793734932 64
1793734937 64
1793734942 64
1793734947 64
```
</details>

---

