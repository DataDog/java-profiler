---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 19:41:09 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 75-96 cores)</summary>

```
1792712192 75
1792712197 75
1792712202 75
1792712207 75
1792712212 75
1792712217 75
1792712222 75
1792712227 75
1792712232 75
1792712237 75
1792712242 75
1792712247 75
1792712252 96
1792712257 96
1792712262 96
1792712267 96
1792712272 96
1792712277 96
1792712282 76
1792712287 76
```
</details>

---

