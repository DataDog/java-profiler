---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 06:41:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (3 unique values: 53-64 cores)</summary>

```
1791282962 53
1791282967 53
1791282972 53
1791282977 53
1791282982 53
1791282987 53
1791282992 53
1791282997 53
1791283002 64
1791283007 64
1791283012 64
1791283017 64
1791283022 64
1791283027 64
1791283032 64
1791283037 64
1791283042 64
1791283047 64
1791283052 59
1791283057 59
```
</details>

---

