---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:24:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1794593994 80
1794593999 80
1794594004 80
1794594009 80
1794594014 80
1794594019 80
1794594024 80
1794594029 80
1794594034 80
1794594039 80
1794594044 80
1794594049 80
1794594054 80
1794594059 80
1794594064 80
1794594069 80
1794594074 80
1794594079 80
1794594084 82
1794594089 82
```
</details>

---

