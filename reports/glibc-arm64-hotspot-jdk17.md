---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:59:21 EST

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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795452954 64
1795452959 64
1795452964 64
1795452969 64
1795452974 64
1795452979 64
1795452984 64
1795452989 64
1795452994 64
1795452999 64
1795453004 64
1795453009 64
1795453014 64
1795453019 64
1795453024 64
1795453029 64
1795453034 64
1795453039 64
1795453044 64
1795453049 64
```
</details>

---

