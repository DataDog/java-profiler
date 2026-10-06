---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-06 06:41:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
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
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1791282909 20
1791282914 20
1791282919 20
1791282924 20
1791282929 20
1791282934 20
1791282939 20
1791282944 20
1791282949 22
1791282954 22
1791282959 22
1791282964 22
1791282969 22
1791282974 22
1791282979 22
1791282984 22
1791282989 22
1791282994 22
1791282999 22
1791283004 22
```
</details>

---

