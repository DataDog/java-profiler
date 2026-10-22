---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 19:41:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 73-96 cores)</summary>

```
1792712207 73
1792712212 73
1792712217 73
1792712222 73
1792712227 73
1792712232 73
1792712237 73
1792712242 73
1792712247 73
1792712252 94
1792712257 94
1792712262 94
1792712267 94
1792712272 96
1792712277 96
1792712282 96
1792712287 96
1792712292 96
1792712297 96
1792712302 96
```
</details>

---

