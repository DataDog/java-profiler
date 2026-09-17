---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 17:26:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789680102 96
1789680107 96
1789680112 96
1789680118 96
1789680123 96
1789680128 96
1789680133 96
1789680138 96
1789680143 96
1789680148 96
1789680153 94
1789680158 94
1789680163 94
1789680168 94
1789680173 94
1789680178 94
1789680183 96
1789680188 96
1789680193 96
1789680198 96
```
</details>

---

