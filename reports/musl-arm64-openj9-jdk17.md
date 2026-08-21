---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-21 10:44:45 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 349 |
| Sample Rate | 5.82/sec |
| Health Score | 364% |
| Threads | 12 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1787323182 34
1787323187 39
1787323192 39
1787323197 39
1787323202 39
1787323207 39
1787323212 39
1787323217 39
1787323223 39
1787323228 39
1787323233 39
1787323238 39
1787323243 39
1787323248 39
1787323253 39
1787323258 39
1787323263 39
1787323268 39
1787323273 39
1787323278 39
```
</details>

---

