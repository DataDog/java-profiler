---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:02:16 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 9 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 14 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 29-64 cores)</summary>

```
1795093096 64
1795093101 64
1795093106 29
1795093111 29
1795093116 29
1795093121 29
1795093126 29
1795093131 29
1795093136 29
1795093141 29
1795093146 29
1795093151 29
1795093156 29
1795093161 29
1795093166 29
1795093171 29
1795093176 29
1795093181 29
1795093187 29
1795093192 29
```
</details>

---

