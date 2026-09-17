---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:26:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1789680093 30
1789680098 30
1789680103 30
1789680108 30
1789680113 30
1789680118 30
1789680123 30
1789680128 30
1789680133 30
1789680138 30
1789680143 30
1789680148 30
1789680153 30
1789680158 30
1789680163 30
1789680168 30
1789680173 30
1789680178 30
1789680183 30
1789680188 30
```
</details>

---

