---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:23:42 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788139069 48
1788139074 48
1788139079 48
1788139084 48
1788139089 48
1788139094 48
1788139099 48
1788139104 48
1788139109 48
1788139114 48
1788139119 48
1788139124 48
1788139129 48
1788139134 43
1788139139 43
1788139144 43
1788139149 43
1788139154 43
1788139159 43
1788139164 43
```
</details>

---

