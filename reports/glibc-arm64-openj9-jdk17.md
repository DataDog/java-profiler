---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:24:50 EST

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
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794594014 48
1794594019 48
1794594024 48
1794594029 48
1794594034 48
1794594039 48
1794594044 43
1794594049 43
1794594054 43
1794594059 43
1794594064 43
1794594069 43
1794594074 43
1794594079 43
1794594084 43
1794594089 43
1794594094 43
1794594099 43
1794594104 43
1794594109 43
```
</details>

---

