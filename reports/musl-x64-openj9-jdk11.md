---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:25:38 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 905 |
| Sample Rate | 15.08/sec |
| Health Score | 942% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 22-43 cores)</summary>

```
1790173183 22
1790173188 22
1790173193 22
1790173198 22
1790173203 22
1790173208 22
1790173213 22
1790173218 22
1790173223 22
1790173228 22
1790173233 22
1790173238 22
1790173243 22
1790173248 22
1790173253 22
1790173258 22
1790173263 30
1790173268 30
1790173273 30
1790173278 30
```
</details>

---

