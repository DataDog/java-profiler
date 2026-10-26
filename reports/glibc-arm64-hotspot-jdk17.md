---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 14:59:54 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 9 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1793040978 51
1793040983 51
1793040988 51
1793040993 51
1793040998 51
1793041003 51
1793041008 51
1793041013 51
1793041018 51
1793041023 51
1793041028 51
1793041033 51
1793041038 51
1793041043 47
1793041048 47
1793041053 47
1793041058 47
1793041063 47
1793041068 47
1793041073 47
```
</details>

---

