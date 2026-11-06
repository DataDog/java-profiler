---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 20:23:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 8 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1793927857 35
1793927863 35
1793927868 35
1793927873 35
1793927878 35
1793927883 35
1793927888 35
1793927893 35
1793927898 35
1793927903 35
1793927908 35
1793927913 30
1793927918 30
1793927923 30
1793927928 30
1793927933 30
1793927938 30
1793927943 30
1793927948 30
1793927953 30
```
</details>

---

