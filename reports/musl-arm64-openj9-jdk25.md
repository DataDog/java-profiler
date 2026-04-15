---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:59:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1776279112 64
1776279117 64
1776279122 64
1776279127 64
1776279132 64
1776279137 64
1776279142 64
1776279147 64
1776279152 64
1776279157 64
1776279162 62
1776279167 62
1776279172 62
1776279177 62
1776279182 64
1776279187 64
1776279192 64
1776279197 64
1776279202 64
1776279207 64
```
</details>

---

