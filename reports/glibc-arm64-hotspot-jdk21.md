---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 14:59:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1793040928 37
1793040933 37
1793040938 37
1793040943 37
1793040948 37
1793040953 38
1793040958 38
1793040963 48
1793040968 48
1793040973 48
1793040978 48
1793040983 48
1793040988 48
1793040993 48
1793040998 48
1793041003 48
1793041008 48
1793041013 48
1793041018 48
1793041023 48
```
</details>

---

