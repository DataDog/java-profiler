---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 09:50:14 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1789738930 64
1789738935 64
1789738940 64
1789738945 64
1789738950 64
1789738955 64
1789738960 64
1789738965 64
1789738970 64
1789738975 64
1789738980 64
1789738985 64
1789738990 64
1789738995 64
1789739000 64
1789739005 64
1789739010 64
1789739015 64
1789739020 64
1789739025 64
```
</details>

---

