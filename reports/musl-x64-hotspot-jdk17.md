---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 10 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1789979857 76
1789979862 76
1789979867 76
1789979872 76
1789979877 76
1789979882 76
1789979887 76
1789979892 96
1789979897 96
1789979902 96
1789979907 84
1789979912 84
1789979917 84
1789979922 84
1789979927 84
1789979932 84
1789979937 84
1789979942 84
1789979947 84
1789979952 84
```
</details>

---

