---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 14:59:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 171 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793040917 43
1793040922 43
1793040927 43
1793040932 43
1793040937 43
1793040942 48
1793040947 48
1793040952 48
1793040957 48
1793040962 48
1793040967 48
1793040972 48
1793040977 48
1793040982 48
1793040987 48
1793040992 48
1793040997 48
1793041002 48
1793041007 48
1793041012 48
```
</details>

---

