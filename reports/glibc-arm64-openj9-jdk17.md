---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 18:03:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 13 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (3 unique values: 16-26 cores)</summary>

```
1789682169 26
1789682174 21
1789682179 21
1789682184 21
1789682189 21
1789682194 16
1789682199 16
1789682204 16
1789682209 16
1789682214 16
1789682219 16
1789682224 21
1789682229 21
1789682234 21
1789682239 21
1789682244 21
1789682249 26
1789682254 26
1789682259 26
1789682264 26
```
</details>

---

