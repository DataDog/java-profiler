---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-06 06:41:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1791282910 30
1791282915 30
1791282920 30
1791282925 30
1791282930 30
1791282935 30
1791282940 30
1791282945 28
1791282950 28
1791282955 28
1791282960 28
1791282965 28
1791282970 28
1791282975 28
1791282980 28
1791282985 28
1791282990 28
1791282995 28
1791283000 28
1791283005 28
```
</details>

---

