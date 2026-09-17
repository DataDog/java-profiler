---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:00:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 43-56 cores)</summary>

```
1789682112 43
1789682117 43
1789682122 43
1789682127 43
1789682132 43
1789682137 43
1789682142 43
1789682147 43
1789682152 43
1789682157 43
1789682162 43
1789682167 43
1789682172 43
1789682177 43
1789682182 43
1789682187 43
1789682192 43
1789682197 56
1789682202 56
1789682207 56
```
</details>

---

