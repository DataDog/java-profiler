---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:52:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 9-11 cores)</summary>

```
1789731992 11
1789731997 11
1789732002 11
1789732007 11
1789732012 11
1789732017 11
1789732022 11
1789732027 9
1789732032 9
1789732037 9
1789732042 9
1789732047 11
1789732052 11
1789732057 11
1789732062 11
1789732067 11
1789732072 11
1789732077 11
1789732082 11
1789732087 11
```
</details>

---

