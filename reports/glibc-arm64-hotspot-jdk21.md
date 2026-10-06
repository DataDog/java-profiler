---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 06:41:32 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 412 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1791282985 33
1791282990 33
1791282995 33
1791283000 33
1791283005 33
1791283010 33
1791283015 33
1791283020 33
1791283025 33
1791283030 33
1791283035 33
1791283040 38
1791283045 38
1791283050 38
1791283055 38
1791283060 38
1791283065 38
1791283070 38
1791283075 38
1791283080 38
```
</details>

---

