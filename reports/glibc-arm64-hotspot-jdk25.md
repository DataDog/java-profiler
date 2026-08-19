---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 13:04:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1787158810 34
1787158815 34
1787158820 34
1787158825 34
1787158830 34
1787158835 34
1787158840 32
1787158845 32
1787158850 32
1787158855 32
1787158860 32
1787158865 32
1787158870 32
1787158875 32
1787158880 32
1787158885 32
1787158890 32
1787158895 32
1787158900 32
1787158905 32
```
</details>

---

