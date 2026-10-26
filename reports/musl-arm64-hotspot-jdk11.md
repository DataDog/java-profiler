---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 14:59:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1793040912 31
1793040917 31
1793040922 31
1793040927 31
1793040932 31
1793040937 31
1793040942 31
1793040947 31
1793040952 31
1793040957 31
1793040962 31
1793040967 31
1793040972 31
1793040977 31
1793040982 31
1793040987 31
1793040992 31
1793040997 31
1793041002 31
1793041007 31
```
</details>

---

