---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-20 01:00:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 12 |
| Allocations | 174 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789880142 43
1789880147 43
1789880152 43
1789880157 43
1789880162 43
1789880167 43
1789880172 43
1789880177 43
1789880182 43
1789880187 43
1789880192 43
1789880197 43
1789880202 43
1789880207 43
1789880212 43
1789880217 48
1789880222 48
1789880227 48
1789880232 48
1789880237 48
```
</details>

---

