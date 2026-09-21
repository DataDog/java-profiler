---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:44:06 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 20-24 cores)</summary>

```
1789979847 20
1789979852 20
1789979857 22
1789979862 22
1789979867 24
1789979872 24
1789979877 24
1789979882 24
1789979887 24
1789979892 24
1789979897 22
1789979902 22
1789979907 22
1789979912 22
1789979917 22
1789979922 22
1789979927 22
1789979932 22
1789979937 22
1789979942 22
```
</details>

---

