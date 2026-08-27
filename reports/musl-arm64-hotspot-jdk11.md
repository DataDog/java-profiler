---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-27 10:49:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1007 |
| Sample Rate | 16.78/sec |
| Health Score | 1049% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787841912 40
1787841917 40
1787841922 40
1787841927 40
1787841932 40
1787841937 40
1787841942 40
1787841947 40
1787841952 40
1787841957 40
1787841962 40
1787841967 40
1787841972 40
1787841977 48
1787841982 48
1787841987 48
1787841992 48
1787841997 48
1787842002 48
1787842007 48
```
</details>

---

