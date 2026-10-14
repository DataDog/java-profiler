---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-14 09:58:41 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1791986014 48
1791986019 48
1791986024 48
1791986029 48
1791986034 48
1791986039 48
1791986044 48
1791986049 48
1791986054 48
1791986059 48
1791986064 48
1791986069 48
1791986074 40
1791986079 40
1791986084 40
1791986089 40
1791986094 40
1791986099 40
1791986104 40
1791986109 40
```
</details>

---

