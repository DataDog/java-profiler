---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 06:41:33 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 975 |
| Sample Rate | 16.25/sec |
| Health Score | 1016% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791282970 30
1791282975 30
1791282980 30
1791282985 30
1791282990 30
1791282995 30
1791283000 30
1791283005 30
1791283010 30
1791283015 30
1791283020 32
1791283025 32
1791283030 32
1791283035 32
1791283040 32
1791283045 32
1791283050 32
1791283055 32
1791283060 32
1791283065 32
```
</details>

---

