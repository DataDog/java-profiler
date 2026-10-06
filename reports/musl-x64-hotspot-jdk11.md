---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 06:41:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 423 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1791282895 26
1791282900 26
1791282905 26
1791282910 26
1791282915 26
1791282920 28
1791282925 28
1791282930 30
1791282935 30
1791282940 30
1791282945 30
1791282950 30
1791282955 30
1791282960 30
1791282965 30
1791282970 30
1791282975 30
1791282980 30
1791282985 30
1791282990 32
```
</details>

---

