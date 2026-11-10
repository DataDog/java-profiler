---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 10:42:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 13 |
| Allocations | 184 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794324992 48
1794324997 48
1794325002 48
1794325007 48
1794325012 48
1794325017 48
1794325022 48
1794325027 48
1794325032 48
1794325037 48
1794325042 48
1794325047 48
1794325052 48
1794325057 48
1794325062 48
1794325067 48
1794325072 48
1794325077 48
1794325082 48
1794325087 43
```
</details>

---

