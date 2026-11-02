---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-02 07:22:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1793621914 10
1793621919 10
1793621924 10
1793621929 10
1793621934 10
1793621939 10
1793621944 10
1793621949 10
1793621954 10
1793621959 10
1793621964 10
1793621969 10
1793621975 10
1793621980 10
1793621985 10
1793621990 10
1793621995 10
1793622000 10
1793622005 10
1793622010 30
```
</details>

---

