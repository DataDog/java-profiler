---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-19 05:47:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 13 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 13 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1789811032 48
1789811037 48
1789811042 48
1789811047 48
1789811052 43
1789811057 43
1789811062 43
1789811067 41
1789811072 41
1789811077 41
1789811082 41
1789811087 41
1789811092 41
1789811097 41
1789811102 41
1789811107 41
1789811112 41
1789811117 41
1789811122 41
1789811127 43
```
</details>

---

