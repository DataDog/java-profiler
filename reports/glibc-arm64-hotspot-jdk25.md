---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 12:00:51 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795452949 54
1795452954 54
1795452959 54
1795452964 54
1795452969 54
1795452974 54
1795452979 59
1795452984 59
1795452989 59
1795452994 59
1795452999 59
1795453004 59
1795453009 59
1795453014 59
1795453019 59
1795453024 59
1795453029 59
1795453034 59
1795453039 59
1795453044 64
```
</details>

---

