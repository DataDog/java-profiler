---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:32:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 71-75 cores)</summary>

```
1794914940 71
1794914945 71
1794914950 71
1794914955 71
1794914960 71
1794914965 71
1794914970 71
1794914975 71
1794914980 73
1794914985 73
1794914990 75
1794914995 75
1794915000 75
1794915005 75
1794915010 75
1794915015 75
1794915020 75
1794915025 75
1794915030 75
1794915035 75
```
</details>

---

