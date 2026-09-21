---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:45:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 41-49 cores)</summary>

```
1789980008 41
1789980013 41
1789980018 41
1789980023 49
1789980028 49
1789980033 49
1789980038 49
1789980043 49
1789980048 49
1789980053 49
1789980058 49
1789980063 49
1789980068 49
1789980073 49
1789980078 49
1789980083 49
1789980088 49
1789980094 49
1789980099 49
1789980104 49
```
</details>

---

