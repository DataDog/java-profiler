---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:29:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1789680081 42
1789680086 42
1789680092 42
1789680097 42
1789680102 42
1789680107 42
1789680112 42
1789680117 48
1789680122 48
1789680127 48
1789680132 48
1789680137 48
1789680142 48
1789680147 48
1789680152 48
1789680157 48
1789680162 48
1789680167 48
1789680172 48
1789680177 48
```
</details>

---

