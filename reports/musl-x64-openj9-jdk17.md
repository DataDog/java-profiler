---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 14:07:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 68-86 cores)</summary>

```
1773252113 68
1773252118 68
1773252123 68
1773252128 77
1773252133 77
1773252138 81
1773252143 81
1773252148 81
1773252153 81
1773252158 86
1773252163 86
1773252168 86
1773252173 86
1773252178 86
1773252183 86
1773252188 86
1773252193 86
1773252198 86
1773252203 86
1773252208 86
```
</details>

---

