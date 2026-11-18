---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:33:04 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 44-54 cores)</summary>

```
1795011952 54
1795011957 49
1795011962 49
1795011967 49
1795011972 44
1795011977 44
1795011982 44
1795011987 44
1795011992 44
1795011997 44
1795012002 44
1795012007 44
1795012012 44
1795012017 44
1795012022 44
1795012027 44
1795012032 44
1795012037 44
1795012042 49
1795012047 49
```
</details>

---

