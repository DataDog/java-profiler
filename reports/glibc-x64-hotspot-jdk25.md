---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 14:59:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 68-88 cores)</summary>

```
1793040938 68
1793040943 68
1793040948 68
1793040953 68
1793040958 68
1793040963 68
1793040968 68
1793040973 68
1793040978 68
1793040983 70
1793040988 70
1793040993 70
1793040998 70
1793041003 70
1793041008 74
1793041013 74
1793041018 74
1793041023 74
1793041028 70
1793041033 70
```
</details>

---

