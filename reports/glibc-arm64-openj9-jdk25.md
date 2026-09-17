---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 17:26:09 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 10 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (2 unique values: 37-38 cores)</summary>

```
1789680103 37
1789680108 37
1789680113 37
1789680118 37
1789680123 37
1789680128 37
1789680133 37
1789680138 37
1789680143 37
1789680148 37
1789680153 37
1789680158 37
1789680163 37
1789680168 37
1789680173 37
1789680178 37
1789680183 37
1789680188 38
1789680193 38
1789680198 38
```
</details>

---

