---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 18:03:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1789682142 10
1789682147 12
1789682152 12
1789682157 12
1789682162 12
1789682167 12
1789682172 12
1789682177 12
1789682182 12
1789682187 12
1789682192 12
1789682197 12
1789682202 12
1789682207 12
1789682212 12
1789682217 12
1789682222 12
1789682227 12
1789682232 12
1789682237 12
```
</details>

---

