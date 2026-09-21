---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 04:42:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 50-81 cores)</summary>

```
1789979857 50
1789979862 50
1789979867 71
1789979872 71
1789979877 71
1789979882 71
1789979887 71
1789979892 71
1789979897 71
1789979902 71
1789979907 71
1789979912 71
1789979917 71
1789979922 71
1789979927 71
1789979932 71
1789979937 81
1789979942 81
1789979947 81
1789979952 81
```
</details>

---

