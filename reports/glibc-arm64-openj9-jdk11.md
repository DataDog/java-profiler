---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 07:13:55 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 9 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790680173 38
1790680178 38
1790680183 38
1790680188 43
1790680193 43
1790680198 43
1790680203 43
1790680208 43
1790680213 43
1790680218 43
1790680223 43
1790680228 43
1790680233 43
1790680238 43
1790680243 43
1790680248 43
1790680253 43
1790680258 43
1790680263 43
1790680268 43
```
</details>

---

